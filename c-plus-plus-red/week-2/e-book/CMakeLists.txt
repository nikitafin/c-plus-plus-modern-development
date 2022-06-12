cmake_minimum_required(VERSION 2.19)
project(e_book)

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
  set(CMAKE_CXX_FLAGS "/EHsc /Od /I /Zi /JMC /sdl /TP /W4 /std:c++17")
endif()

add_executable(e_book e-book.cpp)

include_directories(../../../stuff)
