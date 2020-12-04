#include "days.h"
#include <aoc/Day.h>
#include <aoc/Printer.h>
#include <iostream>
#include <main.h>

int main(int argc, char **argv) {
    aoc::DayContext ctx{"2020", "", "input"};
    std::vector<aoc::Day *> days{
        new Day1(ctx.day("1")),
        new Day2(ctx.day("2")),
        new Day3(ctx.day("3")),
    };

    for (int i = 1; i < argc; i++) {
        int day = std::stoi(argv[i]);
        if (day < 1 || day > days.size()) {
            std::cerr << "Day " << day << " is not in range [1, " << days.size() << "]" << std::endl;
        } else {
            days[day - 1]->run();
        }
    }
    if (argc == 1) {
        for (auto &day : days) {
            day->run();
        }
    }

    for (auto &day : days) {
        delete day;
    }

    return 0;
}
