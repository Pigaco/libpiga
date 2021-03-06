#ifndef PIGA_HOST_H_INCLUDED
#define PIGA_HOST_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
    
#include <piga/status.h>
#include <piga/host_config.h>
#include <piga/player.h>
#include <piga/event_queue.h>
#include <piga/shared_memory.h>
#include <piga/clients_map.h>
    
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
     */
    piga_shared_memory shared_memory;
    
    // Host-Queue. This queue serves as an out-queue for other processes and as an in-queue for the host.
    piga_event_queue *host_queue;
    int host_queue_shm_id;
    piga_clients_map clients_map;
    
    // This event is used as a cache while looping through the host-queue.
    piga_event *cache_event;
} piga_host;

piga_host* piga_host_create();
piga_status piga_host_consume_config(piga_host* host, piga_host_config* config);
piga_status piga_host_free(piga_host *host);

piga_status piga_host_startup(piga_host* host);

piga_player* piga_host_get_player_by_id(piga_host *host, char player_id);
piga_event_queue* piga_host_get_event_queue(piga_host *host);
void piga_host_push_event(piga_host *host, piga_event *ev);
void piga_host_update(piga_host *host);

void piga_host_set_player_input(piga_host* host, char player_id, char input_id, int value);

void piga_host_players_reset_inputs(piga_host *host);

#ifdef __cplusplus
}
#endif

#endif
