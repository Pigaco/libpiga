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
    
    // Flags
    atomic_bool keyboard_requested;
    atomic_bool keyboard_open;
    
    // Inputs & Outputs
    piga_player_inputs inputs;
};

#endif