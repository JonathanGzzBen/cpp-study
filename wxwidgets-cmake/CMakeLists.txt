cmake_minimum_required(VERSION 3.11)

project(wxWidgetsCmake)

include(FetchContent)

FetchContent_Declare(
	wxWidgets
	GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
	GIT_TAG 08301b1b4ae6b54ee0f0a5dc6eb1f4468635954d
)

FetchContent_MakeAvailable(wxWidgets)

if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 src/main.cpp)

	# Manifest required on Windows, more information on:
	# https://docs.wxwidgets.org/latest/plat_msw_install.html#msw_manifest
	target_sources(${PROJECT_NAME} PRIVATE ${wxWidgets_SOURCE_DIR}/include/wx/msw/wx.rc)
else()
	add_executable(${PROJECT_NAME} src/main.cpp)
endif()

target_link_libraries(${PROJECT_NAME} wx::core wx::base wx::net)

# Use wxBUILD_SHARED = OFF to build a single .exe file
if (wxBUILD_SHARED)
	# Copy runtime required DLLs to the build directory
	add_custom_command(
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND_EXPAND_LISTS
	)
endif()
