cmake_minimum_required(VERSION 3.11)

project(ZMQ_BASICS)

include(FetchContent)

FetchContent_Declare(
	zmq
	GIT_REPOSITORY	https://github.com/zeromq/libzmq
	GIT_TAG 		4097855ddaaa65ed7b5e8cb86d143842a594eebd
)

FetchContent_MakeAvailable(zmq)

add_library(common src/common.c)
target_link_libraries(common libzmq)


add_executable(hwserver src/hwserver.c)
add_executable(hwclient src/hwclient.c)
target_link_libraries(hwserver common)
target_link_libraries(hwclient common)
