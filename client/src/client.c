#include <stdlib.h>
#include <piga/client.h>
#include <piga/internal/piga_event_text_input_queue_struct.h>
#include <piga/internal/piga_player_struct.h>
#include <sys/ipc.h>
#include <sys/shm.h>

piga_client* piga_client_create()
{
    piga_client *client = (piga_client*) malloc(sizeof(piga_client));
    client->config = NULL;
    client->shared_memory_id = 0;
    client->shared_memory.start = NULL;
    client->shared_memory.players = NULL;
    return client;
}
piga_status piga_client_free(piga_client* client)
{
    // Check if the shared memory can be detached.
    // If it cannot be detached without errors, the destructor will stop and delete nothing.
    if(client->shared_memory.start != NULL) {
        if(shmdt(client->shared_memory.start) == -1)
            return PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY;
    }
    
    piga_shared_memory_free_players(&client->shared_memory);
        
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
        + sizeof(piga_event_text_input_queue)
        + 120; // Padding
        
    client->shared_memory_id = shmget(client->config->shared_memory_key, 
        shared_memory_size, 0666);
    if(client->shared_memory_id == -1)
        return PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
    
    // Mapping the start segment
    client->shared_memory.start = shmat(client->shared_memory_id, 0, 0);
    if(client->shared_memory.start == (void*) -1)
        return PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY;
    
    piga_shared_memory_map(&client->shared_memory, client->shared_memory.start, client->config->player_count);
    
    return PIGA_STATUS_OK;
}
int piga_client_get_shared_memory_id(piga_client* client)
{
    return client->shared_memory_id;
}
char* piga_client_get_shared_memory_start_segment(piga_client* client)
{
    return client->shared_memory.start;
}
piga_player* piga_client_get_player_by_id(piga_client* client, char player_id)
{
    return client->shared_memory.players[player_id];
}
piga_event_text_input_queue* piga_client_get_event_text_input_queue(piga_client* client)
{
    return client->shared_memory.event_text_input_queue;
}
