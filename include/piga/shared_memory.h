#ifndef PIGA_SHARED_MEMORY_H_INCLUDED
#define PIGA_SHARED_MEMORY_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <piga/event_text_input_queue.h>
#include <piga/player.h>
    
typedef struct 
{
    void *start;
    piga_event_text_input_queue *event_text_input_queue;
    piga_player **players;
} piga_shared_memory;

void piga_shared_memory_map(piga_shared_memory* mem, void* start, short int player_count);
void piga_shared_memory_free_players(piga_shared_memory *mem);

#ifdef __cplusplus
}
#endif
    
#endif