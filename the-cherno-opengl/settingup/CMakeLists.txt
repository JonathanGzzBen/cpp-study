cmake_minimum_required(VERSION 3.22)
project(settingup)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL)

add_executable(settingup main.cpp)
target_link_libraries(settingup glfw OpenGL::GL)