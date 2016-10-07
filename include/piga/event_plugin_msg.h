#ifndef PIGA_EVENT_PLUGIN_MSG_H_INCLUDED
#define PIGA_EVENT_PLUGIN_MSG_H_INCLUDED

typedef struct piga_event_plugin_msg piga_event_plugin_msg;

/**
 * @brief The size (in bytes) of the binary/8bit char block inside the msg.
 */
#define PIGA_EVENT_PLUGIN_MSG_BLOBSIZE 70

/**
 * @brief Receives the type of the plugin msg. This is used to differentiate
 * between plugins and their additions to the libpiga IPC bus.
 */
int piga_event_plugin_msg_get_type(const piga_event_plugin_msg *msg);
void piga_event_plugin_msg_set_type(piga_event_plugin_msg *msg, int type);

/**
 * @brief Sets the binary blob of the specified msg. The data will be copied.
 */
void piga_event_plugin_msg_set_blob(piga_event_plugin_msg *msg, const char *blob);
/**
 * @brief Gets the binary blob of the specified msg. The data will be copied.
 * 
 * If you want to access the binary blob directly without copying it, you must
 * include the internal/piga_event_plugin_msg_struct.h file to get the 
 * definition for the function 
 * atomic_char* piga_event_plugin_msg_get_blob(piga_event_plugin_msg*) .
 * This is to provide a bit more memory safety using the stdatomic types. 
 */
void piga_event_plugin_msg_copy_blob(piga_event_plugin_msg *msg, char *blob);

#endif
