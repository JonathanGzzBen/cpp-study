cmake_minimum_required(VERSION 3.0)

project(tboxes VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

message("Building Makefile for ${PROJECT_NAME}")

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(UNIX)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(WIN32)
    message("This is a Windows System")
endif()

# or use MATCHES to see if actual system name 
# Darwin is Apple's system name
if(${CMAKE_SYSTEM_NAME} MATCHES Darwin)
    message("This is a ${CMAKE_SYSTEM_NAME} system")
elseif(${CMAKE_SYSTEM_NAME} MATCHES Windows)
    message("This is a Windows System")
endif()

add_definitions(-DVERSION_NAME="v1.0.0")

include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES src/main.cpp
            src/config.cpp
            src/toybox.cpp
            src/triangle.cpp
            src/square.cpp
            src/i_figure.cpp
            src/i_printable.cpp
            src/invalid_measures_exception.cpp
            src/toybox_not_found.cpp
            src/config.h
            src/toybox.h
            src/triangle.h
            src/square.h
            src/i_figure.h
            src/i_printable.h
            src/invalid_measures_exception.h
            src/toybox_not_found.h
            )


add_executable(${PROJECT_NAME} ${SOURCES})
