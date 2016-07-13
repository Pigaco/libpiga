#include <stdlib.h>
#include <piga/client.h>
#include <piga/internal/piga_event_queue_struct.h>
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
    client->in_queue = 0;
    client->in_queue_shm_id = 0;
    client->out_queue = 0;
    client->out_queue_shm_id = 0;
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
    
    // Unregister this consumer.
    piga_event *ev = piga_event_create();
    piga_event_set_type(ev, PIGA_EVENT_CONSUMER_UNREGISTERED);
    piga_event_consumer_unregistered *unregistered = piga_event_get_consumer_unregistered(ev);
    piga_event_consumer_unregistered_set_shm_key(unregistered, piga_event_queue_get_default_process_shm_key());
    piga_event_queue_push(client->out_queue, ev);
    piga_event_free(ev);
    
    if(client->out_queue) {
        piga_event_queue_disconnect_from_shm(client->out_queue);
        client->out_queue = 0;
        client->out_queue_shm_id = 0;
    }
    if(client->in_queue) {
        piga_event_queue_free_in_shm(client->in_queue, client->in_queue_shm_id);
        client->in_queue = 0;
        client->in_queue_shm_id = 0;
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
piga_status piga_client_connect(piga_client* client, const char *name, int name_length)
{
    int shared_memory_size = 
        client->config->player_count * sizeof(piga_player)
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
    
    // Attach to the host-queue (out-queue).
    piga_status status;
    client->out_queue = piga_event_queue_connect_to_shm(
        PIGA_EVENT_QUEUE_START_KEY, 
        &client->out_queue_shm_id, 
        &status
    );
    
    if(status != PIGA_STATUS_OK)
        return status;
    
    // Create the in-queue. 
    client->in_queue = piga_event_queue_create_default_in_shm(
        &client->in_queue_shm_id,
        &status,
        client->out_queue,
        name, name_length
    );
    
    if(status != PIGA_STATUS_OK)
        return status;
    
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
piga_event_queue* piga_client_get_in_queue(piga_client* client)
{
    return client->in_queue;
}
piga_event_queue* piga_client_get_out_queue(piga_client* client)
{
    return client->out_queue;
}
piga_status piga_client_push_event(piga_client* client, piga_event* ev)
{
    if(!client->out_queue) 
        return PIGA_ERROR_NO_OUT_QUEUE;
    
    piga_event_queue_push(client->out_queue, ev);
}