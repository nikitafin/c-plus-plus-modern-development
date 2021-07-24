cmake_minimum_required(VERSION 3.19)
project(learner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "/EHsc /Od /I /Zi /JMC /sdl /TP /W4 /std:c++17")

add_executable(learner learner.cpp)

include_directories(../../../stuff)
