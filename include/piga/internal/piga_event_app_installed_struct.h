#ifndef PIGA_INTERNAL_EVENT_APP_INSTALLED_STRUCT_H_INCLUDED
#define PIGA_INTERNAL_EVENT_APP_INSTALLED_STRUCT_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_app_installed.h>

struct piga_event_app_installed {
    atomic_char app_name[PIGA_EVENT_APP_INSTALLED_NAME_LENGTH];
};

#endif
