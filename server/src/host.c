#include <stdlib.h>

#include <piga/host.h>

#include <sys/ipc.h>
#include <sys/shm.h>

piga_host* piga_host_create()
{
    piga_host* host = (piga_host*) malloc(sizeof(piga_host));
    host->config = NULL;
    host->shared_memory_id = 0;
    host->shared_memory_start_segment = 0;
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
    if(host->config->create_shared_memory && host->shared_memory_start_segment) 
        shmdt(host->shared_memory_start_segment);
    
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
          + sizeof(piga_event_text_input_queue);
        
        host->shared_memory_id = shmget(host->config->shared_memory_key, 
                                        shared_memory_size, IPC_CREAT | 0666);
        if(host->shared_memory_id == -1)
            return PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
        
        // Mapping the start segment
        host->shared_memory_start_segment = shmat(host->shared_memory_id, 0, 0);
        
        // Initialize the memory.
        for(int i = 0; i < host->config->player_count; ++i)
            piga_player_init((char *) piga_host_get_player_by_id(host, i));
        
        piga_event_text_input_queue_init((char *) piga_host_get_event_text_input_queue(host));
    }
    
    return PIGA_STATUS_OK;
}
piga_player* piga_host_get_player_by_id(piga_host* host, char player_id)
{
    return (piga_player*) 
        (host->shared_memory_start_segment + (player_id * sizeof(piga_player)));
}
void piga_host_set_player_input(piga_host* host, char player_id, char input_id, int value)
{
    piga_player *player = piga_host_get_player_by_id(host, player_id);
    player->inputs.value[input_id] = value;
}
piga_event_text_input_queue* piga_host_get_event_text_input_queue(piga_host* host)
{
    return (piga_event_text_input_queue*) 
        (host->config->player_count * sizeof(piga_player));
}
void piga_host_players_reset_inputs(piga_host* host)
{
    for(int i = 0; i < host->config->player_count; ++i)
        piga_player_inputs_reset(&(piga_host_get_player_by_id(host, i)->inputs));
}