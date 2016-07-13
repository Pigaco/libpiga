#ifndef PIGA_INTERNAL_EVENT_PLAYER_LEFT_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_PLAYER_LEFT_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_player_left.h>

struct piga_event_player_left {
    atomic_char player_id;
};

#endif
