cmake_minimum_required(VERSION 3.17)
project(week_3)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS_PART1 "-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-not-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.object-pool/object_pool.cpp)

set(current ${s-1})

get_filename_component(name ${current} NAME_WLE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)


add_executable(week_3 ${current})

if (${WIN32})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name})
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name}.out)
endif ()
include_directories(../../stuff)