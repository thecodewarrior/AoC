#ifndef AOC_DAY3_H
#define AOC_DAY3_H

#include <aoc/Day.h>
#include <utils.h>

class Day3 : public aoc::Day {
public:
    explicit Day3(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run_day() override;
};

#endif // AOC_DAY3_H
