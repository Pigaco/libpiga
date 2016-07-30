#include <piga/internal/piga_event_request_restart_struct.h>
#include <piga/event_request_restart.h>
#include <stdlib.h>
#include <string.h>
 
char piga_event_request_restart_get_flags(piga_event_request_restart* restart)
{
    return restart->flags;
}
void piga_event_request_restart_set_flags(piga_event_request_restart* restart, char flags)
{
    restart->flags = flags;
}
void piga_event_request_restart_set_name(piga_event_request_restart* restart, const char* name, int length)
{
    memcpy(restart->app_name, name, length);
}
void piga_event_request_restart_get_name(piga_event_request_restart* restart, char* buffer)
{
    memcpy(buffer, restart->app_name, PIGA_EVENT_APP_INSTALLED_NAME_LENGTH);
}
char* piga_event_request_restart_get_name_create(piga_event_request_restart* restart)
{
    char *buffer = malloc(sizeof(char) * PIGA_EVENT_APP_INSTALLED_NAME_LENGTH);
    piga_event_request_restart_get_name(restart, buffer);
    return buffer;
}
void piga_event_request_restart_free_name(char* buffer)
{
    free(buffer);
}

