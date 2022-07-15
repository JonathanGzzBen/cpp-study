cmake_minimum_required(VERSION 3.22)
project(classes_refactoring)

set(CMAKE_CXX_STANDARD 20)

# OpenGL
find_package(OpenGL)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} src/main.cpp src/renderer.cpp src/vertex_buffer.cpp src/index_buffer.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL GLEW::GLEW)
