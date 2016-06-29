#ifndef PIGA_PLAYER_ROLE_H_INCLUDED
#define PIGA_PLAYER_ROLE_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
    
typedef enum 
{
    PIGA_PLAYER_ROLE_PERMANENTLY_BANNED = 0,
    PIGA_PLAYER_ROLE_TEMPORARY_BANNED = 1,
    PIGA_PLAYER_ROLE_KICKED = 2,
    PIGA_PLAYER_ROLE_GUEST = 3,
    PIGA_PLAYER_ROLE_NORMAL = 4,
    PIGA_PLAYER_ROLE_MODERATOR = 5,
    PIGA_PLAYER_ROLE_ADMIN = 6,
    PIGA_PLAYER_ROLE_SUPER_ADMIN = 7,
    PIGA_PLAYER_ROLE_OWNER = 8,
} piga_player_role;

typedef char piga_player_role_char;

const char* piga_player_role_name(piga_player_role role);

#ifdef __cplusplus
}
#endif

#endif