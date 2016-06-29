#ifndef PIGA_PLAYER_H_INCLUDED
#define PIGA_PLAYER_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <piga/player_role.h>
#include <piga/player_status.h>
#include <piga/player_inputs.h>

#include <piga/status.h>

#define PIGA_PLAYER_NAME_LENGTH 50
#define PIGA_PLAYER_DEFAULT_NAME "Undefined"

typedef struct piga_player piga_player;
    
piga_player* piga_player_create();
void piga_player_free(piga_player *player);

void piga_player_init(char *memory);

char* piga_player_get_name(piga_player *player);
/**
 * @brief Sets the name to the player with the length (without \0 ).
 */
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
int piga_player_get_direct_output(piga_player *player, char output_id);
void piga_player_set_direct_output(piga_player *player, char output_id, int value);

#ifdef __cplusplus
}
#endif


#endif