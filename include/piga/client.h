#ifndef PIGA_CLIENT_H_INCLUDED
#define PIGA_CLIENT_H_INCLUDED

#include <piga/client_config.h>
#include <piga/status.h>
#include <piga/player.h>
#include <piga/event_text_input_queue.h>

typedef struct 
{
    piga_client_config *config;
    int shared_memory_id;
    char* shared_memory_start_segment;
} piga_client;

piga_client* piga_client_create();
piga_status piga_client_free(piga_client* client);

void piga_client_consume_config(piga_client *client, piga_client_config *config);

piga_status piga_client_connect(piga_client *client);

int piga_client_get_shared_memory_id(piga_client *client);

char* piga_client_get_shared_memory_start_segment(piga_client *client);

piga_player* piga_client_get_player_by_id(piga_client *client, char player_id);
piga_event_text_input_queue* piga_client_get_event_text_input_queue(piga_client *client);

#endif
