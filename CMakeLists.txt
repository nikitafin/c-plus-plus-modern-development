# FIXME(Nikita): version + cfg for all targets
cmake_minimum_required(VERSION 3.21)
project(c-plus-plus-modern-development)

set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
if(UNIX)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()

# FIXME(Nikita): into lib
include_directories(stuff)

# FIXME(Nikita): flags for all platrforms
if(UNIX)
  message("GCC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
  # set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wcast-qual -Wconversion
  # -Wduplicated-branches -Wduplicated-cond  -Wextra-semi -Wfloat-equal
  # -Wnon-virtual-dtor -Wsign-conversion" )
endif()

# FIXME(Nikita): fix old project conf+build
# add_subdirectory(c-plus-plus-red)
add_subdirectory(c-plus-plus-brown)
