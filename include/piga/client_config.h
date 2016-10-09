#ifndef PIGA_CLIENT_CONFIG_H_INCLUDED
#define PIGA_CLIENT_CONFIG_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    int shared_memory_key;
    char player_count;
    int event_type_mask;
} piga_client_config;

piga_client_config* piga_client_config_default();
void piga_client_config_free(piga_client_config *config);

int piga_client_config_get_shared_memory_key(piga_client_config *config);
void piga_client_config_set_shared_memory_key(piga_client_config *config, int key);

char piga_client_config_get_player_count(piga_client_config *config);
void piga_client_config_set_player_count(piga_client_config *config, char player_count);

int piga_client_config_get_event_type_mask(piga_client_config *config);
void piga_client_config_set_event_type_mask(piga_client_config *config, int type_mask);

#ifdef __cplusplus
}
#endif


#endif
