#include <stdlib.h>
#include <piga/player.h>

piga_player* piga_player_create()
{
    piga_player *player = (piga_player*) malloc(sizeof(piga_player));
    piga_player_init((char* ) player);
    return player;
}
void piga_player_init(char* memory)
{
    piga_player *player = (piga_player*) memory;
    player->role = PIGA_PLAYER_ROLE_GUEST;
    player->status = PIGA_PLAYER_STATUS_OFFLINE;
    piga_player_inputs_reset(&player->inputs);
}
void piga_player_free(piga_player* player)
{
    free(player);
}
const char* piga_player_get_name(piga_player* player)
{
    return player->name;
}
short int piga_player_get_name_length(piga_player* player)
{
    for(int i = 0; i < PIGA_PLAYER_NAME_LENGTH; ++i)
        if(player->name[i] == '\0')
            return i;
    return 0;
}
void piga_player_set_name(piga_player* player, const char* name, short int length)
{
    if(length >= PIGA_PLAYER_NAME_LENGTH)
        for(int i = 0; i < length; ++i)
            player->name[i] = name[i];
}
piga_player_role piga_player_get_role(piga_player* player)
{
    return player->role;
}
void piga_player_set_role(piga_player* player, piga_player_role role)
{
    player->role = role;
}
piga_player_status piga_player_get_status(piga_player* player)
{
    return player->status;
}
void piga_player_set_status(piga_player* player, piga_player_status status)
{
    player->status = status;
}
piga_player_inputs* piga_player_get_inputs(piga_player* player)
{
    return &player->inputs;
}
int piga_player_get_input(piga_player* player, char input_id)
{
    return piga_player_inputs_get(&player->inputs, input_id);
}
void piga_player_set_input(piga_player* player, char input_id, int value)
{
    piga_player_inputs_set(&player->inputs, input_id, value);
}


