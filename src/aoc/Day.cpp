#include <aoc/Day.h>
#include <exception>

namespace aoc {

Day::Day(DayContext ctx)
    : day_name(std::move(ctx.day_name)), input(std::move(ctx.input_directory)), printer(std::move(ctx.year)) {}

void Day::run_day() {
    printer.print_header(day_name);
    std::string error_message;
    try {
        run();
    } catch (DayAbortException &e) {
        error_message = e.message;
    }
    printer.print_footer(error_message);
    printer.reset_day_state();
}

std::vector<std::string> Day::read_input_lines() {
    fs::ifstream inputfile(input / fmt::format("day{}.txt", day_name));
    if (!inputfile.is_open()) {
        AOC_ABORT(fmt::format("Unable to open day{}.txt", day_name));
    }

    std::vector<std::string> lines;

    std::string line;
    while (getline(inputfile, line)) {
        lines.push_back(line);
    }

    return lines;
}

} // namespace aoc
