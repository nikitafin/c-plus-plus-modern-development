project(object-pool)

if (WIN32)
    set(CMAKE_CXX_FLAGS "/EHsc /Od /I /Zi /JMC /sdl /TP /W4 /std:c++17")
endif ()

add_executable(object-pool "object-pool.cpp")
include_directories(../../../stuff)
