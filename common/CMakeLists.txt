set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HDR ${CMAKE_CURRENT_SOURCE_DIR}/../include/piga)

set(HDRS
    ${HDR}/status.h
    ${HDR}/event_game_input.h
    ${HDR}/event_text_input.h
    ${HDR}/event_queue.h
    ${HDR}/shared_memory.h
    ${HDR}/player.h
    ${HDR}/player_role.h
    ${HDR}/player_status.h
    ${HDR}/player_inputs.h
    ${HDR}/event.h
    ${HDR}/event_app_installed.h
    ${HDR}/event_request_keyboard.h
    ${HDR}/event_player_joined.h
    ${HDR}/event_player_left.h
    ${HDR}/event_consumer_registered.h
    ${HDR}/event_consumer_unregistered.h

    ${HDR}/internal/piga_event_app_installed_struct.h
    ${HDR}/internal/piga_event_consumer_registered_struct.h
    ${HDR}/internal/piga_event_player_joined_struct.h
    ${HDR}/internal/piga_event_player_left_struct.h
    ${HDR}/internal/piga_event_queue_struct.h
    ${HDR}/internal/piga_event_request_keyboard_struct.h
    ${HDR}/internal/piga_event_request_restart_struct.h
    ${HDR}/internal/piga_event_struct.h
    ${HDR}/internal/piga_event_text_input_struct.h
    ${HDR}/internal/piga_player_inputs_struct.h
    ${HDR}/internal/piga_player_struct.h
)
set(SRCS
    ${SRC}/status.c
    ${SRC}/event_game_input.c
    ${SRC}/event_text_input.c
    ${SRC}/event_queue.c
    ${SRC}/shared_memory.c
    ${SRC}/player.c
    ${SRC}/player_role.c
    ${SRC}/player_status.c
    ${SRC}/player_inputs.c
    ${SRC}/event.c
    ${SRC}/event_app_installed.c
    ${SRC}/event_request_keyboard.c
    ${SRC}/event_request_restart.c
    ${SRC}/event_player_joined.c
    ${SRC}/event_player_left.c
    ${SRC}/event_consumer_registered.c
    ${SRC}/event_consumer_unregistered.c
)

add_library(piga_common SHARED ${HDRS} ${SRCS})
target_include_directories(piga_common PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

 
