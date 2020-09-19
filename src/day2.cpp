#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "days.h"

namespace day2
{
    int run()
    {
        std::ifstream inputfile("input/day2.txt");

        if (!inputfile.is_open())
        {
            std::cout << "Unable to open file";
            return 1;
        }
        aoc::IntcodeProgram program(&inputfile);
        inputfile.close();

        printf("1202 result (part one): %d\n", run_program(&program, 12, 2));

        auto search_result = find_program(&program, 19690720);
        printf("Search result (part two): %d\n", 100 * search_result.first + search_result.second);

        return 0;
    }

    int run_program(aoc::IntcodeProgram *program, int noun, int verb)
    {
        aoc::IntcodeComputer computer(program);

        computer[1] = noun;
        computer[2] = verb;

        computer.run();

        return computer[0];
    }

    std::pair<int, int> find_program(aoc::IntcodeProgram *program, int target)
    {
        printf("Searching for result %d\n", target);
        for (int noun = 0; noun < 100; noun++)
        {
            for (int verb = 0; verb < 100; verb++)
            {
                if (run_program(program, noun, verb) == target)
                {
                    return std::pair<int, int>(noun, verb);
                }
            }
        }
        return std::pair<int, int>(-1, -1);
    }
} // namespace day2