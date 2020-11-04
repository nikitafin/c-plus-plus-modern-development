cmake_minimum_required(VERSION 3.17)
project(week-4)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS_PART1 "-Ofast -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-op-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.lecture-title.cpp)
set(s-2 2.class-function.cpp)
set(s-3 3.class-function-2.cpp)
set(s-4 4.working-with-files.cpp)
set(s-5 5.conclusion-with-precision.cpp)
set(s-6 6.reading-and-dumping-a-table.cpp)

set(current ${s-6})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins/${current})
add_executable(week-4 ${current})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${current})
