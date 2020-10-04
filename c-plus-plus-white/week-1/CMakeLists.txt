cmake_minimum_required(VERSION 3.17)
project(week_1)

set(CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS_PART1 "-Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy")
set(CXX_FLAGS_PART2 "-Wextra-semi -Wfloat-equal -Wlogical-op-parentheses -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
set(CXX_FLAGS_PART3 "-Wsign-conversion -Wsign-promo -O3")

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_PART1} ${CXX_FLAGS_PART2} ${CXX_FLAGS_PART3}")

set(solution-1 1.a-b.cpp)
set(solution-2 2.minimal-naia-stroka.cpp)
set(solution-3 3.equation.cpp)
set(solution-4 4.division.cpp)
set(solution-5 5.calculation-of-the-cost-of-goods.cpp)
set(solution-6 6.even-nums.cpp)
set(solution-7 7.second-occurrence.cpp)
set(solution-8 8.gcd.cpp)
set(solution-9 9.binary-numbers.cpp)

add_executable(week_1 ${solution-9})