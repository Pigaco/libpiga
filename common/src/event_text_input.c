#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <piga/event_text_input.h>

piga_event_text_input* piga_event_text_input_create()
{
    piga_event_text_input *ev = malloc(sizeof(piga_event_text_input));
    ev->player_id = 0;
    for(int i = 0; i < PIGA_EVENT_TEXT_INPUT_TEXT_SIZE; ++i)
        ev->input[i] = '\0';
    ev->seconds = 0;
    ev->nanoseconds = 0;
    return ev;
}
void piga_event_text_input_free(piga_event_text_input* ev)
{
    free(ev);
}

char piga_event_text_input_get_player_id(const piga_event_text_input* ev)
{
    return ev->player_id;
}
void piga_event_text_input_set_player_id(piga_event_text_input* ev, char player_id)
{
    ev->player_id = player_id;
}
const atomic_char* piga_event_text_input_get_input(piga_event_text_input* ev)
{
    return &ev->input[0];
}
short piga_event_text_input_get_input_length(piga_event_text_input* ev)
{
    for(int i = 0; i < PIGA_EVENT_TEXT_INPUT_TEXT_SIZE; ++i) {
        if(ev->input[i] == '\0')
            return i;
    }
    return 0;
}
piga_status piga_event_text_input_set_input(piga_event_text_input* ev, const char* input, short int length)
{
    if(length >= PIGA_EVENT_TEXT_INPUT_TEXT_SIZE) {
        return PIGA_ERROR_EVENT_TEXT_INPUT_TEXT_TOO_LONG;
    }
    for(int i = 0; i < length; ++i) {
        ev->input[i] = input[i];
    }
    return PIGA_STATUS_OK;
}
long int piga_event_text_input_get_seconds(piga_event_text_input* ev)
{
    return ev->seconds;
}
void piga_event_text_input_set_seconds(piga_event_text_input* ev, long int seconds)
{
    ev->seconds = seconds;
}
long int piga_event_text_input_get_nanoseconds(piga_event_text_input* ev)
{
    return ev->nanoseconds;
}
void piga_event_text_input_set_nanoseconds(piga_event_text_input* ev, long int nanoseconds)
{
    ev->nanoseconds = nanoseconds;
}
void piga_event_text_input_copy(piga_event_text_input* src, piga_event_text_input* tgt)
{
    tgt->player_id = src->player_id;
    tgt->seconds = src->seconds;
    tgt->nanoseconds = src->nanoseconds;
    for(int i = 0; i < PIGA_EVENT_TEXT_INPUT_TEXT_SIZE; ++i) {
        tgt->input[i] = src->input[i];
    }
}
