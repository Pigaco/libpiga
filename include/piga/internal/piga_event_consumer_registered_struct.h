#ifndef PIGA_INTERNAL_EVENT_CONSUMER_REGISTERED_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_CONSUMER_REGISTERED_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_consumer_registered.h>

struct piga_event_consumer_registered {
    atomic_char name[PIGA_EVENT_CONSUMER_REGISTERED_NAME_LENGTH];
    atomic_int shm_key;
};

#endif
