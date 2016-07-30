#ifndef PIGA_EVENT_REQUEST_RESTART_H_INCLUDED
#define PIGA_EVENT_REQUEST_RESTART_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct piga_event_request_restart piga_event_request_restart;

typedef enum {
    PIGA_EVENT_REQUEST_RESTART_FLAG_DEBUG = 1 << 0,
} piga_event_restart_flags;

void piga_event_request_restart_set_flags(piga_event_request_restart *restart, char flags);
char piga_event_request_restart_get_flags(piga_event_request_restart *restart);

void piga_event_request_restart_set_name(piga_event_request_restart *restart, const char* name, int length);
void piga_event_request_restart_get_name(piga_event_request_restart *restart, char *buffer);
char* piga_event_request_restart_get_name_create(piga_event_request_restart *restart);
void piga_event_request_restart_free_name(char *buffer);

#ifdef __cplusplus
}
#endif

#endif
