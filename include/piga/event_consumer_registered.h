#ifndef PIGA_EVENT_CONSUMER_REGISTERED_H_INCLUDED
#define PIGA_EVENT_CONSUMER_REGISTERED_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#define PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH 80
    
typedef struct piga_event_consumer_registered piga_event_consumer_registered;

void piga_event_consumer_registered_get_name(piga_event_consumer_registered *ev, char *buffer);
char* piga_event_consumer_registered_get_namec(piga_event_consumer_registered *ev);
void piga_event_consumer_registered_name_free(char *buffer);
void piga_event_consumer_registered_set_name(piga_event_consumer_registered *ev, const char *name, int name_length);

int piga_event_consumer_registered_get_shm_key(piga_event_consumer_registered *ev);
void piga_event_consumer_registered_set_shm_key(piga_event_consumer_registered *ev, int shm_key);

#ifdef __cplusplus
}
#endif

#endif
