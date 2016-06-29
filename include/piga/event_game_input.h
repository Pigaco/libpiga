#ifndef PIGA_EVENT_GAME_INPUT_H_INCLUDED
#define PIGA_EVENT_GAME_INPUT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct piga_event_game_input piga_event_game_input;

char piga_event_game_input_get_player_id(piga_event_game_input *game_input);
char piga_event_game_input_get_input_id(piga_event_game_input *game_input);
int piga_event_game_input_get_input_value(piga_event_game_input *game_input);

void piga_event_game_input_set_player_id(piga_event_game_input* game_input, char player_id);
void piga_event_game_input_set_input_id(piga_event_game_input* game_input, char input_id);
void piga_event_game_input_set_input_value(piga_event_game_input *game_input, int value);

long piga_event_game_input_get_seconds(piga_event_game_input *game_input);
long piga_event_game_input_get_nanoseconds(piga_event_game_input *game_input);
void piga_event_game_input_set_seconds(piga_event_game_input *game_input, long seconds);
void piga_event_game_input_set_nanoseconds(piga_event_game_input *game_input, long nanoseconds);

#ifdef __cplusplus
}
#endif

#endif