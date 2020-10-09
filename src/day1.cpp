#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "days.h"

namespace day1 {
    void run(aoc::aoc_output &out) {
        std::ifstream inputfile("input/day1.txt");

        if (!inputfile.is_open()) {
            out.return_error("Unable to open input/day1.txt");
            return;
        }

        std::vector<int> masses;

        std::string line;
        while (getline(inputfile, line)) {
            masses.push_back(std::stoi(line));
        }
        inputfile.close();

        out.print_trivia("Module count", (int) masses.size());

        int fuel = 0;
        for (int &mass : masses) {
            int module_fuel = mass / 3 - 2;
            fuel += module_fuel;
            mass = module_fuel;
        }

        out.print_result("Part one", "Naive fuel requirement", fuel, 3302760);

        bool mass_remaining = true;
        while (mass_remaining) {
            mass_remaining = false;

            for (int &mass : masses) {
                int fuel_fuel = mass / 3 - 2;
                if (fuel_fuel > 0) {
                    mass_remaining = true;
                    fuel += fuel_fuel;
                    mass = fuel_fuel;
                }
            }
        }

        out.print_result("Part two", "Real fuel requirement", fuel, 4951265);
    }
} // namespace day1