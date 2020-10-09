#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include "days.h"
#include "intcode.h"

namespace day5 {
    void run(aoc::aoc_output &out) {
        std::ifstream inputfile("input/day5.txt");
        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            out.return_error("Unable to open input/day5.txt");
            return;
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
        out.print_trivia("AC Unit Output", ss.str());
        if (output.empty()) {
            out.print_result("Part one", "Diagnostic Code", "<!>", "13210611");
        } else {
            out.print_result("Part one", "Diagnostic Code", output[output.size() - 1], 13210611);
        }

        computer = aoc::IntcodeComputer(&program);
        output = computer.run({5});
        ss = std::stringstream();
        for (size_t i = 0; i < output.size(); i++) {
            if (i != 0)
                ss << ",";
            ss << output[i];
        }
        out.print_trivia("Thermal Radiator Output", ss.str());
        if (output.empty()) {
            out.print_result("Part two", "Diagnostic Code", "<!>", "584126");
        } else {
            out.print_result("Part two", "Diagnostic Code", output[output.size() - 1], 584126);
        }
    }
}
