cmake_minimum_required(VERSION 3.10)

# set the project name
project(Viewer)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Viewer AppViewerMain.cpp AppViewer.cpp)

# include directories
include_directories(${PROJECT_SOURCE_DIR})

if(MINGW)
    target_link_libraries(Viewer ws2_32)
endif()

# add subdirectory
add_subdirectory(helpers)
target_link_libraries(Viewer helpers_viewer)