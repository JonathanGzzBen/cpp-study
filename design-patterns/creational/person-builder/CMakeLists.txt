cmake_minimum_required(VERSION 3.11)

project(person_builder)

add_executable(${PROJECT_NAME} src/main.cpp src/person.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
# set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)