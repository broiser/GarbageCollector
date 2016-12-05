cmake_minimum_required(VERSION 3.6)
project(GarbageCollector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TypeDescriptor.cpp TypeDescriptor.h)
add_executable(GarbageCollector ${SOURCE_FILES})