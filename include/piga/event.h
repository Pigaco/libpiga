#ifndef PIGA_EVENT_H_INCLUDED
#define PIGA_EVENT_H_INCLUDED

typedef struct piga_event piga_event;
typedef struct piga_event_text_input piga_event_text_input;
typedef struct piga_event_game_input piga_event_game_input;
typedef struct piga_event_player_joined piga_event_player_joined;
typedef struct piga_event_player_left piga_event_player_left;
typedef struct piga_event_request_keyboard piga_event_request_keyboard;
typedef struct piga_event_request_restart piga_event_request_restart;
typedef struct piga_event_app_installed piga_event_app_installed;
typedef struct piga_event_consumer_registered piga_event_consumer_registered;
typedef struct piga_event_consumer_unregistered piga_event_consumer_unregistered;

typedef enum {
    PIGA_EVENT_UNKNOWN                  = 1 << 0,
    PIGA_EVENT_TEXT_INPUT               = 1 << 1,
    PIGA_EVENT_GAME_INPUT               = 1 << 2,
    PIGA_EVENT_PLAYER_JOINED            = 1 << 3,
    PIGA_EVENT_PLAYER_LEFT              = 1 << 4,
    PIGA_EVENT_REQUEST_KEYBOARD         = 1 << 5,
    PIGA_EVENT_REQUEST_RESTART          = 1 << 6,
    PIGA_EVENT_APP_INSTALLED            = 1 << 7,
    PIGA_EVENT_CONSUMER_REGISTERED      = 1 << 8,
    PIGA_EVENT_CONSUMER_UNREGISTERED    = 1 << 9,
} piga_event_type;

piga_event* piga_event_create();
void piga_event_free(piga_event *ev);

/**
 * @brief Copies the contents of src to tgt.
 * @param src The source to copy from.
 * @param tgt The target to copy to.
 *
 * This function doesn't allocate memory and only copies the contents of the event (including the event_union).
 */
void piga_event_copy(piga_event *src, piga_event *tgt);

piga_event_type piga_event_get_type(piga_event *ev);
void piga_event_set_type(piga_event *ev, piga_event_type type);

piga_event_text_input* piga_event_get_text_input(piga_event *ev);
piga_event_game_input* piga_event_get_game_input(piga_event *ev);
piga_event_player_joined* piga_event_get_player_joined(piga_event *ev);
piga_event_player_left* piga_event_get_player_left(piga_event *ev);
piga_event_request_keyboard* piga_event_get_request_keyboard(piga_event *ev);
piga_event_request_restart* piga_event_get_request_restart(piga_event *ev);
piga_event_app_installed* piga_event_get_app_installed(piga_event *ev);
piga_event_consumer_registered* piga_event_get_consumer_registered(piga_event *ev);
piga_event_consumer_unregistered* piga_event_get_consumer_unregistered(piga_event *ev);

#endif
