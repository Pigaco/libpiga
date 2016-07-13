#include <stdlib.h>
#include <stdatomic.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <piga/internal/piga_event_queue_struct.h>
#include <piga/event.h>

#define PIGA_EVENT_QUEUE_SHM_SIZE sizeof(piga_event_queue) + 20

piga_event_queue* piga_event_queue_create()
{
    piga_event_queue *queue = malloc(sizeof(piga_event_queue));
    piga_event_queue_init((char*) queue);
    return queue;
}
piga_event_queue* piga_event_queue_create_in_shm(int shm_key, int* shm_id, piga_status* status)
{
    *shm_id = shmget(shm_key, 
        PIGA_EVENT_QUEUE_SHM_SIZE, IPC_CREAT | 0666);
    if(*shm_id == -1) {
        *status = PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
        return 0;
    }
    
    // Mapping the start segment
    void *start = shmat(*shm_id, 0, 0);
    if(start == (void*) -1) {
        *status = PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY;
        return 0;
    }
    
    // Copy the event queue into SHM and remove the old one afterwards.
    piga_event_queue *queue = piga_event_queue_create();
    memcpy(start, queue, sizeof(piga_event_queue));
    piga_event_queue_free(queue);
    
    *status = PIGA_STATUS_OK;
    return start;
}
piga_event_queue* piga_event_queue_connect_to_shm(int shm_key, int* shm_id, piga_status *status)
{
    *shm_id = shmget(shm_key, 
        PIGA_EVENT_QUEUE_SHM_SIZE, 0666);
    if(*shm_id == -1) {
        *status = PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY;
        return 0;
    }
    
    // Mapping the start segment
    void *start = shmat(*shm_id, 0, 0);
    if(start == (void*) -1) {
        *status = PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY;
        return 0;
    }
    
    piga_event_queue *queue = (piga_event_queue*) start;
    
    *status = PIGA_STATUS_OK;
    return queue;
}
piga_event_queue* piga_event_queue_create_default_in_shm(int* shm_id, piga_status* status, piga_event_queue *host_queue, const char *name, int name_length)
{
    int shm_key = piga_event_queue_get_default_process_shm_key();
    
    piga_event_queue *queue = piga_event_queue_create_in_shm(
        shm_key,
        shm_id,
        status
    );
    
    if(*status == PIGA_STATUS_OK) {
        piga_event *ev = piga_event_create();
        
        piga_event_set_type(ev, PIGA_EVENT_CONSUMER_REGISTERED);
        
        piga_event_consumer_registered *consumer_registered = piga_event_get_consumer_registered(ev);
        piga_event_consumer_registered_set_shm_key(consumer_registered, shm_key);
        piga_event_consumer_registered_set_name(consumer_registered, name, name_length);
        
        piga_event_queue_push(host_queue, ev);
        
        piga_event_free(ev);
    }
    
    return queue;
}
int piga_event_queue_get_default_process_shm_key()
{
    return PIGA_EVENT_QUEUE_START_KEY + getpid();
}
void piga_event_queue_init(char* memory)
{
    piga_event_queue *queue = (piga_event_queue*) memory;
    queue->front = 0;
    queue->rear = 0;

    // Initialize the type mask. This mask defines the types of
    // events, this queue receives from the other side.
    queue->type_mask =
              PIGA_EVENT_APP_INSTALLED
            | PIGA_EVENT_CONSUMER_REGISTERED
            | PIGA_EVENT_CONSUMER_UNREGISTERED
            | PIGA_EVENT_PLAYER_JOINED
            | PIGA_EVENT_PLAYER_LEFT
            | PIGA_EVENT_REQUEST_KEYBOARD
            | PIGA_EVENT_REQUEST_RESTART
            | PIGA_EVENT_TEXT_INPUT
            | PIGA_EVENT_GAME_INPUT
            | PIGA_EVENT_UNKNOWN;
}
void piga_event_queue_free(piga_event_queue* queue)
{
    free(queue);
}
piga_status piga_event_queue_disconnect_from_shm(piga_event_queue* queue)
{
    if(shmdt(queue) == -1)
        return PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY;
    
    return PIGA_STATUS_OK;
}
piga_status piga_event_queue_free_in_shm(piga_event_queue* queue, int shm_id)
{
    piga_status status = piga_event_queue_disconnect_from_shm(queue);
    if(status != PIGA_STATUS_OK)
        return status;
    
    shmctl(shm_id, IPC_RMID, NULL);
    
    return PIGA_STATUS_OK;
}
piga_status piga_event_queue_push(piga_event_queue* queue, piga_event* input)
{
    if(!piga_event_queue_is_in_type_mask(queue, piga_event_get_type(input)))
        return PIGA_ERROR_NOT_IN_TYPE_MASK;

    piga_event_copy(input, &queue->elements[queue->front++]);
    
    if(queue->front == PIGA_EVENT_QUEUE_SIZE)
        queue->front = 0;

    return PIGA_STATUS_OK;
}
piga_status piga_event_queue_poll(piga_event_queue* queue, piga_event *tgt)
{
    if(piga_event_queue_is_empty(queue))
        return PIGA_ERROR_EMPTY_QUEUE;
    piga_event_copy(&queue->elements[queue->rear++], tgt);
    
    if(queue->rear == PIGA_EVENT_QUEUE_SIZE)
        queue->rear = 0;
    
    return PIGA_STATUS_OK;
}
int piga_event_queue_is_empty(piga_event_queue* queue)
{
    return 1 ? queue->rear == queue->front : 0;
}

int piga_event_queue_is_in_type_mask(piga_event_queue *queue, piga_event_type type)
{
    return queue->type_mask & type;
}
