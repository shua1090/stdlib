cmake_minimum_required(VERSION 3.20)
project(stdlib)

set(CMAKE_CXX_STANDARD 11)

add_executable(stdlib src/main.cpp)
include_directories(include)
