cmake_minimum_required(VERSION 3.17)
project(week_2)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS_PART1 "-std=c++17 -Ofast -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-op-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
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

set(current ${s-10})

add_executable(week_2 ${current})