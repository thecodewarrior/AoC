#ifndef AOC_MAIN_H
#define AOC_MAIN_H

#include <string>
#include "aoc/Printer.h"

int main(int argc, char *argv[]);

void run_day(int day, void(*function)(aoc::Printer &));

#endif //AOC_MAIN_H
