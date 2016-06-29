#ifndef PIGA_HOST_CONFIG_H_INCLUDED
#define PIGA_HOST_CONFIG_H_INCLUDED

#define PIGA_DEFAULT_SHARED_MEMORY_KEY 7001
#define PIGA_DEFAULT_PLAYER_COUNT 16

typedef struct 
{
    unsigned short create_shared_memory : 1;
    int shared_memory_key;
    char player_count;
    const char* name;
} piga_host_config;

piga_host_config* piga_host_config_default();
void piga_host_config_free(piga_host_config *config);

unsigned short piga_host_config_get_create_shared_memory(const piga_host_config *config);
void piga_host_config_set_create_shared_memory(piga_host_config *config, unsigned short val);

int piga_host_config_get_shared_memory_key(const piga_host_config *config);
void piga_host_config_set_shared_memory_key(piga_host_config *config, int key);

const char* piga_host_config_get_name(const piga_host_config* config);
void piga_host_config_set_name(piga_host_config *config, const char* name);

#endif