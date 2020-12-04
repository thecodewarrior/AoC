#ifndef AOC_DAY3_H
#define AOC_DAY3_H

#include <aoc/Day.h>
#include <utils.h>
#include <vector>

class Day3 : public aoc::Day {
public:
    explicit Day3(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run_day() override;

    struct TreeMap {
        std::vector<bool> map;
        int width = 0;
        int height = 0;

        void add_line(const std::string &line);
        bool has_tree(int x, int y);
        int trees_for_slope(int dx, int dy);
    };
};

#endif // AOC_DAY3_H
