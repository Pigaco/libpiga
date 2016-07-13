#ifndef piga_event_queue_H_INCLUDED
#define piga_event_queue_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
    
#define PIGA_EVENT_QUEUE_SIZE 10
    
// The start key defines the starting point for the shm_keys 
// of shared memory segments of the event queues. The additional 
// queues use PID-IDs and add them to this number, to stay unique.
// Additionally, this is the ID of the host-queue.
#define PIGA_EVENT_QUEUE_START_KEY 7010
    
#include <piga/status.h>
#include <piga/event.h>

typedef struct piga_event_queue piga_event_queue;
    
piga_event_queue* piga_event_queue_create();

/**
 * @brief Creates the event queue in the specified shared memory segment.
 * 
 * This should be followed by a new piga_event_consumer_registered to the host, to register the queue. 
 */
piga_event_queue* piga_event_queue_create_default_in_shm(int *shm_id, piga_status *status, piga_event_queue *host_queue, const char *name, int name_length);
piga_event_queue* piga_event_queue_create_in_shm(int shm_key, int *shm_id, piga_status *status);
piga_event_queue* piga_event_queue_connect_to_shm(int shm_key, int* shm_id, piga_status *status);
int piga_event_queue_get_default_process_shm_key();

void piga_event_queue_free(piga_event_queue *queue);
piga_status piga_event_queue_disconnect_from_shm(piga_event_queue* queue);
piga_status piga_event_queue_free_in_shm(piga_event_queue* queue, int shm_id);
void piga_event_queue_init(char *memory);

/**
 * @brief Pushes input to the specified queue. The pointer will not be consumed.
 */
piga_status piga_event_queue_push(piga_event_queue *queue, piga_event *input);

/**
 * @brief Polls the queue and tries to copy the content of the currently topmost element to tgt. 
 * 
 * The counter will be moved forward (and the function will return PIGA_STATUS_OK), as long as there are 
 * events. As soon as there aren't any more, this
 * function will return PIGA_ERROR_EMPTY_QUEUE.
 */
piga_status piga_event_queue_poll(piga_event_queue *queue, piga_event *tgt);

/**
 * @brief Returns 1 if the queue is empty, 0 otherwise.
 */
int piga_event_queue_is_empty(piga_event_queue *queue);

int piga_event_queue_is_in_type_mask(piga_event_queue *queue, piga_event_type type);


#ifdef __cplusplus
}
#endif

#endif
