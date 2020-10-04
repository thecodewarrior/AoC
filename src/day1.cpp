#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "days.h"

namespace day1 {
    aoc::DayResult run(std::ostream &out) {
        aoc::DayResult result;

        std::ifstream inputfile("input/day1.txt");

        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            return aoc::DayResult(1);
        }

        std::vector<int> masses;

        std::string line;
        while (getline(inputfile, line)) {
            masses.push_back(std::stoi(line));
        }
        inputfile.close();

        result.results.emplace_back("", true, "Module count", (int) masses.size());

        int fuel = 0;
        for (int &mass : masses) {
            int module_fuel = mass / 3 - 2;
            fuel += module_fuel;
            mass = module_fuel;
        }

        result.results.emplace_back("Part one", false, "Naive fuel requirement", fuel);

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

        result.results.emplace_back("Part two", false, "Real fuel requirement", fuel);

        return result;
    }
} // namespace day1