#ifndef PIGA_CLIENT_H_INCLUDED
#define PIGA_CLIENT_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <piga/client_config.h>
#include <piga/status.h>
#include <piga/player.h>
#include <piga/event_queue.h>
#include <piga/shared_memory.h>

typedef struct 
{
    piga_client_config *config;
    int shared_memory_id;
    piga_shared_memory shared_memory;
    
    piga_event_queue *in_queue;
    int in_queue_shm_id;
    piga_event_queue *out_queue;
    int out_queue_shm_id;
} piga_client;

piga_client* piga_client_create();
piga_status piga_client_free(piga_client* client);

void piga_client_consume_config(piga_client *client, piga_client_config *config);

piga_status piga_client_connect(piga_client *client, const char *name, int name_length);

int piga_client_get_shared_memory_id(piga_client *client);

char* piga_client_get_shared_memory_start_segment(piga_client *client);

piga_player* piga_client_get_player_by_id(piga_client *client, char player_id);

piga_event_queue* piga_client_get_in_queue(piga_client *client);
piga_event_queue* piga_client_get_out_queue(piga_client *client);
piga_status piga_client_push_event(piga_client* client, piga_event* ev);

#ifdef __cplusplus
}
#endif
    
#endif
