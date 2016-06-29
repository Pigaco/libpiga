#ifndef PIGA_HOST_H_INCLUDED
#define PIGA_HOST_H_INCLUDED

#include <piga/status.h>
#include <piga/host_config.h>
#include <piga/player.h>
#include <piga/event_text_input_queue.h>

typedef struct {
    piga_host_config *config;
    int shared_memory_id;
    
    /**
     * @brief This pointer marks the start of the shared memory segment used to communicate with all clients.
     * 
     * ## Memory Layout
     * 
     * ### Player Type
     * 
     * The player type is 54 bytes long and contains information about a player.
     * 
     * ### Main Table
     * 
     * The main table contains all data and is accessed by all clients.
     * 
     * Name | Type | Description
     * -----|------|-------------
     * **Players**
     * Player[n] | piga_player | Players (as much as defined in the config).
     * **Queues**
     * Text Event Queue | piga_event_text_input_queue | The queue for text inputs.
     */
    char* shared_memory_start_segment;
} piga_host;

piga_host* piga_host_create();
piga_status piga_host_consume_config(piga_host* host, piga_host_config* config);
piga_status piga_host_free(piga_host *host);

piga_status piga_host_startup(piga_host* host);

piga_player* piga_host_get_player_by_id(piga_host *host, char player_id);
piga_event_text_input_queue* piga_host_get_event_text_input_queue(piga_host *host);

void piga_host_set_player_input(piga_host* host, char player_id, char input_id, int value);

void piga_host_players_reset_inputs(piga_host *host);

#endif