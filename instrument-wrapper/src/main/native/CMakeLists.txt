cmake_minimum_required(VERSION 2.8)
project(instrument_wrapper)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_MAKEFILE ON)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(${JNI_INCLUDE_DIRS})

FILE(GLOB SOURCE *.c *.h)

add_library(instrument_wrapper SHARED ${SOURCE} )
