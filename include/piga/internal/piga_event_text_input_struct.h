#ifndef PIGA_INTERNAL_EVENT_TEXT_INPUT_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_TEXT_INPUT_STRUCT_H_INCLUDED

#include <piga/event_text_input.h>
#include <stdatomic.h>

struct piga_event_text_input
{
    atomic_char player_id; 
    atomic_char input[PIGA_EVENT_TEXT_INPUT_TEXT_SIZE];
    atomic_long seconds;
    atomic_long nanoseconds;
};

#endif