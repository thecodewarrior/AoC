cmake_minimum_required(VERSION 3.17)
project(AoC)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(AoC
        include/aoc_utils.h
        include/days.h
        src/aoc_utils.cpp
        src/day1.cpp
        src/day2.cpp
        src/day3.cpp
        src/main.cpp)
