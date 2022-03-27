project(wxformbuilder-tests)
cmake_minimum_required(VERSION 3.20)

if (WIN32)
    add_link_options(-mwindows)
endif ()

set(wxWidgets_ROOT_DIR ${WX_PATH})
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(${CMAKE_SOURCE_DIR})
add_executable(wxformbuilder-test
        main.cpp
        ui/wx_gui.cpp
        ui_implementation/main_frame_implementation.cpp
        )

set_property(TARGET wxformbuilder-test PROPERTY CXX_STANDARD 17)

target_link_libraries(wxformbuilder-test ${wxWidgets_LIBRARIES})
