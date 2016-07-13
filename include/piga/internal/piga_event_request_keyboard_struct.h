#ifndef PIGA_INTERNAL_REQUEST_KEYBOARD_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_REQUEST_KEYBOARD_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_request_keyboard.h>

struct piga_event_request_keyboard {
    atomic_char player_id;
};

#endif
