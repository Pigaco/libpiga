#ifndef PIGA_PLAYER_H_INCLUDED
#define PIGA_PLAYER_H_INCLUDED

#include <piga/player_role.h>
#include <piga/player_status.h>
#include <piga/player_inputs.h>

#include <piga/status.h>

#define PIGA_PLAYER_NAME_LENGTH 50

typedef struct 
{
    char name[PIGA_PLAYER_NAME_LENGTH];
    piga_player_role_char role;
    piga_player_status_char status;
    piga_player_inputs inputs;
} piga_player;

piga_player* piga_player_create();
void piga_player_free(piga_player *player);

void piga_player_init(char *memory);

const char* piga_player_get_name(piga_player *player);
void piga_player_set_name(piga_player *player, const char* name, short length);
short piga_player_get_name_length(piga_player *player);

piga_player_role piga_player_get_role(piga_player *player);
void piga_player_set_role(piga_player *player, piga_player_role role);

piga_player_status piga_player_get_status(piga_player *player);
void piga_player_set_status(piga_player *player, piga_player_status status);

piga_player_inputs* piga_player_get_inputs(piga_player *player);

// Convenience functions
int piga_player_get_input(piga_player *player, char input_id);
void piga_player_set_input(piga_player *player, char input_id, int value);

#endif