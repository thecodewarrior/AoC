#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include "aoc_utils.h"
#include "days.h"

namespace day3 {
    struct Intersection {
        aoc::point<int> point;
        int time_a, time_b, time;

        Intersection(const aoc::point<int> &point, int timeA, int timeB) : point(point), time_a(timeA), time_b(timeB),
                                                                           time(timeA + timeB) {}
    };

    struct Segment {
        bool vertical;
        // position on the crosswise axis (x for vertical, y for horizontal)
        int position;
        // fully closed range on that axis
        int start, end;
        int start_time, time_direction;

        Segment(bool vertical, int position, int start, int anEnd, int startTime, int timeDirection) : vertical(
                vertical), position(position), start(start), end(anEnd), start_time(startTime), time_direction(
                timeDirection) {}

        void add_intersections(std::vector<Intersection> &list, const Segment &other) const {
            if (vertical != other.vertical) {
                if (start <= other.position && other.position <= end &&
                    other.start <= position && position <= other.end) {

                    aoc::point<int> point = vertical
                                            ? aoc::point<int>(position, other.position)
                                            : aoc::point<int>(other.position, position);

                    list.emplace_back(
                            point,
                            start_time + time_direction * (other.position - start),
                            other.start_time + other.time_direction * (position - other.start)
                    );
                }
            } else {
                if (position == other.position) {
                    int max_start = std::max(start, other.start);
                    int min_end = std::min(end, other.end);
                    for (int i = max_start; i <= min_end; i++) {
                        aoc::point<int> point =
                                vertical
                                ? aoc::point<int>(position, i)
                                : aoc::point<int>(i, position);
                        list.emplace_back(
                                point,
                                start_time + time_direction * (i - start),
                                other.start_time + other.time_direction * (i - other.start)
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
            int time = 0;
            std::stringstream ss(line);
            std::string insn;
            while (getline(ss, insn, ',')) {
                int length = std::stoi(insn.substr(1));
                switch (insn[0]) {
                    case 'U':
                        segments.emplace_back(true, x, y - length, y, time + length, -1);
                        y -= length;
                        break;
                    case 'D':
                        segments.emplace_back(true, x, y, y + length, time, 1);
                        y += length;
                        break;
                    case 'L':
                        segments.emplace_back(false, y, x - length, x, time + length, -1);
                        x -= length;
                        break;
                    case 'R':
                        segments.emplace_back(false, y, x, x + length, time, 1);
                        x += length;
                        break;
                }
                time += length;
            }
        }

        [[nodiscard]] std::vector<Intersection> get_intersections(const WireMess &other) const {
            std::vector<Intersection> intersections;
            for (auto segment : segments) {
                for (auto other_segment : other.segments) {
                    segment.add_intersections(intersections, other_segment);
                }
            }
            return intersections;
        }
    };

    aoc::DayResult run() {
        aoc::DayResult result;
        std::ifstream inputfile("input/day3.txt");

        if (!inputfile.is_open()) {
            std::cout << "Unable to open file";
            return aoc::DayResult(1);
        }

        std::string line;
        if (!getline(inputfile, line)) {
            std::cout << "Undable to read line 1";
            inputfile.close();
            return aoc::DayResult(1);
        }
        WireMess mess1(line);

        if (!getline(inputfile, line)) {
            std::cout << "Undable to read line 2";
            inputfile.close();
            return aoc::DayResult(1);
        }
        WireMess mess2(line);

        inputfile.close();

        std::vector<Intersection> intersections = mess1.get_intersections(mess2);
        int minDistance = INT_MAX;
        Intersection shortest(aoc::point<int>(0, 0), INT_MAX / 2, INT_MAX / 2);

        for (auto intersection : intersections) {
            if (intersection.point != aoc::point<int>(0, 0)) { // center point doesn't count
                int distance = intersection.point.manhattan_distance(aoc::point<int>(0, 0));
                if (distance < minDistance) // manual for sake of breakpointing
                    minDistance = distance;

                if (intersection.time < shortest.time) {
                    shortest = intersection;
                }
            }
        }

        result.results.emplace_back("Part one", false, "Minimum distance", minDistance, 1337);
        result.results.emplace_back("Part two", false, "Shortest time", shortest.time, 65356);

        return result;
    }
}