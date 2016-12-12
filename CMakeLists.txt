cmake_minimum_required(VERSION 3.6)
project(GarbageCollector)

include_directories()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(GarbageCollector ${SOURCE_FILES})