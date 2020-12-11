//#include "days.h"
#include "Day1.h"
#include "Day2.h"
#include "Day3.h"
#include "Day4.h"
#include "Day5.h"
#include <aoc/Day.h>
#include <aoc/Printer.h>
#include <iostream>
#include <main.h>

int main(int argc, char **argv) {
    aoc::DayContext ctx{"2020", "", "input"};
    std::vector<aoc::Day *> days{
        new Day1(ctx.day("1")), new Day2(ctx.day("2")), new Day3(ctx.day("3")),
        new Day4(ctx.day("4")), new Day5(ctx.day("5")),
    };

    for (int i = 1; i < argc; i++) {
        int day = std::stoi(argv[i]);
        if (day < 1 || day > days.size()) {
            std::cerr << "Day " << day << " is not in range [1, " << days.size() << "]" << std::endl;
        } else {
            days[day - 1]->run_day();
        }
    }
    if (argc == 1) {
        for (auto &day : days) {
            day->run_day();
        }
    }

    for (auto &day : days) {
        delete day;
    }

    return 0;
}
