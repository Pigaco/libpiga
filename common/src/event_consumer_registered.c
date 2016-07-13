#include <stdlib.h>
#include <string.h>
#include <piga/internal/piga_event_consumer_registered_struct.h>

void piga_event_consumer_registered_get_name(piga_event_consumer_registered *ev, char *buffer)
{
    memcpy(buffer, ev->name, PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH);
}
char *piga_event_consumer_registered_get_namec(piga_event_consumer_registered *ev)
{
    char *buffer = malloc(PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH);
    piga_event_consumer_registered_get_name(ev, buffer);
    return buffer;
}
void piga_event_consumer_registered_name_free(char *buffer)
{
    free(buffer);
}
void piga_event_consumer_registered_set_name(piga_event_consumer_registered* ev, const char* name, int name_length)
{
    memcpy(ev->name, name, name_length);
}
int piga_event_consumer_registered_get_shm_key(piga_event_consumer_registered* ev)
{
    return ev->shm_key;
}
void piga_event_consumer_registered_set_shm_key(piga_event_consumer_registered* ev, int shm_key)
{
    ev->shm_key = shm_key;
}