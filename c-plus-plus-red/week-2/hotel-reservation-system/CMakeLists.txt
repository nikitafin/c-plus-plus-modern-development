cmake_minimum_required(VERSION 3.20)
project(hotel_reservation_system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "/EHsc /Od /I /Zi /JMC /sdl /TP /W4 /std:c++17 /GR")

add_executable(hotel_reservation_system main.cpp)

include_directories(../../../stuff)