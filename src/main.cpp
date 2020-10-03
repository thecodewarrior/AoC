#include "aoc_utils.h"
#include "days.h"
#include <cstdlib>
#include <iostream>

using namespace aoc;

int main(int argc, char *argv[])
{
    if(argc != 2) {
        std::cerr << "Program is not in the form: " << argv[0] << " <day>" << std::endl;
        return 1;
    }

    int day_count = 3;
    int (*days[])() = {
        day1::run,
        day2::run,
        day3::run
    };

    int day = atoi(argv[1]);
    if(day <= 0 || day > day_count) {
        std::cerr << "Day " << day << " is not in range [1, " << day_count << "]" << std::endl;
        return 1;
    }

    printf("\n\n/========================= Advent of Code 2019, day %-2d =========================\\\n", day);
    int exit_code = (*days[day - 1])();
    if (exit_code == 0)
    {
        printf("\\=================================== Success ===================================/\n\n");
    }
    else
    {
        printf("\\================================== Error: %2d ==================================/\n\n", exit_code);
    }

    return exit_code;
}