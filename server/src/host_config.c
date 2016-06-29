#include <piga/host_config.h>
#include <stdlib.h>

piga_host_config* piga_host_config_default()
{
    piga_host_config *config = (piga_host_config*) malloc(sizeof(piga_host_config));
    
    // Set the default configuration
    config->create_shared_memory = 1;
    config->name = "Default Piga Host";
    config->player_count = PIGA_DEFAULT_PLAYER_COUNT;
    
    // The default key for shared memory is defined in 
    // PIGA_DEFAULT_SHARED_MEMORY_KEY
    config->shared_memory_key = PIGA_DEFAULT_SHARED_MEMORY_KEY;
    
    return config;
}
void piga_host_config_free(piga_host_config* config)
{
    free(config);
}
short unsigned int piga_host_config_get_create_shared_memory(const piga_host_config* config)
{
    return config->create_shared_memory;
}
void piga_host_config_set_create_shared_memory(piga_host_config* config, short unsigned int val)
{
    config->create_shared_memory = val;
}
int piga_host_config_get_shared_memory_key(const piga_host_config* config)
{
    return config->shared_memory_key;
}
void piga_host_config_set_shared_memory_key(piga_host_config* config, int key)
{
    config->shared_memory_key = key;
}
const char* piga_host_config_get_name(const piga_host_config* config)
{
    return config->name;
}
void piga_host_config_set_name(piga_host_config* config, const char* name)
{
    config->name = name;
}