#ifndef PIGA_EVENT_TEXT_INPUT_H_INCLUDED
#define PIGA_EVENT_TEXT_INPUT_H_INCLUDED

#include <stdatomic.h>
#include <piga/status.h>

#define PIGA_EVENT_TEXT_INPUT_TEXT_SIZE 16

typedef struct 
{
    atomic_char player_id; 
    atomic_char input[PIGA_EVENT_TEXT_INPUT_TEXT_SIZE];
    atomic_long seconds;
    atomic_long nanoseconds;
} piga_event_text_input;

piga_event_text_input* piga_event_text_input_create();
void piga_event_text_input_free(piga_event_text_input *ev);

char piga_event_text_input_get_player_id(const piga_event_text_input *ev);
void piga_event_text_input_set_player_id(piga_event_text_input* ev, char player_id);

/**
 * @brief Writes the specified input to the internal buffer. 
 * 
 * \0 is stored with the string, so the maximum effective length possible for one
 * event is PIGA_EVENT_TEXT_INPUT_TEXT_SIZE - 1.
 */
piga_status piga_event_text_input_set_input(piga_event_text_input *ev, const char* input, short length);
const atomic_char* piga_event_text_input_get_input(piga_event_text_input *ev);
/**
 * @brief Returns the length of the internal input string (including \0 ).
 * 
 * Can be of the maximum size PIGA_EVENT_TEXT_INPUT_TEXT_SIZE,
 * because \0 gets added when read. 
 */
short piga_event_text_input_get_input_length(piga_event_text_input *ev);

long piga_event_text_input_get_seconds(piga_event_text_input *ev);
void piga_event_text_input_set_seconds(piga_event_text_input *ev, long seconds);

long piga_event_text_input_get_nanoseconds(piga_event_text_input *ev);
void piga_event_text_input_set_nanoseconds(piga_event_text_input *ev, long nanoseconds);

void piga_event_text_input_copy(piga_event_text_input *src, piga_event_text_input *tgt);

#endif