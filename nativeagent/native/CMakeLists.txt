cmake_minimum_required(VERSION 2.8)
project(nativeagent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_MAKEFILE ON)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(${JNI_INCLUDE_DIRS})
include_directories(../gen_headers/)
include_directories(share/bin/)

FILE(GLOB SRC_BIN share/bin/*.c  share/bin/*.h)
FILE(GLOB SRC_INSTRUMENT share/instrument/*.c share/instrument/*.h)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories(solaris/instrument)
    FILE(GLOB SRC_PLATFORM solaris/instrument/*.c solaris/instrument/*.h)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories(windows/instrument)
    FILE(GLOB SRC_PLATFORM windows/instrument/*.c windows/instrument/*.h)
endif()

add_library(nativeagent SHARED ${SRC_INSTRUMENT} ${SRC_PLATFORM} ${SRC_BIN} )
