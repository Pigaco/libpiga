#include <piga/status.h>

const char* piga_status_what(piga_status status)
{
    switch(status)
    {
        case PIGA_STATUS_OK:
            return "PIGA_STATUS_OK: Indicates success";
        case PIGA_ERROR_HOST_HAS_NO_CONFIG:
            return "PIGA_ERROR_HOST_HAS_NO_CONFIG: The host tried to be started up has no config!";
        case PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY:
            return "PIGA_ERROR_HOST_COULD_NOT_OPEN_SHARED_MEMORY: Could not open/create its shared memory!";
        case PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY:
            return "PIGA_ERROR_HOST_COULD_NOT_ATTACH_SHARED_MEMORY: Could not attach the shared memory segment into an address of the process!";
        case PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY:
            return "PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY: Could not detach the shared memory!";
        case PIGA_ERROR_EVENT_TEXT_INPUT_TEXT_TOO_LONG:
            return "PIGA_ERROR_EVENT_TEXT_INPUT_TEXT_TOO_LONG: The text input is too long!";
        case PIGA_ERROR_EMPTY_QUEUE:
            return "PIGA_ERROR_EMPTY_QUEUE: The queue is empty, no element can be returned.";
        case PIGA_ERROR_INVALID_PLAYER_ID:
            return "PIGA_ERROR_INVALID_PLAYER_ID: The player id was invalid because it "
            "was either smaller than 0 or greater than the player count defined in the host config.";
    }
    return "Error not found.";
}