#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "days.h"

namespace day5 {
    aoc::DayResult run(std::ostream &out) {
        aoc::DayResult result;

        std::ifstream inputfile("input/day5.txt");
        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            return aoc::DayResult(1);
        }
        aoc::IntcodeProgram program(&inputfile);
        inputfile.close();

        aoc::IntcodeComputer computer(&program);
        std::vector<int> output = computer.run({ 1 });

        std::stringstream ss;
        for(size_t i = 0; i < output.size(); i++) {
            if(i != 0)
                ss << ",";
            ss << output[i];
        }
        result.results.emplace_back("", true, "AC Unit Output", ss.str());
        if(output.empty()) {
            result.results.emplace_back("Part one", false, "Diagnostic Code", "<!>", "13210611");
        } else {
            result.results.emplace_back("Part one", false, "Diagnostic Code", output[output.size() - 1], 13210611);
        }

        computer = aoc::IntcodeComputer(&program);
        output = computer.run({ 5 });
        ss = std::stringstream();
        for(size_t i = 0; i < output.size(); i++) {
            if(i != 0)
                ss << ",";
            ss << output[i];
        }
        result.results.emplace_back("", true, "Thermal Radiator Output", ss.str());
        if(output.empty()) {
            result.results.emplace_back("Part two", false, "Diagnostic Code", "<!>", "584126");
        } else {
            result.results.emplace_back("Part two", false, "Diagnostic Code", output[output.size() - 1], 584126);
        }

        return result;
    }
}
