#ifndef PIGA_PLAYER_INPUTS_H_INCLUDED
#define PIGA_PLAYER_INPUTS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
    
#define PIGA_PLAYER_INPUTS_COUNT 32

typedef struct piga_player_inputs piga_player_inputs;
    
void piga_player_inputs_reset(piga_player_inputs *inputs);

const char* piga_player_inputs_get_input_name(int input_id);

int piga_player_inputs_get(piga_player_inputs *inputs, char id);
void piga_player_inputs_set(piga_player_inputs *inputs, char id, int value);

int piga_player_inputs_get_direct_output(piga_player_inputs *inputs, char id);
void piga_player_inputs_set_direct_output(piga_player_inputs *inputs, char id, int value);

#ifdef __cplusplus
}
#endif

#endif