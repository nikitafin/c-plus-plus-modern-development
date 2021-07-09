cmake_minimum_required(VERSION 3.17)
project(week_4)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS_PART1 "-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-not-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.sportsman/sportsman.cc)
set(s-2 2.stack-vector/stack_vector.cpp)
set(s-3 3.translator/translator.cpp)
set(s-4 4.airport-counter/airport-counter.cpp)
set(s-5 5.basic-text-editor/text_editor.cpp)
set(s-6 6.server-stats/stats.cpp)
set(s-6-add 6.server-stats/server_stats.cpp 6.server-stats/stats.h 6.server-stats/http_request.h)

set(current ${s-6})
set(inc ${s-6-add})

get_filename_component(name ${current} NAME_WLE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)

add_executable(week_4 ${current} ${inc})

if (${WIN32})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name}.1)
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${name}.out)
endif ()
include_directories(../../stuff)
