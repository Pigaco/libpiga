#include <piga/event_game_input.h>

char piga_event_game_input_get_player_id(piga_event_game_input* game_input)
{
    return game_input->player_id;
}
char piga_event_game_input_get_input_id(piga_event_game_input* game_input)
{
    return game_input->input_id;
}
int piga_event_game_input_get_input_value(piga_event_game_input* game_input)
{
    return game_input->input_value;
}
long int piga_event_game_input_get_seconds(piga_event_game_input* game_input)
{
    return game_input->seconds;
}
long int piga_event_game_input_get_nanoseconds(piga_event_game_input* game_input)
{
    return game_input->nanoseconds;
}
void piga_event_game_input_set_seconds(piga_event_game_input* game_input, long int seconds)
{
    game_input->seconds = seconds;
}
void piga_event_game_input_set_nanoseconds(piga_event_game_input* game_input, long int nanoseconds)
{
    game_input->nanoseconds = nanoseconds;
}
void piga_event_game_input_set_player_id(piga_event_game_input* game_input, char player_id)
{
    game_input->player_id = player_id;
}
void piga_event_game_input_set_input_id(piga_event_game_input* game_input, char input_id)
{
    game_input->input_id = input_id;
}
void piga_event_game_input_set_input_value(piga_event_game_input* game_input, int value)
{
    game_input->input_value = value;
}
