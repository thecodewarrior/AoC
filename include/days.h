#ifndef _DAYS_H
#define _DAYS_H
#include "aoc_utils.h"

namespace day1
{
    int run();
} // namespace day1

namespace day2
{
    int run();
    int run_program(aoc::IntcodeProgram *program, int noun, int verb);
    std::pair<int, int> find_program(aoc::IntcodeProgram *program, int target);
} // namespace day2

#endif