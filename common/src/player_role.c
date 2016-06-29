#include <piga/player_role.h>

const char* piga_player_role_name(piga_player_role role)
{
    switch(role)
    {
        case PIGA_PLAYER_ROLE_PERMANENTLY_BANNED:
            return "Permanently Banned";
        case PIGA_PLAYER_ROLE_TEMPORARY_BANNED:
            return "Temporarily Banned";
        case PIGA_PLAYER_ROLE_KICKED:
            return "Kicked";
        case PIGA_PLAYER_ROLE_NORMAL:
            return "Normal";
        case PIGA_PLAYER_ROLE_MODERATOR:
            return "Moderator";
        case PIGA_PLAYER_ROLE_ADMIN:
            return "Admin";
        case PIGA_PLAYER_ROLE_SUPER_ADMIN:
            return "Super Admin";
        case PIGA_PLAYER_ROLE_OWNER:
            return "Owner";
    }
    return "Unknown Role";
}

