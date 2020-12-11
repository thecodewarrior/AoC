#ifndef AOC_OUTPUT_H
#define AOC_OUTPUT_H

#include "ansi.h"
#include <fmt/format.h>
#include <string>

namespace aoc {

template <typename T> std::string to_string(const T &value) { return fmt::format(FMT_STRING("{}"), value); }

/**
 * Handles pretty printing of AoC results/output.
 */
class Printer {
private:
    std::string year;
    int pad_width = 80;

    bool had_failure = false;

public:
    explicit Printer(std::string year) : year(std::move(year)) {}

    /**
     * Rests the per-day state (e.g. errors) so this printer can be reused for another day. This is automatically
     * called at the end of the Day::run_day function.
     */
    void reset_day_state();

    void print_header(const std::string &day_name) const;

    void print_footer(std::string &error_message) const;

    void print_line(const std::string &text) const;

    struct LogValue {
        std::string text;

        template <typename T> LogValue(const T &value) : text(to_string(value)) {} // NOLINT(google-explicit-constructor)
    };

    void print_trivia(const std::string &description, const LogValue &value) const;
    void print_trivia_fmt(const std::string &description, const std::vector<LogValue> &values) const;

    void print_result(const std::string &part_name, const std::string &description, const LogValue &value,
                      const LogValue &correct_value);

    void print_result(const std::string &part_name, const std::string &description, const LogValue &value);
};

std::string center(const std::string &pad, size_t width, const std::string &text);

/**
 * Get the visual width of a piece of text. This performs a basic process of counting codepoints and subtracting the
 * length of any ANSI escape sequences.
 *
 * @param text The text to measure.
 * @return The visual length of the text.
 */
int text_width(const std::string &text);
} // namespace aoc

#endif // AOC_OUTPUT_H
