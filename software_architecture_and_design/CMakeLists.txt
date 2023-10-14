cmake_minimum_required(VERSION 3.10)

# set the project name
project(Arch)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include the subdirectories
add_subdirectory(Client)
add_subdirectory(Monitor)
add_subdirectory(Server)

# add subdirectory
add_subdirectory(helpers)
target_include_directories(Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../helpers)
target_include_directories(Monitor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../helpers)
target_include_directories(Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../helpers)