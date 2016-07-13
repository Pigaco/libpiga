#include <stdlib.h>
#include <string.h>
#include <piga/clients_map.h>

#include <piga/event_consumer_unregistered.h>

void piga_clients_map_item_set_name(piga_clients_map_item* item, const char* name, int name_length)
{
    memcpy(item->name, name, name_length);
}
const char* piga_clients_map_item_get_name(piga_clients_map_item* item)
{
    return item->name;
}
void piga_clients_map_item_set_shm_key(piga_clients_map_item* item, int shm_key)
{
    item->shm_key = shm_key;
}
int piga_clients_map_item_get_shm_key(piga_clients_map_item* item)
{
    return item->shm_key;
}
void piga_clients_map_item_set_shm_id(piga_clients_map_item* item, int shm_id)
{
    item->shm_id = shm_id;
}
int piga_clients_map_item_get_shm_id(piga_clients_map_item* item)
{
    return item->shm_id;
}
void piga_clients_map_item_set_queue(piga_clients_map_item* item, piga_event_queue* queue)
{
    item->queue = queue;
}
piga_event_queue* piga_clients_map_item_get_queue(piga_clients_map_item* item)
{
    return item->queue;
}
void piga_clients_map_item_push_event(piga_clients_map_item* item, piga_event* ev)
{
    piga_event_queue_push(item->queue, ev);
}
void piga_clients_map_init(piga_clients_map* map)
{
    for(size_t i = 0; i < PIGA_CLIENTS_MAP_ITEM_NUMBER; ++i) {
        map->items[i].queue = 0;
        map->items[i].shm_key = 0;
    }
}
piga_status piga_clients_map_add(piga_clients_map* map, int shm_key, const char* name, int name_length)
{
    for(size_t i = 0; i < PIGA_CLIENTS_MAP_ITEM_NUMBER; ++i) {
        if(map->items[i].queue == 0) {
            // This item is still unused.
            piga_clients_map_item_set_name(&map->items[i], name, name_length);
            piga_clients_map_item_set_shm_key(&map->items[i], shm_key);
            
            // Receive the queue.
            piga_status status;
            piga_event_queue *queue;
            queue = piga_event_queue_connect_to_shm(shm_key, &(map->items[i].shm_id), &status);
            if(status != PIGA_STATUS_OK)
                return status;
            
            piga_clients_map_item_set_queue(&map->items[i], queue);
            return PIGA_STATUS_OK;
        }
    }
    return PIGA_ERROR_NO_SPACE_LEFT_IN_MAP; 
}
piga_status piga_clients_map_remove(piga_clients_map* map, int shm_key)
{
    for(size_t i = 0; i < PIGA_CLIENTS_MAP_ITEM_NUMBER; ++i) {
        if(map->items[i].queue == 0) {
            if(piga_clients_map_item_get_shm_key(&map->items[i]) == shm_key) {
                // Disconnect the queue
                piga_event_queue_disconnect_from_shm(piga_clients_map_item_get_queue(&map->items[i]));
                
                // Remove the item from the map.
                map->items[i].queue = 0;
                map->items[i].shm_key = 0;
            }
        }
    }
}
piga_status piga_clients_map_add_from_ev(piga_clients_map* map, piga_event_consumer_registered* ev)
{
    char *buffer = piga_event_consumer_registered_get_namec(ev);
    
    piga_status status = piga_clients_map_add(
        map, 
        piga_event_consumer_registered_get_shm_key(ev),
        buffer,
        PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH
    );
    
    piga_event_consumer_registered_name_free(buffer);
    
    return status;
}
piga_status piga_clients_map_remove_from_ev(piga_clients_map* map, piga_event_consumer_unregistered* ev)
{
    return piga_clients_map_remove(
        map,
        piga_event_consumer_unregistered_get_shm_key(ev)
    );
}
void piga_clients_map_push_event(piga_clients_map* map, piga_event* ev)
{
    for(size_t i = 0; i < PIGA_CLIENTS_MAP_ITEM_NUMBER; ++i) {
        if(map->items[i].queue != 0) {
            piga_clients_map_item_push_event(&map->items[i], ev);
        }
    }
}
