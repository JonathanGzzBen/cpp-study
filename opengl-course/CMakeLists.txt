cmake_minimum_required(VERSION 3.22.3)
project(opengl-course)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# GLFW
add_subdirectory(libs/GLFW)
include_directories(libs/GLFW/include)

# GLEW
add_subdirectory(libs/GLEW/build/cmake)
include_directories(libs/GLEW/include)

add_executable(main src/main.c)
target_link_libraries(main glfw opengl32 glew_s)
