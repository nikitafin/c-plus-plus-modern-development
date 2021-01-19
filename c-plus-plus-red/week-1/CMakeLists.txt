cmake_minimum_required(VERSION 3.16)
project(week_1)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS_PART1 "-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-not-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.log/log.cpp)
set(s-2 2.comparator-generator/comparator-generator.cpp)
set(s-3 3.update-field/update_field.cpp)
set(s-4 4.bad-macros/bad.cpp)
set(s-5 5.unique-token/uniq_id.cpp)
set(s-6 6.table/table.cpp)
set(s-7 7.dequeue/main.cpp 7.dequeue/deque.hpp)

set(current ${s-7})

#get_filename_component(name ${current} NAME_WLE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)

add_executable(week_1 ${current})

#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name}.out)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME a)
include_directories(../../stuff)