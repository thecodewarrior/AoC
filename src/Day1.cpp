#include "Day1.h"

void Day1::run_day() {
    fs::ifstream inputfile(input / "day1.txt");
    if (!inputfile.is_open()) {
        AOC_ABORT("Unable to open day1.txt");
    }
}
