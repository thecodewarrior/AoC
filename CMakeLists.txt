cmake_minimum_required(VERSION 3.17)
project(AoC)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
find_package(fmt REQUIRED)

add_executable(AoC
        include/aoc_utils.h
        include/days.h
        src/aoc_utils.cpp
        src/day1.cpp
        src/day2.cpp
        src/day3.cpp
        src/main.cpp src/day4.cpp include/main.h src/day5.cpp)

target_link_libraries(AoC PRIVATE fmt::fmt)