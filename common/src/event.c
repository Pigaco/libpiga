#include <stdlib.h>
#include <string.h>
#include <piga/internal/piga_event_struct.h>

piga_event *piga_event_create()
{
    piga_event *ev = malloc(sizeof(piga_event));
    return ev;
}

void piga_event_free(piga_event *ev)
{
    free(ev);
}

void piga_event_copy(piga_event *src, piga_event *tgt)
{
    memcpy(tgt, src, sizeof(piga_event));
}

piga_event_type piga_event_get_type(piga_event *ev)
{
    return ev->type;
}

void piga_event_set_type(piga_event *ev, piga_event_type type)
{
    ev->type = type;
}

piga_event_text_input *piga_event_get_text_input(piga_event *ev)
{
    return &ev->text_input;
}

piga_event_game_input* piga_event_get_game_input(piga_event* ev)
{
    return &ev->game_input;
}

piga_event_player_joined *piga_event_get_player_joined(piga_event *ev)
{
    return &ev->player_joined;
}

piga_event_player_left *piga_event_get_player_left(piga_event *ev)
{
    return &ev->player_left;
}

piga_event_request_keyboard *piga_event_get_request_keyboard(piga_event *ev)
{
    return &ev->request_keyboard;
}

piga_event_request_restart *piga_event_get_request_restart(piga_event *ev)
{
    return &ev->request_restart;
}

piga_event_app_installed *piga_event_get_app_installed(piga_event *ev)
{
    return &ev->app_installed;
}

piga_event_consumer_registered* piga_event_get_consumer_registered(piga_event* ev)
{
    return &ev->consumer_registered;
}

piga_event_consumer_unregistered* piga_event_get_consumer_unregistered(piga_event* ev)
{
    return &ev->consumer_unregistered;
}