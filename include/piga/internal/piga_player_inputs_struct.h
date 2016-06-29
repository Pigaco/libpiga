#ifndef PIGA_INTERNAL_PLAYER_INPUTS_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_PLAYER_INPUTS_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/player_inputs.h>

struct piga_player_inputs
{
    atomic_int value[PIGA_PLAYER_INPUTS_COUNT];
    atomic_int direct_output[PIGA_PLAYER_INPUTS_COUNT];
};

#endif