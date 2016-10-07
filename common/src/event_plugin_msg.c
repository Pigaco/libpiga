#include <string.h>
#include <piga/internal/piga_event_plugin_msg_struct.h>

int piga_event_plugin_msg_get_type(const piga_event_plugin_msg *msg)
{
     return msg->type;   
}
void piga_event_plugin_msg_set_type(piga_event_plugin_msg *msg, int type)
{
    msg->type = type;
}
void piga_event_plugin_msg_set_blob(piga_event_plugin_msg *msg, const char *blob)
{
    memcpy(msg->blob, blob, PIGA_EVENT_PLUGIN_MSG_BLOBSIZE);
}
void piga_event_plugin_msg_copy_blob(piga_event_plugin_msg *msg, char *blob)
{
    memcpy(blob, msg->blob, PIGA_EVENT_PLUGIN_MSG_BLOBSIZE);
}
