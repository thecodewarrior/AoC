cmake_minimum_required(VERSION 3.17)
project(AoC)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt REQUIRED)

find_package(Boost 1.73.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)
add_executable(AoC
        include/days.h
        src/Day1.cpp
        src/Day2.cpp
        src/Day3.cpp
        src/main.cpp src/Day4.cpp include/main.h src/Day5.cpp src/Day6.cpp src/intcode.cpp include/intcode.h src/aoc/Printer.cpp include/aoc/Printer.h src/aoc/Day.cpp include/aoc/Day.h include/utils.h src/utils.cpp include/Day1.h include/Day2.h include/Day3.h include/Day4.h include/Day6.h include/Day5.h)

target_link_libraries(AoC PRIVATE fmt::fmt ${Boost_LIBRARIES})