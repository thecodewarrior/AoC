#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include "aoc_utils.h"
#include "days.h"

namespace day3 {
    struct Segment {
        bool vertical;
        // position on the crosswise axis (x for vertical, y for horizontal)
        int position;
        // fully closed range on that axis
        int start, end;

        Segment(bool vertical, int position, int start, int anEnd) : vertical(vertical), position(position),
                                                                     start(start), end(anEnd) {}

        void add_intersections(std::vector<aoc::point<int>> &list, const Segment &other) const {
            if (vertical != other.vertical) {
                if (start <= other.position && other.position <= end &&
                    other.start <= position && position <= other.end) {
                    list.push_back(
                            vertical
                            ? aoc::point<int>(position, other.position)
                            : aoc::point<int>(other.position, position)
                    );
                }
            } else {
                if (position == other.position) {
                    int max_start = std::max(start, other.start);
                    int min_end = std::min(end, other.end);
                    for (int i = max_start; i <= min_end; i++) {
                        list.push_back(
                                vertical
                                ? aoc::point<int>(position, i)
                                : aoc::point<int>(i, position)
                        );
                    }
                }
            }
        }
    };

    class WireMess {
        std::vector<Segment> segments;
    public:
        explicit WireMess(std::string &line) {
            int x = 0, y = 0;
            std::stringstream ss(line);
            std::string insn;
            while (getline(ss, insn, ',')) {
                int length = std::stoi(insn.substr(1));
                switch (insn[0]) {
                    case 'U':
                        segments.emplace_back(true, x, y - length, y);
                        y -= length;
                        break;
                    case 'D':
                        segments.emplace_back(true, x, y, y + length);
                        y += length;
                        break;
                    case 'L':
                        segments.emplace_back(false, y, x - length, x);
                        x -= length;
                        break;
                    case 'R':
                        segments.emplace_back(false, y, x, x + length);
                        x += length;
                        break;
                }
            }
        }

        std::vector<aoc::point<int>> get_intersections(const WireMess &other) const {
            std::vector<aoc::point<int>> intersections;
            for (auto segment : segments) {
                for (auto other_segment : other.segments) {
                    segment.add_intersections(intersections, other_segment);
                }
            }
            return intersections;
        }
    };

    int run() {
        std::ifstream inputfile("input/day3.txt");

        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            return 1;
        }


        std::string line;
        if (!getline(inputfile, line)) {
            std::cout << "Undable to read line 1";
            inputfile.close();
            return 1;
        }
        WireMess mess1(line);

        if (!getline(inputfile, line)) {
            std::cout << "Undable to read line 2";
            inputfile.close();
            return 1;
        }
        WireMess mess2(line);

        inputfile.close();

        std::vector<aoc::point<int>> intersections = mess1.get_intersections(mess2);
        int minDistance = INT_MAX;
        for (auto point : intersections) {
            if (point != aoc::point<int>(0, 0)) { // center point doesn't count
                int distance = point.manhattan_distance(aoc::point<int>(0, 0));
                if (distance < minDistance) // manual for sake of breakpointing
                    minDistance = distance;
            }
        }

        printf("Minimum distance (part one): %d\n", minDistance);

        return 0;
    }
}