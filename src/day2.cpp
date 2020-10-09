#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "days.h"
#include "intcode.h"

namespace day2 {
    int run_program(aoc::IntcodeProgram *program, int noun, int verb);

    std::pair<int, int> find_program(aoc::IntcodeProgram *program, int target);

    void run(aoc::aoc_output &out) {
        std::ifstream inputfile("input/day2.txt");

        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            out.return_error("Unable to open input/day2.txt");
            return;
        }
        aoc::IntcodeProgram program(&inputfile);
        inputfile.close();

        out.print_trivia("Program length", program.program_length());

        out.print_result("Part one", "1202 result", run_program(&program, 12, 2), 3790689);

        auto search_result = find_program(&program, 19690720);
        out.print_result("Part two", "Search result", 100 * search_result.first + search_result.second, 6533);
    }

    int run_program(aoc::IntcodeProgram *program, int noun, int verb) {
        aoc::IntcodeComputer computer(program);

        computer[1] = noun;
        computer[2] = verb;

        computer.run(std::vector<int>());

        return computer[0];
    }

    std::pair<int, int> find_program(aoc::IntcodeProgram *program, int target) {
        for (int noun = 0; noun < 100; noun++) {
            for (int verb = 0; verb < 100; verb++) {
                if (run_program(program, noun, verb) == target) {
                    return std::pair<int, int>(noun, verb);
                }
            }
        }
        return std::pair<int, int>(-1, -1);
    }
} // namespace day2