#ifndef PIGA_INTERNAL_EVENT_REQUEST_RESTART_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_REQUEST_RESTART_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_request_restart.h>
#include <piga/event_app_installed.h>

struct piga_event_request_restart {
    atomic_char app_name[PIGA_EVENT_APP_INSTALLED_NAME_LENGTH];
    atomic_char flags;
};

#endif
