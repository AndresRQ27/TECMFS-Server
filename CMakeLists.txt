cmake_minimum_required(VERSION 3.7)
project(TECMFS_Server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(TECMFS_Server ${SOURCE_FILES})