cmake_minimum_required(VERSION 3.22.3)
project(opengl-course)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

add_executable(main src/main.c)
target_link_libraries(main OpenGL::GL glfw GLEW::GLEW)
