#include <stdlib.h>
#include <string.h>
#include <piga/internal/piga_event_app_installed_struct.h>

void piga_event_app_installed_get_name(piga_event_app_installed *ev, char *buffer)
{
    memcpy(buffer, ev->app_name, PIGA_EVENT_APP_INSTALLED_NAME_LENGTH);
}
char *piga_event_app_installed_get_namec(piga_event_app_installed *ev)
{
    char *buffer = malloc(PIGA_EVENT_APP_INSTALLED_NAME_LENGTH);
    piga_event_app_installed_get_name(ev, buffer);
    return buffer;
}
void piga_event_app_installed_free_name(char *name)
{
    free(name);
}
void piga_event_app_installed_set_name(piga_event_app_installed* ev, const char* name, int length)
{
    memcpy(ev->app_name, name, length);
}