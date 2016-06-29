#include <piga/player_inputs.h>

void piga_player_inputs_reset(piga_player_inputs* inputs)
{
    for(int i = 0; i < PIGA_PLAYER_INPUTS_COUNT; ++i) {
        inputs->value[i] = 0; 
        inputs->direct_output[i] = 0;
    }
}
const char* piga_player_inputs_get_input_name(int input_id)
{
    switch(input_id) 
    {
        case 0:
            return "Joytick UP";
        case 1:
            return "Joystick DOWN";
        case 2: 
            return "Joystick LEFT";
        case 3: 
            return "Joystick RIGHT";
        case 4: 
            return "Joystick ACTION";
        case 5:
            return "Button 1";
        case 6: 
            return "Button 2";
        case 7: 
            return "Button 3";
        case 8: 
            return "Button 4";
        case 9: 
            return "Button 5";
        case 10: 
            return "Button 6";
    }
    
    if(input_id < PIGA_PLAYER_INPUTS_COUNT)
        return "Button is not specified in the Pigaco standard, but still valid.";
    else
        return "Button is invalid and outside of the supported range.";
}

int piga_player_inputs_get(piga_player_inputs* inputs, char id)
{
    return inputs->value[id];
}
void piga_player_inputs_set(piga_player_inputs* inputs, char id, int value)
{
    inputs->value[id] = value;
}
int piga_player_direct_output_get(piga_player_inputs* inputs, char id)
{
    return inputs->direct_output[id];
}
void piga_player_direct_output_set(piga_player_inputs* inputs, char id, int value)
{
    inputs->direct_output[id] = value;
}