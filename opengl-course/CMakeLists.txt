cmake_minimum_required(VERSION 3.22.3)
project(opengl-course)

# GLFW
find_package(glfw3 3.3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(main src/main.c)
target_link_libraries(main glfw ${GLFW_LIBRARIES} opengl32 GLEW::GLEW)
