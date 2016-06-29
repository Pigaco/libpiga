#ifndef PIGA_INTERNAL_EVENT_TEXT_INPUT_QUEUE_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_TEXT_INPUT_QUEUE_STRUCT_H_INCLUDED

#include <piga/internal/piga_event_text_input_struct.h>
#include <piga/event_text_input_queue.h>

struct piga_event_text_input_queue
{
    piga_event_text_input elements[PIGA_EVENT_TEXT_INPUT_QUEUE_SIZE];
    atomic_char front;
    atomic_char rear;
}; 

#endif