#ifndef AOC_DAY2_H
#define AOC_DAY2_H

#include <aoc/Day.h>
#include <utils.h>

class Day2 : public aoc::Day {
public:
    explicit Day2(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run_day() override;
};

#endif // AOC_DAY2_H
