cmake_minimum_required(VERSION 3.27)
project(liblogger LANGUAGES C VERSION 0.0.0)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -DLOGGER")

set(SOURCE_DIRS
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
)
set(SOURCE_LIST)
foreach(SOURCE_DIR ${SOURCE_DIRS})
    file(GLOB_RECURSE RECURSE_SOURCES ${SOURCE_DIR}/*.c ${SOURCE_DIR}/*.h)
    list(APPEND SOURCE_LIST ${RECURSE_SOURCES})
endforeach()

include(cppcheck.cmake)
include(uncrustify.cmake)

include_directories(include)
set(SRCS src/Logger.c)
add_library(logger ${SRCS})
add_dependencies(logger uncrustify)

add_executable(test_Logger ${CMAKE_SOURCE_DIR}/test/test_Logger.c)
target_link_libraries(test_Logger logger)

enable_testing()
add_test(test_Logger test_Logger)
