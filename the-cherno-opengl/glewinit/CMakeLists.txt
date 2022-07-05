cmake_minimum_required(VERSION 3.22)
project(glewinit)

set(CMAKE_CXX_STANDARD 20)

# OpenGL
find_package(OpenGL)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW::GLEW)
