#include <stdlib.h>
#include <piga/client.h>
#include <sys/ipc.h>
#include <sys/shm.h>

piga_client* piga_client_create()
{
    piga_client *client = (piga_client*) malloc(sizeof(piga_client));
    client->config = NULL;
    client->shared_memory_id = 0;
    client->shared_memory_start_segment = NULL;
    return client;
}
piga_status piga_client_free(piga_client* client)
{
    // Check if the shared memory can be detached.
    // If it cannot be detached without errors, the destructor will stop and delete nothing.
    if(client->shared_memory_start_segment != NULL) {
        if(shmdt(client->shared_memory_start_segment) == -1)
            return PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY;
    }
        
    if(client->config != NULL)
        free(client->config);
    
    free(client);
    
    return PIGA_STATUS_OK;
}
void piga_client_consume_config(piga_client* client, piga_client_config* config)
{
    if(client->config != NULL)
        free(client->config);
    
    client->config = config;
}
piga_status piga_client_connect(piga_client* client)
{
    int shared_memory_size = 
        client->config->player_count * sizeof(piga_player)
        + sizeof(piga_event_text_input_queue);
        
    client->shared_memory_id = shmget(client->config->shared_memory_key, 
                                    shared_memory_size, IPC_EXCL | 0666);
    if(client->shared_memory_id == -1)
        return PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
    
    // Mapping the start segment
    client->shared_memory_start_segment = shmat(client->shared_memory_id, 0, 0);
}
int piga_client_get_shared_memory_id(piga_client* client)
{
    return client->shared_memory_id;
}
char* piga_client_get_shared_memory_start_segment(piga_client* client)
{
    return client->shared_memory_start_segment;
}
piga_player* piga_client_get_player_by_id(piga_client* client, char player_id)
{
    return (piga_player*) 
        (client->shared_memory_start_segment + player_id * sizeof(piga_player));
}
piga_event_text_input_queue* piga_client_get_event_text_input_queue(piga_client* client)
{
    return (piga_event_text_input_queue*) 
        (client->shared_memory_start_segment + client->config->player_count * sizeof(piga_player));
}
