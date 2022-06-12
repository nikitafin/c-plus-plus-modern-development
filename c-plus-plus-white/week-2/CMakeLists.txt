cmake_minimum_required(VERSION 3.17)
project(week_2)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS_PART1
    "-Ofast -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy"
)
set(CXX_FLAGS_PART2
    "-Wextra-semi -Wfloat-equal -Wlogical-op-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls"
)
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(s-1 1.factorial.cpp)
set(s-2 2.is-palindrom.cpp)
set(s-3 3.palindrom-filter.cpp)
set(s-4 4.maximizer.cpp)
set(s-5 5.move-strings.cpp)
set(s-6 6.reverse.cpp)
set(s-7 7.reversed.cpp)
set(s-8 8.average-temperature.cpp)
set(s-9 9.queue.cpp)
set(s-10 10.monthly-affairs.cpp)
set(s-11 11.is-anagrams.cpp)
set(s-12 12.capitals.cpp)
set(s-13 13.bus-stops-1.cpp)
set(s-14 14.bus-stops-2.cpp)
set(s-15 15.synonyms.cpp)
set(s-16 16.bus-stops-3.cpp)

set(current ${s-10})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins/${current})

add_executable(week_2 ${current})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${current})
