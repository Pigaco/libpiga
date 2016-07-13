set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(SEVER_HDRS
    ${HDR}/host.h
    ${HDR}/host_config.h
    ${HDR}/clients_map.h
    PARENT_SCOPE)
set(SERVER_SRCS
    ${SRC}/host.c
    ${SRC}/host_config.c
    ${SRC}/clients_map.c
    PARENT_SCOPE)

