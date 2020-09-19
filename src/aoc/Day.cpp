#include <aoc/Day.h>
#include <exception>

namespace aoc {

Day::Day(DayContext ctx)
    : day_name(std::move(ctx.day_name)), input(std::move(ctx.input_directory)), printer(std::move(ctx.year)) {}

void Day::run() {
    printer.print_header(day_name);
    std::string error_message;
    try {
        run_day();
    } catch (DayAbortException &e) {
        error_message = e.message;
    }
    printer.print_footer(error_message);
    printer.reset_day_state();
}

} // namespace aoc
