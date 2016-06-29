#include <stdlib.h>
#include <piga/client_config.h>
#include <piga/host_config.h>

piga_client_config* piga_client_config_default()
{
    piga_client_config *config = (piga_client_config*) malloc(sizeof(piga_client_config));
    
    // The defaults are received from the host header. These settings must match 
    // with the host!
    config->player_count = PIGA_DEFAULT_PLAYER_COUNT;
    config->shared_memory_key = PIGA_DEFAULT_SHARED_MEMORY_KEY;
    
    return config;
}
void piga_client_config_free(piga_client_config* config)
{
    free(config);
}
int piga_client_config_get_shared_memory_key(piga_client_config* config)
{
    return config->shared_memory_key;
}
void piga_client_config_set_shared_memory_key(piga_client_config* config, int key)
{
    config->shared_memory_key = key;
}
char piga_client_config_get_player_count(piga_client_config* config)
{
    return config->player_count;
}
void piga_client_config_set_player_count(piga_client_config* config, char player_count)
{
    config->player_count = player_count;
}
