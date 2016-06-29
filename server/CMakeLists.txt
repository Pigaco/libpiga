set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(HDRS
    ${HDR}/host.h
    ${HDR}/host_config.h
)
set(SRCS
    ${SRC}/host.c
    ${SRC}/host_config.c
)

add_library(piga_server SHARED ${HDRS} ${SRCS})
target_include_directories(piga_server PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(piga_server piga_common)