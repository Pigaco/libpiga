#ifndef PIGA_CLIENT_CONFIG_H_INCLUDED
#define PIGA_CLIENT_CONFIG_H_INCLUDED

typedef struct
{
    int shared_memory_key;
    char player_count;
} piga_client_config;

piga_client_config* piga_client_config_default();
void piga_client_config_free(piga_client_config *config);

int piga_client_config_get_shared_memory_key(piga_client_config *config);
void piga_client_config_set_shared_memory_key(piga_client_config *config, int key);

char piga_client_config_get_player_count(piga_client_config *config);
void piga_client_config_set_player_count(piga_client_config *config, char player_count);

#endif