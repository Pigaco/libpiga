#ifndef PIGA_INTERNAL_EVENT_TEXT_INPUT_QUEUE_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_TEXT_INPUT_QUEUE_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/internal/piga_event_struct.h>
#include <piga/event_queue.h>

struct piga_event_queue {
    atomic_int type_mask;
    piga_event elements[PIGA_EVENT_QUEUE_SIZE];
    atomic_char front;
    atomic_char rear;
}; 

#endif
