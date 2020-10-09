#ifndef AOC_MAIN_H
#define AOC_MAIN_H

#include <string>
#include "aoc_output.h"

int main(int argc, char *argv[]);

void run_day(int day, void(*function)(aoc::aoc_output &));

#endif //AOC_MAIN_H
