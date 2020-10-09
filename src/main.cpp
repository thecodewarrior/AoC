#include "aoc_utils.h"
#include "aoc_output.h"
#include "days.h"
#include <iostream>
#include <sstream>
#include <utility>
#include <main.h>

int main(int argc, char **argv) {
    std::vector<void(*)(aoc::aoc_output &)> days{
            day1::run,
            day2::run,
            day3::run,
            day4::run,
            day5::run,
            day6::run,
    };

    for (int i = 1; i < argc; i++) {
        int day = std::stoi(argv[i]);
        if (day <= 0 || day > days.size()) {
            std::cerr << "Day " << day << " is not in range [1, " << days.size() << "]" << std::endl;
        } else {
            run_day(day, days[day - 1]);
        }
    }
    if (argc == 1) {
        for (int day = 0; day < days.size(); day++) {
            run_day(day + 1, days[day]);
        }
    }

    return 0;
}


void run_day(int day, void(*function)(aoc::aoc_output &)) {
    aoc::aoc_output output;
    output.print_header(std::to_string(day));
    function(output);
    output.print_footer();
}
