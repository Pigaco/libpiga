#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <piga/host.h>
#include <piga/internal/piga_event_queue_struct.h>
#include <piga/internal/piga_player_struct.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>

piga_host* piga_host_create()
{
    piga_host* host = (piga_host*) malloc(sizeof(piga_host));
    host->config = NULL;
    host->shared_memory_id = 0;
    host->shared_memory.start = NULL;
    host->shared_memory.players = NULL;
    host->host_queue = 0;
    host->host_queue_shm_id = 0;
    piga_clients_map_init(&host->clients_map);
    host->cache_event = piga_event_create();
    return host;
}
piga_status piga_host_consume_config(piga_host *host, piga_host_config* config)
{
    if(host->config) 
        free(host->config);
    host->config = config;
    
    return PIGA_STATUS_OK;
}
piga_status piga_host_free(piga_host *host)
{
    // Cleanup
    if(host->config->create_shared_memory && host->shared_memory.start) 
        shmdt(host->shared_memory.start);
    
    // Remove the shared memory.
    piga_shared_memory_free_players(&host->shared_memory);
    
    if(host->config->create_shared_memory && host->shared_memory_id)
        shmctl(host->shared_memory_id, IPC_RMID, NULL);
    
    // Free the host-queue, if it has been created.
    if(host->host_queue) {
        piga_event_queue_free_in_shm(host->host_queue, host->host_queue_shm_id);
        host->host_queue = 0;
        host->host_queue_shm_id = 0;
    }
    
    if(host->config) 
        free(host->config);
    
    piga_event_free(host->cache_event);
    
    free(host);
    
    return PIGA_STATUS_OK;
}

piga_status piga_host_startup(piga_host *host)
{
    if(!host->config)
        return PIGA_ERROR_HOST_HAS_NO_CONFIG;
    
    if(host->config->create_shared_memory) {
        int shared_memory_size = 
            host->config->player_count * sizeof(piga_player)
          + 120; // Padding
          
        host->shared_memory_id = shmget(host->config->shared_memory_key, 
                                        shared_memory_size, IPC_CREAT | 0666);
        if(host->shared_memory_id == -1)
            return PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
        
        // Mapping the start segment
        void *start = shmat(host->shared_memory_id, 0, 0);
        if(start == (void*) -1)
            return PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY;
        else 
            host->shared_memory.start = start;
        
        // Initialize the memory
        {
            size_t size = (sizeof(piga_player) * host->config->player_count + 1);
            piga_player **players = malloc(size);
            memcpy(host->shared_memory.start, (&players[0]), size);
            free(players);
        }
        
        // Setup the memory mappings
        piga_shared_memory_map(&host->shared_memory, host->shared_memory.start, host->config->player_count);
        
        // Set the default player names
        for(size_t i = 0; i < host->config->player_count; ++i) {
            piga_player_init((char*) piga_host_get_player_by_id(host, i));
            piga_player_set_name(piga_host_get_player_by_id(host, i), 
                PIGA_PLAYER_DEFAULT_NAME, sizeof(PIGA_PLAYER_DEFAULT_NAME));
        }
        
        piga_status status;
        
        // Setup the host-queue 
        host->host_queue = piga_event_queue_create_in_shm(PIGA_EVENT_QUEUE_START_KEY,
            &host->host_queue_shm_id,
            &status
        );
        
        if(status != PIGA_STATUS_OK) 
            return status;
    }
    
    return PIGA_STATUS_OK;
}
piga_player* piga_host_get_player_by_id(piga_host* host, char player_id)
{
    return host->shared_memory.players[player_id];
}
void piga_host_set_player_input(piga_host* host, char player_id, char input_id, int value)
{
    piga_player *player = piga_host_get_player_by_id(host, player_id);
    player->inputs.value[input_id] = value;
}
piga_event_queue* piga_host_get_event_queue(piga_host* host)
{
    return host->host_queue;
}
void piga_host_players_reset_inputs(piga_host* host)
{
    for(int i = 0; i < host->config->player_count; ++i)
        piga_player_inputs_reset(&(piga_host_get_player_by_id(host, i)->inputs));
}
void piga_host_push_event(piga_host* host, piga_event* ev)
{
    piga_clients_map_push_event(&host->clients_map, ev);
}
void piga_host_update(piga_host* host)
{
    while(piga_event_queue_poll(host->host_queue, host->cache_event) == PIGA_STATUS_OK) {
        switch(piga_event_get_type(host->cache_event)) {
            case PIGA_EVENT_CONSUMER_REGISTERED:
                piga_clients_map_add_from_ev(&host->clients_map, 
                    piga_event_get_consumer_registered(host->cache_event));
                break;
            case PIGA_EVENT_CONSUMER_UNREGISTERED:
                piga_clients_map_remove_from_ev(&host->clients_map,
                    piga_event_get_consumer_unregistered(host->cache_event));
                break;
            case PIGA_EVENT_APP_INSTALLED:
                break;
            case PIGA_EVENT_GAME_INPUT:
                break;
            case PIGA_EVENT_PLAYER_JOINED:
                break;
            case PIGA_EVENT_PLAYER_LEFT:
                break;
            case PIGA_EVENT_REQUEST_KEYBOARD:
                break;
            case PIGA_EVENT_REQUEST_RESTART:
                break;
            case PIGA_EVENT_TEXT_INPUT:
                break;
            case PIGA_EVENT_PLUGIN_MSG:
                break;
            case PIGA_EVENT_UNKNOWN:
                break;
            }
        }
    }
