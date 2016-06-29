#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <piga/host.h>
#include <piga/internal/piga_event_text_input_queue_struct.h>
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
    
    if(host->config) 
        free(host->config);
    
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
          + sizeof(piga_event_text_input_queue)
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
            
            piga_event_text_input_queue *queue = piga_event_text_input_queue_create();
            memcpy(host->shared_memory.start + size, queue, sizeof(piga_event_text_input_queue));
            free(queue);
        }
        
        // Setup the memory mappings
        piga_shared_memory_map(&host->shared_memory, host->shared_memory.start, host->config->player_count);
        
        // Set the default player names
        for(size_t i = 0; i < host->config->player_count; ++i) {
            piga_player_init((char*) piga_host_get_player_by_id(host, i));
            piga_player_set_name(piga_host_get_player_by_id(host, i), 
                PIGA_PLAYER_DEFAULT_NAME, sizeof(PIGA_PLAYER_DEFAULT_NAME));
        }
        piga_event_text_input_queue_init((char*) piga_host_get_event_text_input_queue(host));
        
        
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
piga_event_text_input_queue* piga_host_get_event_text_input_queue(piga_host* host)
{
    return host->shared_memory.event_text_input_queue;
}
void piga_host_players_reset_inputs(piga_host* host)
{
    for(int i = 0; i < host->config->player_count; ++i)
        piga_player_inputs_reset(&(piga_host_get_player_by_id(host, i)->inputs));
}