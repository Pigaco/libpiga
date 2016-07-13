#include <stdlib.h>
#include <string.h>
#include <piga/internal/piga_event_consumer_unregistered_struct.h>

void piga_event_consumer_unregistered_get_name(piga_event_consumer_unregistered *ev, char *buffer)
{
    memcpy(buffer, ev->name, PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH);
}
char *piga_event_consumer_unregistered_get_namec(piga_event_consumer_unregistered *ev)
{
    char *buffer = malloc(PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH);
    piga_event_consumer_unregistered_get_name(ev, buffer);
    return buffer;
}
void piga_event_consumer_unregistered_name_free(char *buffer)
{
    free(buffer);
}
int piga_event_consumer_unregistered_get_shm_key(piga_event_consumer_unregistered* ev)
{
    return ev->shm_key;
}
void piga_event_consumer_unregistered_set_shm_key(piga_event_consumer_unregistered* ev, int shm_key)
{
    ev->shm_key = shm_key;
}