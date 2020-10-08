#ifndef AOC_MAIN_H
#define AOC_MAIN_H

#include <string>

int main(int argc, char *argv[]);

int run_day(int day, aoc::DayResult(*function)());

std::string center(const std::string &pad, size_t width, std::string text, size_t visual_width);

#endif //AOC_MAIN_H
