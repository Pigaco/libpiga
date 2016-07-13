#ifndef PIGA_EVENT_CONSUMER_UNREGISTERED_H_INCLUDED
#define PIGA_EVENT_CONSUMER_UNREGISTERED_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct piga_event_consumer_unregistered piga_event_consumer_unregistered;

void piga_event_consumer_unregistered_get_name(piga_event_consumer_unregistered *ev, char *buffer);
char* piga_event_consumer_unregistered_get_namec(piga_event_consumer_unregistered *ev);
void piga_event_consumer_unregistered_name_free(char *buffer);

int piga_event_consumer_unregistered_get_shm_key(piga_event_consumer_unregistered *ev);
void piga_event_consumer_unregistered_set_shm_key(piga_event_consumer_unregistered *ev, int shm_key);

#ifdef __cplusplus
}
#endif

#endif