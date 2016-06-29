#include <piga/shared_memory.h>
#include <piga/internal/piga_event_text_input_queue_struct.h>
#include <piga/internal/piga_player_struct.h>
#include <stddef.h>
#include <stdlib.h>

void piga_shared_memory_map(piga_shared_memory* mem, void* start, short player_count)
{
    mem->start = start;
    
    // The event_text_input_queue is after the players.
    mem->event_text_input_queue = start + sizeof(piga_player) * player_count;
    
    if(mem->players)
        free(mem->players);
    
    mem->players = malloc(sizeof(piga_player*) * player_count);
    
    for(size_t i = 0; i < player_count; ++i)
        mem->players[i] = start + i * sizeof(piga_player);
}
void piga_shared_memory_free_players(piga_shared_memory* mem)
{
    if(mem->players)
        free(mem->players);
}