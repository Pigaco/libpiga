#ifndef PIGA_INTERNAL_PLAYER_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_PLAYER_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/internal/piga_player_inputs_struct.h>
#include <piga/player.h>

struct piga_player
{
    atomic_char name[PIGA_PLAYER_NAME_LENGTH];
    atomic_char role;
    atomic_char status;
    piga_player_inputs inputs;
};

#endif