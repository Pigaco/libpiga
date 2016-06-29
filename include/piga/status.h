#ifndef PIGA_ERROR_H_INCLUDED
#define PIGA_ERROR_H_INCLUDED
    
#ifdef __cplusplus
extern "C"
{
#endif
    
typedef enum 
{
    PIGA_STATUS_OK = 0,
    PIGA_ERROR_HOST_HAS_NO_CONFIG = -1,
    PIGA_ERROR_COULD_NOT_OPEN_SHARED_MEMORY = -2,
    PIGA_ERROR_COULD_NOT_ATTACH_SHARED_MEMORY = -3,
    PIGA_ERROR_COULD_NOT_DETACH_SHARED_MEMORY = -4,
    PIGA_ERROR_EVENT_TEXT_INPUT_TEXT_TOO_LONG = -5,
    PIGA_ERROR_EMPTY_QUEUE = -6,
    PIGA_ERROR_INVALID_PLAYER_ID = -7,
    PIGA_ERROR_SHMSIZE_INVALID = -8,
} piga_status;

const char* piga_status_what(piga_status status);

const char* piga_errno_what();

#ifdef __cplusplus
}
#endif

#endif