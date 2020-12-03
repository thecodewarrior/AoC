#ifndef AOC_DAY5_H
#define AOC_DAY5_H

#include <aoc/Day.h>
#include <utils.h>

class Day5 : public aoc::Day {
public:
    explicit Day5(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run_day() override;
};

#endif // AOC_DAY5_H
