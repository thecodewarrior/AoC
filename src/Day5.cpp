#include "Day5.h"
#include "intcode.h"
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

void Day5::run_day() {
    fs::ifstream inputfile(input / "day5.txt");
    if (!inputfile.is_open()) {
        AOC_ABORT("Unable to open day5.txt");
    }
    aoc::IntcodeProgram program(&inputfile);
    inputfile.close();

    aoc::IntcodeComputer computer(&program);
    std::vector<int> output = computer.run({1});

    std::stringstream ss;
    for (size_t i = 0; i < output.size(); i++) {
        if (i != 0)
            ss << ",";
        ss << output[i];
    }
    print_trivia("AC Unit Output", ss.str());
    if (output.empty()) {
        print_result("Part one", "Diagnostic Code", "<!>", "13210611");
    } else {
        print_result("Part one", "Diagnostic Code", output[output.size() - 1], 13210611);
    }

    computer = aoc::IntcodeComputer(&program);
    output = computer.run({5});
    ss = std::stringstream();
    for (size_t i = 0; i < output.size(); i++) {
        if (i != 0)
            ss << ",";
        ss << output[i];
    }
    print_trivia("Thermal Radiator Output", ss.str());
    if (output.empty()) {
        print_result("Part two", "Diagnostic Code", "<!>", "584126");
    } else {
        print_result("Part two", "Diagnostic Code", output[output.size() - 1], 584126);
    }
}
