cmake_minimum_required(VERSION 3.10)

# set the project name
project(Server)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Server AppServerMain.cpp AppServer.cpp)

# include directories
include_directories(${PROJECT_SOURCE_DIR})

# add subdirectory
add_subdirectory(helpers)
target_link_libraries(Server helpers_server)
