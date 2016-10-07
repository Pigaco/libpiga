#ifndef PIGA_INTERNAL_EVENT_PLUGIN_MSG_H_INCLUDED
#define PIGA_INTERNAL_EVENT_PLUGIN_MSG_H_INCLUDED

#include <stdatomic.h>
#include <piga/event_plugin_msg.h>

struct piga_event_plugin_msg {
    atomic_int type;
    atomic_char blob[PIGA_EVENT_PLUGIN_MSG_BLOBSIZE];
};

/**
 * @brief This function returns a pointer to the internal binary data blob. 
 * 
 * The size of the array is PIGA_EVENT_PLUGIN_MSG_BLOBSIZE. This can be used
 * to setup custom messages over the libpiga IPC messaging bus and to access
 * this data faster.
 */
atomic_char* piga_event_plugin_msg_get_blob(piga_event_plugin_msg *msg);

#endif
