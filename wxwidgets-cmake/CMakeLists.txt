cmake_minimum_required(VERSION 3.11)

project(wxWidgetsCmake)

include(FetchContent)

FetchContent_Declare(
	wxWidgets
	GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
	GIT_TAG 08301b1b4ae6b54ee0f0a5dc6eb1f4468635954d
)

FetchContent_MakeAvailable(wxWidgets)

add_executable(${PROJECT_NAME} WIN32 src/main.cpp)

target_link_libraries(${PROJECT_NAME} wx::core wx::base wx::net)


if (wxBUILD_SHARED)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND_EXPAND_LISTS
	)
endif()
