cmake_minimum_required(VERSION 3.21)
project(c-plus-plus-modern-development)


set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 20)

include_directories(stuff)
if (UNIX)
    set(CMAKE_C_COMPILER /usr/bin/gcc-10)
    set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond  -Wextra-semi -Wfloat-equal -Wnon-virtual-dtor -Wsign-conversion")
endif ()
if(WIN32)
    
endif ()
add_subdirectory(c-plus-plus-red)