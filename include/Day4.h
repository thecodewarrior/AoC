#ifndef AOC_DAY4_H
#define AOC_DAY4_H

#include <aoc/Day.h>
#include <map>
#include <string>
#include <utils.h>

class Day4 : public aoc::Day {
public:
    explicit Day4(const aoc::DayContext &ctx) : Day(ctx) {}

protected:
    void run() override;

    struct Passport {
        std::map<std::string, std::string> fields;
        [[nodiscard]] bool has_fields(const std::vector<std::string> &required_fields) const;
        [[nodiscard]] bool validate_basic() const;
        [[nodiscard]] bool validate_strict() const;
        [[nodiscard]] bool has_cid() const;
    };
};

#endif // AOC_DAY4_H
