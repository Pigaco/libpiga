#ifndef PIGA_INTERNAL_EVENT_PLAYER_JOINED_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_PLAYER_JOINED_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_player_joined.h>

struct piga_event_player_joined {
    atomic_char player_id;
};

#endif
