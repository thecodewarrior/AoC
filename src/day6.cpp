#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "days.h"

namespace day6 {
    void run(aoc::aoc_output &out) {
        std::ifstream inputfile("input/day6.txt");
        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            out.return_error("Unable to open input/day6.txt");
            return;
        }

        // a map of orbiter -> parent
        std::map<std::string, std::string> planets;
        std::string line;
        while (getline(inputfile, line)) {
            std::string parent = line.substr(0, line.find(')'));
            std::string planet = line.substr(line.find(')') + 1);
            planets[planet] = parent;

        }
        inputfile.close();

        out.print_trivia("Planet count", planets.size());
        {
            int count = 0;
            auto leaf = planets.begin();
            while (leaf != planets.end()) {
                auto current = leaf;
                while (current != planets.end()) {
                    count++;
                    current = planets.find(current->second);
                }
                leaf++;
            }
            out.print_result("Part one", "Orbit count", count, 145250);
        }
        {
            std::vector<std::string> my_orbits;
            auto current = planets.find(planets["YOU"]);
            while (current != planets.end()) {
                my_orbits.push_back(current->first);
                current = planets.find(current->second);
            }

            int transfer_count = -1;

            int santa_depth = 0;
            current = planets.find(planets["SAN"]);
            while (current != planets.end()) {
                auto common_body = std::find(my_orbits.begin(), my_orbits.end(), current->first);
                if(common_body != my_orbits.end()) {
                    auto common_index = common_body - my_orbits.begin();
                    transfer_count = santa_depth + common_index;
                    break;
                }
                current = planets.find(current->second);
                santa_depth++;
            }

            out.print_result("Part one", "Transfer count", transfer_count, 274);
        }
    }
}
