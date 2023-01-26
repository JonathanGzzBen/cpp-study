cmake_minimum_required(VERSION 3.11)
project(opengl-course)

include(FetchContent)

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 7482de6071d21db77a7236155da44c172a7f6c9e # 3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
	glew
	URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.tgz
	SOURCE_SUBDIR build/cmake
)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # 0.9.9.8
)

FetchContent_MakeAvailable(glfw glew glm)

# OpenGL
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/mesh.cpp src/shader.cpp src/window.cpp src/camera.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
target_include_directories(${PROJECT_NAME} PRIVATE ${glew_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw glew_s glm)
