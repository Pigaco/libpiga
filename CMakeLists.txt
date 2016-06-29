project(Libpiga)
cmake_minimum_required(VERSION 3.0.1)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/server)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/client)


# Unit Tests
# Tests are written in C++ to make testing easier.

find_package(Boost COMPONENTS system unit_test_framework)

enable_testing()

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
set(CTEST_OUTPUT_ON_FAILURE 1)

set(ENV{BOOST_TEST_LOG_LEVEL} "all")

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    add_executable(${testName} ${testSrc})

    target_link_libraries(${testName} piga_server piga_client piga_common ${Boost_LIBRARIES} )
    
    target_include_directories(${testName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

    set_target_properties(${testName} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/testBin)
        
    target_compile_definitions(${testName} PUBLIC 
        -DBOOST_TEST_DYN_LINK)

    add_test(NAME ${testName} 
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testBin 
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testBin/${testName} )
endforeach(testSrc)