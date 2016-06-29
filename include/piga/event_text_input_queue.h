#ifndef PIGA_EVENT_TEXT_INPUT_QUEUE_H_INCLUDED
#define PIGA_EVENT_TEXT_INPUT_QUEUE_H_INCLUDED

#define PIGA_EVENT_TEXT_INPUT_QUEUE_SIZE 10

#include <stdatomic.h>

#include <piga/status.h>
#include <piga/event_text_input.h>

typedef struct
{
    piga_event_text_input elements[PIGA_EVENT_TEXT_INPUT_QUEUE_SIZE];
    atomic_char front;
    atomic_char rear;
} piga_event_text_input_queue;

piga_event_text_input_queue* piga_event_text_input_queue_create();
void piga_event_text_input_queue_free(piga_event_text_input_queue *queue);
void piga_event_text_input_queue_init(char *memory);

/**
 * @brief Pushes input to the specified queue. The pointer will not be consumed.
 */
piga_status piga_event_text_input_queue_push(piga_event_text_input_queue *queue, piga_event_text_input *input);

/**
 * @brief Polls the queue and tries to copy the content of the currently topmost element to tgt. 
 * 
 * The counter will be moved forward (and the function will return PIGA_STATUS_OK), as long as there are 
 * events. As soon as there aren't any more, this
 * function will return PIGA_ERROR_EMPTY_QUEUE.
 */
piga_status piga_event_text_input_queue_poll(piga_event_text_input_queue *queue, piga_event_text_input *tgt);

/**
 * @brief Returns 1 if the queue is empty, 0 otherwise.
 */
int piga_event_text_input_queue_is_empty(piga_event_text_input_queue *queue);

#endif