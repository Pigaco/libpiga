project(Libpiga)
cmake_minimum_required(VERSION 3.0.1)

include(GenerateExportHeader)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Library Version
set(PIGA_VERSION_MAJOR "0" CACHE STRING "Major-Version")
set(PIGA_VERSION_MINOR "9" CACHE STRING "Minor-Version")
set(PIGA_VERSION_PATCH "5" CACHE STRING "Patch-Version")
set(PIGA_VERSION_TWEAK "0" CACHE STRING "Tweak-Version")
set(PIGA_VERSION_BUILD "0" CACHE STRING "Build")
set(PIGA_VERSION ${PIGA_VERSION_MAJOR}.${PIGA_VERSION_MINOR}.${PIGA_VERSION_PATCH}.${PIGA_VERSION_TWEAK}:${PIGA_VERSION_BUILD})

# Subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_library(piga_common SHARED ${COMMON_HDRS} ${COMMON_SRCS})
target_include_directories(piga_common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/server)
add_library(piga_server SHARED ${SERVER_HDRS} ${SERVER_SRCS})
target_include_directories(piga_server PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(piga_server piga_common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/client)
add_library(piga_client SHARED ${CLIENT_HDRS} ${CLIENT_SRCS})
target_include_directories(piga_client PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(piga_client piga_common)

# C-Standard 
set_property(TARGET piga_common PROPERTY COMPILE_FLAGS "-std=gnu99")
set_property(TARGET piga_client PROPERTY COMPILE_FLAGS "-std=gnu99")
set_property(TARGET piga_server PROPERTY COMPILE_FLAGS "-std=gnu99")

# SWIG
find_package(SWIG)

find_package(Lua)

if(${SWIG_FOUND})
    include(${SWIG_USE_FILE})
    if(${LUA_FOUND})
        SWIG_ADD_MODULE(piga_common_lua lua ${CMAKE_CURRENT_SOURCE_DIR}/swig/piga_common.i)
        SWIG_ADD_MODULE(piga_client_lua lua ${CMAKE_CURRENT_SOURCE_DIR}/swig/piga_client.i)
        SWIG_ADD_MODULE(piga_server_lua lua ${CMAKE_CURRENT_SOURCE_DIR}/swig/piga_server.i)
        SWIG_LINK_LIBRARIES(piga_common_lua piga_common)
        SWIG_LINK_LIBRARIES(piga_client_lua piga_client)
        SWIG_LINK_LIBRARIES(piga_server_lua piga_server)
        
        # Include directories for SWIG modules.
        target_include_directories(piga_common_lua PRIVATE ${LUA_INCLUDE_DIR})
        target_include_directories(piga_client_lua PRIVATE ${LUA_INCLUDE_DIR})
        target_include_directories(piga_server_lua PRIVATE ${LUA_INCLUDE_DIR})
    endif()
endif()

# Config.h
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/piga/config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/piga/config.h)

# CMake logic to export the target and make it findable by other
# projects.
generate_export_header(piga_common)
generate_export_header(piga_server)
generate_export_header(piga_client)

set_property(TARGET piga_common PROPERTY VESION ${PIGA_VERSION})
set_property(TARGET piga_common PROPERTY SOVERSION ${PIGA_VERSION_MAJOR})
set_property(TARGET piga_common PROPERTY
    INTERFACE_piga_common_MAJOR_VERSION ${PIGA_VERSION_MAJOR})
set_property(TARGET piga_client PROPERTY VESION ${PIGA_VERSION})
set_property(TARGET piga_client PROPERTY SOVERSION ${PIGA_VERSION_MAJOR})
set_property(TARGET piga_client PROPERTY
    INTERFACE_piga_client_MAJOR_VERSION ${PIGA_VERSION_MAJOR})
set_property(TARGET piga_server PROPERTY VESION ${PIGA_VERSION})
set_property(TARGET piga_server PROPERTY SOVERSION ${PIGA_VERSION_MAJOR})
set_property(TARGET piga_server PROPERTY
    INTERFACE_piga_server_MAJOR_VERSION ${PIGA_VERSION_MAJOR})

include(GNUInstallDirs)

install(TARGETS piga_common piga_server piga_client EXPORT PigaTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/piga
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/PigaConfigVersion.cmake"
  VERSION ${PIGA_VERSION}
  COMPATIBILITY AnyNewerVersion
)
configure_file(${CMAKE_MODULE_PATH}/PigaConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/PigaConfig.cmake"
  COPYONLY
)

set(ConfigPackageLocation lib/Piga/)

install(EXPORT PigaTargets
  FILE
    PigaTargets.cmake
  NAMESPACE
    Upstream::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/PigaConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/PigaConfig.cmake"
  DESTINATION
    ${ConfigPackageLocation}
)

# Install Lua files generated by SWIG
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/piga_client_lua.so)
	file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/piga_client_lua.so ${CMAKE_CURRENT_BINARY_DIR}/piga_client.so)
	file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/piga_server_lua.so ${CMAKE_CURRENT_BINARY_DIR}/piga_server.so)
	file(RENAME ${CMAKE_CURRENT_BINARY_DIR}/piga_common_lua.so ${CMAKE_CURRENT_BINARY_DIR}/piga_common.so)
endif()

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/piga_client.so)
    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/piga_client.so
            ${CMAKE_CURRENT_BINARY_DIR}/piga_server.so
            ${CMAKE_CURRENT_BINARY_DIR}/piga_common.so
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}/
    )
endif()

# Unit Tests
# Tests are written in C++ to make testing easier.

find_package(Boost COMPONENTS system unit_test_framework)

enable_testing()

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
set(CTEST_OUTPUT_ON_FAILURE 1)

set(ENV{BOOST_TEST_LOG_LEVEL} "all")

find_package(Threads)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A library which implements the pigaco IPC system for the piga console.")
set(CPACK_PACKAGE_VENDOR "Pigaco")
set(CPACK_PACKAGE_VERSION_MAJOR ${PIGA_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PIGA_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PIGA_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PIGA_VERSION_TWEAK})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "http://pigaco.net/pages/libpiga.html")
set(CPACK_DEBIAN_PACKAGE_DEPENDS)
set(CPACK_PACKAGE_NAME "piga-libpiga")
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Max Heisinger <mail@maximaximal.com>")
include(CPack)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    add_executable(${testName} ${testSrc})

    target_link_libraries(${testName} piga_server piga_client piga_common ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    target_include_directories(${testName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    set_target_properties(${testName} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/testBin)

    target_compile_definitions(${testName} PUBLIC
        -DBOOST_TEST_DYN_LINK)

    add_test(NAME ${testName}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testBin
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testBin/${testName} )

    set_property(TARGET ${testName} PROPERTY COMPILE_FLAGS "-std=c++11")
endforeach(testSrc)
