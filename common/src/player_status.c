#include <piga/player_status.h>

const char* piga_player_status_name(piga_player_status status)
{
    switch(status) 
    {
        case PIGA_PLAYER_STATUS_OFFLINE:
            return "Offline";
        case PIGA_PLAYER_STATUS_ONLINE:
            return "Online";
        case PIGA_PLAYER_STATUS_WAITING:
            return "Waiting";
        case PIGA_PLAYER_STATUS_TYPING:
            return "Typing";
    }
    return "Unknown Status";
}