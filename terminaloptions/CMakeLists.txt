cmake_minimum_required(VERSION 3.0)

project(terminaloptions VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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

add_definitions(-DVERSION_NUMBER="v1.0.0")

add_executable(${PROJECT_NAME} src/main.cpp)
