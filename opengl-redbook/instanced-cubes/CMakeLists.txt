cmake_minimum_required(VERSION 3.20)
#cmake_minimum_required(VERSION 3.22)
project(instanced-cubes)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp libs/stb/stbi_image.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_PROJECT_NAME="${PROJECT_NAME}")
target_include_directories(${PROJECT_NAME} PRIVATE libs)

include(FetchContent)

# glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 7482de6071d21db77a7236155da44c172a7f6c9e
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# glew
FetchContent_Declare(
        glew
        URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0.zip
        SOURCE_SUBDIR build/cmake
)

# glm
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)

# Make Available
FetchContent_MakeAvailable(glfw glew glm)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glew_s OpenGL::GL)
target_include_directories(${PROJECT_NAME} PRIVATE ${glew_SOURCE_DIR}/include ${glm_SOURCE_DIR})
