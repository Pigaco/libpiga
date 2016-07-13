#ifndef PIGA_INTERNAL_EVENT_GAME_INPUT_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_GAME_INPUT_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_game_input.h>

struct piga_event_game_input {
    atomic_char player_id;
    atomic_char input_id;
    atomic_int input_value;
    atomic_long seconds;
    atomic_long nanoseconds;
};

#endif