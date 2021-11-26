cmake_minimum_required(VERSION 3.10)
set(This basic_window)
project(${This} VERSION 0.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Using conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
include_directories(${CMAKE_SOURCE_DIR} ./src)

set(SOURCES
        src/main.cc
    )

set(HEADERS
    )

add_executable(${This} ${SOURCES})

conan_target_link_libraries(${This})