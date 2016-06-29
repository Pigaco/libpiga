#ifndef PIGA_PLAYER_STATUS_H_INCLUDED
#define PIGA_PLAYER_STATUS_H_INCLUDED

#include <stdatomic.h>

typedef enum 
{
    PIGA_PLAYER_STATUS_OFFLINE = 0,
    PIGA_PLAYER_STATUS_ONLINE = 1,
    PIGA_PLAYER_STATUS_WAITING = 2,
    PIGA_PLAYER_STATUS_TYPING = 3,
} piga_player_status;

typedef atomic_char piga_player_status_char;

const char* piga_player_status_name(piga_player_status status);

#endif