project(week-5)

if (UNIX)
    set(CMAKE_C_COMPILER /usr/bin/gcc-10)
    set(CMAKE_CXX_COMPILER /usr/bin/g++-10)
endif ()

add_subdirectory(josephus_permutation)