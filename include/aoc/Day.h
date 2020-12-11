#ifndef AOC_DAY_H
#define AOC_DAY_H

#include "Printer.h"
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

namespace aoc {

namespace fs = boost::filesystem;

class DayAbortException : public std::exception {
public:
    const std::string message;
    explicit DayAbortException(std::string message) : message(std::move(message)) {}
    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};

struct DayContext {
    std::string year;
    std::string day_name;
    fs::path input_directory;

    DayContext day(std::string day) { return {year, std::move(day), input_directory}; }
};

class Day {
private:
    aoc::Printer printer;

protected:
    fs::path input;

public:
    const std::string day_name;

    explicit Day(DayContext ctx);
    virtual ~Day() = default;

    /**
     * Run this day and display the output with the given printer
     */
    void run_day();

protected:
    /**
     * Run the actual day. The #run_day function prints the header, calls this, then prints the footer.
     */
    virtual void run() = 0;

    std::vector<std::string> read_input_lines();

    void print_line(const std::string &text) const { printer.print_line(text); }

    void print_trivia(const std::string &description, const Printer::LogValue &value) const {
        printer.print_trivia(description, value);
    }
    void print_trivia_fmt(const std::string &description, const std::vector<Printer::LogValue> &values) const {
        printer.print_trivia_fmt(description, values);
    }

    void print_result(const std::string &part_name, const std::string &description, const Printer::LogValue &value,
                      const Printer::LogValue &correct_value) {
        printer.print_result(part_name, description, value, correct_value);
    }

    void print_result(const std::string &part_name, const std::string &description, const Printer::LogValue &value) {
        printer.print_result(part_name, description, value);
    }
};

#define AOC_ABORT(msg) throw aoc::DayAbortException(msg);

} // namespace aoc

#endif // AOC_DAY_H
