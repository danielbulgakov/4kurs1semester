cmake_minimum_required(VERSION 3.10)

# set the project name
project(Arch)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include the subdirectories
add_subdirectory(Client)
add_subdirectory(Server)