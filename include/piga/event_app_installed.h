#ifndef PIGA_EVENT_APP_INSTALLED_H_INCLUDED
#define PIGA_EVENT_APP_INSTALLED_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include <piga/status.h>

typedef struct piga_event_app_installed piga_event_app_installed;

#define PIGA_EVENT_APP_INSTALLED_NAME_LENGTH 80

void piga_event_app_installed_get_name(piga_event_app_installed *ev, char *buffer);
char* piga_event_app_installed_get_namec(piga_event_app_installed *ev);
void piga_event_app_installed_free_name(char *name);
void piga_event_app_installed_set_name(piga_event_app_installed *ev, const char *name, int length);

#ifdef __cplusplus
}
#endif

#endif
