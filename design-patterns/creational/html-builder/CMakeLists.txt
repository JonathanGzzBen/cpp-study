cmake_minimum_required(VERSION 3.11)

project(html_builder)


add_executable(${PROJECT_NAME} src/main.cpp src/HtmlElement.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)