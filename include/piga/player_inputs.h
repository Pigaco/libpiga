#ifndef PIGA_PLAYER_INPUTS_H_INCLUDED
#define PIGA_PLAYER_INPUTS_H_INCLUDED

#include <stdatomic.h>

#define PIGA_PLAYER_INPUTS_COUNT 32

typedef struct 
{
    atomic_int value[PIGA_PLAYER_INPUTS_COUNT];
    atomic_int direct_output[PIGA_PLAYER_INPUTS_COUNT];
} piga_player_inputs;

void piga_player_inputs_reset(piga_player_inputs *inputs);

const char* piga_player_inputs_get_input_name(int input_id);

int piga_player_inputs_get(piga_player_inputs *inputs, char id);
void piga_player_inputs_set(piga_player_inputs *inputs, char id, int value);

int piga_player_direct_output_get(piga_player_inputs *inputs, char id);
void piga_player_direct_output_set(piga_player_inputs *inputs, char id, int value);

#endif