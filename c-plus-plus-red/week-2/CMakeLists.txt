cmake_minimum_required(VERSION 3.17)
project(week_2)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS_PART1 "-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-not-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.sort-students/sort_students.cpp 1.sort-students/student.h)
set(s-2 2.learner/learner.cpp)
set(s-3 3.express-routing/slow.cpp)
set(s-4 4.ebook/slow.cpp)
set(s-5 5.hotel-reservation-system/hotel.cpp)

set(current ${s-5})

#set(name "bin")
get_filename_component(name ${current} NAME_WLE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)

add_executable(week_2 ${current})

if (${WIN32})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name})
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name}.out)
endif ()
include_directories(../../stuff)