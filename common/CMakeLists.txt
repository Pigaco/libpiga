set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(HDRS
    ${HDR}/status.h
    ${HDR}/event_game_input.h
    ${HDR}/event_text_input.h
    ${HDR}/event_text_input_queue.h
    ${HDR}/shared_memory.h
    ${HDR}/player.h
    ${HDR}/player_role.h
    ${HDR}/player_status.h
    ${HDR}/player_inputs.h
)
set(SRCS
    ${SRC}/status.c
    ${SRC}/event_game_input.c
    ${SRC}/event_text_input.c
    ${SRC}/event_text_input_queue.c
    ${SRC}/shared_memory.c
    ${SRC}/player.c
    ${SRC}/player_role.c
    ${SRC}/player_status.c
    ${SRC}/player_inputs.c
)

add_library(piga_common SHARED ${HDRS} ${SRCS})
target_include_directories(piga_common PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

 
