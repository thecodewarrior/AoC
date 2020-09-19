#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "days.h"

namespace day1
{
    int run()
    {
        std::ifstream inputfile("input/day1.txt");

        if (!inputfile.is_open())
        {
            std::cout << "Unable to open file";
            return 1;
        }

        std::vector<int> masses;

        std::string line;
        while (getline(inputfile, line))
        {
            masses.push_back(std::stoi(line));
        }
        inputfile.close();

        printf("Received %d modules\n", (int)masses.size());

        int fuel = 0;
        for (int i = 0; i < masses.size(); i++)
        {
            int module_fuel = masses[i] / 3 - 2;
            fuel += module_fuel;
            masses[i] = module_fuel;
        }

        printf("Naive fuel requirement (part one): %d\n", fuel);

        bool mass_remaining = true;
        while (mass_remaining)
        {
            mass_remaining = false;

            for (int i = 0; i < masses.size(); i++)
            {
                int fuel_fuel = masses[i] / 3 - 2;
                if (fuel_fuel > 0)
                {
                    mass_remaining = true;
                    fuel += fuel_fuel;
                    masses[i] = fuel_fuel;
                }
            }
        }

        printf("Real fuel requirement (part two): %d\n", fuel);

        return 0;
    }
} // namespace day1