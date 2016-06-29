#include <stdlib.h>
#include <piga/event_text_input_queue.h>

piga_event_text_input_queue* piga_event_text_input_queue_create()
{
    piga_event_text_input_queue *queue = malloc(sizeof(piga_event_text_input_queue));
    piga_event_text_input_queue_init((char*) queue);
    return queue;
}
void piga_event_text_input_queue_init(char* memory)
{
    piga_event_text_input_queue *queue = (piga_event_text_input_queue*) memory;
    queue->front = 0;
    queue->rear = 0;
}
void piga_event_text_input_queue_free(piga_event_text_input_queue* queue)
{
    free(queue);
}
piga_status piga_event_text_input_queue_push(piga_event_text_input_queue* queue, piga_event_text_input* input)
{
    piga_event_text_input_copy(input, &queue->elements[queue->front++]);
    
    if(queue->front == PIGA_EVENT_TEXT_INPUT_QUEUE_SIZE)
        queue->front = 0;
}
piga_status piga_event_text_input_queue_poll(piga_event_text_input_queue* queue, piga_event_text_input* tgt)
{
    if(piga_event_text_input_queue_is_empty(queue))
        return PIGA_ERROR_EMPTY_QUEUE;
    piga_event_text_input_copy(&queue->elements[queue->rear++], tgt);
    
    if(queue->rear == PIGA_EVENT_TEXT_INPUT_QUEUE_SIZE)
        queue->rear = 0;
    
    return PIGA_STATUS_OK;
}
int piga_event_text_input_queue_is_empty(piga_event_text_input_queue* queue)
{
    return 1 ? queue->rear == queue->front : 0;
}
