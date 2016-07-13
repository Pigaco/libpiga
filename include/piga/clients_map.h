#ifndef PIGA_CLIENTS_MAP_H_INCLUDED
#define PIGA_CLIENTS_MAP_H_INCLUDED

#include <piga/event_queue.h>
#include <piga/event_consumer_registered.h>

#define PIGA_CLIENTS_MAP_ITEM_NUMBER 8

typedef struct {
    char name[PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH];
    int shm_key;
    int shm_id;
    piga_event_queue *queue;
} piga_clients_map_item;

typedef struct {
    piga_clients_map_item items[PIGA_CLIENTS_MAP_ITEM_NUMBER];
} piga_clients_map;

void piga_clients_map_item_set_shm_key(piga_clients_map_item *item, int shm_key);
int piga_clients_map_item_get_shm_key(piga_clients_map_item *item);

void piga_clients_map_item_set_shm_id(piga_clients_map_item *item, int shm_id);
int piga_clients_map_item_get_shm_id(piga_clients_map_item *item);

void piga_clients_map_item_set_queue(piga_clients_map_item *item, piga_event_queue *queue);
piga_event_queue* piga_clients_map_item_get_queue(piga_clients_map_item *item);
void piga_clients_map_item_push_event(piga_clients_map_item *item, piga_event *ev);

void piga_clients_map_item_set_name(piga_clients_map_item *item, const char *name, int name_length);
const char* piga_clients_map_item_get_name(piga_clients_map_item *item);

void piga_clients_map_init(piga_clients_map *map);

void piga_clients_map_push_event(piga_clients_map *map, piga_event *ev);

piga_status piga_clients_map_add(piga_clients_map *map, int shm_key, const char *name, int name_length);
piga_status piga_clients_map_add_from_ev(piga_clients_map *map, piga_event_consumer_registered *ev);
piga_status piga_clients_map_remove(piga_clients_map *map, int shm_key);
piga_status piga_clients_map_remove_from_ev(piga_clients_map *map, piga_event_consumer_unregistered *ev);

#endif