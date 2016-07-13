#ifndef PIGA_INTERNAL_EVENT_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_STRUCT_H_INCLUDED

#include <stdatomic.h>

#include <piga/event.h>
#include <piga/internal/piga_event_text_input_struct.h>
#include <piga/internal/piga_event_game_input_struct.h>
#include <piga/internal/piga_event_player_joined_struct.h>
#include <piga/internal/piga_event_player_left_struct.h>
#include <piga/internal/piga_event_request_keyboard_struct.h>
#include <piga/internal/piga_event_request_restart_struct.h>
#include <piga/internal/piga_event_app_installed_struct.h>
#include <piga/internal/piga_event_consumer_registered_struct.h>
#include <piga/internal/piga_event_consumer_unregistered_struct.h>

struct piga_event {
    atomic_int type;
    union {
        piga_event_text_input text_input;
        piga_event_game_input game_input;
        piga_event_app_installed app_installed;
        piga_event_consumer_registered consumer_registered;
        piga_event_consumer_unregistered consumer_unregistered;
        piga_event_player_joined player_joined;
        piga_event_player_left player_left;
        piga_event_request_keyboard request_keyboard;
        piga_event_request_restart request_restart;
    };
};

#endif
