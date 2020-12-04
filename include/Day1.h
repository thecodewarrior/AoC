#ifndef AOC_DAY1_H
#define AOC_DAY1_H

#include <aoc/Day.h>
#include <utils.h>

class Day1 : public aoc::Day {
public:
    explicit Day1(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run() override;
};

#endif // AOC_DAY1_H
