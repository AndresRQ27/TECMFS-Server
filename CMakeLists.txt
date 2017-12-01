cmake_minimum_required(VERSION 3.8)
project(TECMFS_Server)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ControllerNode.cpp ControllerNode.h TCPServer.cpp TCPServer.h json.hpp)
add_executable(TECMFS_Server ${SOURCE_FILES})