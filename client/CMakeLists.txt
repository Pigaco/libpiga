set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(CLIENT_HDRS
    ${HDR}/client.h
    ${HDR}/client_config.h
    PARENT_SCOPE)
set(CLIENT_SRCS
    ${SRC}/client.c
    ${SRC}/client_config.c
    PARENT_SCOPE)

