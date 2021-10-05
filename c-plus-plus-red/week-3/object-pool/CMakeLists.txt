cmake_minimum_required (VERSION 3.8)
project(object-pool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_CXX_FLAGS "/EHsc /Od /I /Zi /JMC /sdl /TP /W4 /std:c++17")

add_executable (object-pool "object-pool.cpp")
include_directories(../../../stuff)
