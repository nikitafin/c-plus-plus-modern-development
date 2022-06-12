cmake_minimum_required(VERSION 3.21)
project(c-plus-plus-modern-development)

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 17)

include_directories(stuff)

if(UNIX)
  message("GCC")
  # set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wcast-qual -Wconversion
  # -Wduplicated-branches -Wduplicated-cond  -Wextra-semi -Wfloat-equal
  # -Wnon-virtual-dtor -Wsign-conversion" )
endif()

add_subdirectory(c-plus-plus-red)
