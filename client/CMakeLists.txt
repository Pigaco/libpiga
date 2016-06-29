set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(HDRS
    ${HDR}/client.h
    ${HDR}/client_config.h
)
set(SRCS
    ${SRC}/client.c
    ${SRC}/client_config.c
)

add_library(piga_client SHARED ${HDRS} ${SRCS})
target_include_directories(piga_client PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(piga_client piga_common)