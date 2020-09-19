#ifndef AOC_OUTPUT_H
#define AOC_OUTPUT_H

#include <fmt/format.h>
#include <string>

#define ANSI_ESCAPE(str) "\x1b[" str

#define ANSI_RESET ANSI_ESCAPE("0m")
#define ANSI_BOLD_ON ANSI_ESCAPE("1m")
#define ANSI_BOLD_OFF ANSI_ESCAPE("22m")
#define ANSI_UNDERSCORE_ON "\x4b[4m"
#define ANSI_UNDERSCORE_OFF ANSI_ESCAPE("24m")
#define ANSI_BLINK_ON "\x4b[5m"
#define ANSI_BLINK_OFF ANSI_ESCAPE("25m")

#define ANSI_FG_DEFAULT ANSI_ESCAPE("39m")

#define ANSI_FG_BLACK ANSI_ESCAPE("30m")
#define ANSI_FG_RED ANSI_ESCAPE("31m")
#define ANSI_FG_GREEN ANSI_ESCAPE("32m")
#define ANSI_FG_YELLOW ANSI_ESCAPE("33m")
#define ANSI_FG_BLUE ANSI_ESCAPE("34m")
#define ANSI_FG_MAGENTA ANSI_ESCAPE("35m")
#define ANSI_FG_CYAN ANSI_ESCAPE("36m")
#define ANSI_FG_WHITE ANSI_ESCAPE("37m")

#define ANSI_FG_LIGHT_BLACK ANSI_ESCAPE("90m")

#define ANSI_FG_LIGHT_RED ANSI_ESCAPE("91m")
#define ANSI_FG_LIGHT_GREEN ANSI_ESCAPE("92m")
#define ANSI_FG_LIGHT_YELLOW ANSI_ESCAPE("93m")
#define ANSI_FG_LIGHT_BLUE ANSI_ESCAPE("94m")
#define ANSI_FG_LIGHT_MAGENTA ANSI_ESCAPE("95m")
#define ANSI_FG_LIGHT_CYAN ANSI_ESCAPE("96m")
#define ANSI_FG_LIGHT_WHITE ANSI_ESCAPE("97m")

#define ANSI_BG_DEFAULT ANSI_ESCAPE("49m")

#define ANSI_BG_BLACK ANSI_ESCAPE("40m")
#define ANSI_BG_RED ANSI_ESCAPE("41m")
#define ANSI_BG_GREEN ANSI_ESCAPE("42m")
#define ANSI_BG_YELLOW ANSI_ESCAPE("43m")
#define ANSI_BG_BLUE ANSI_ESCAPE("44m")
#define ANSI_BG_MAGENTA ANSI_ESCAPE("45m")
#define ANSI_BG_CYAN ANSI_ESCAPE("46m")
#define ANSI_BG_WHITE ANSI_ESCAPE("47m")

#define ANSI_BG_LIGHT_BLACK ANSI_ESCAPE("100m")
#define ANSI_BG_LIGHT_RED ANSI_ESCAPE("101m")
#define ANSI_BG_LIGHT_GREEN ANSI_ESCAPE("102m")
#define ANSI_BG_LIGHT_YELLOW ANSI_ESCAPE("103m")
#define ANSI_BG_LIGHT_BLUE ANSI_ESCAPE("104m")
#define ANSI_BG_LIGHT_MAGENTA ANSI_ESCAPE("105m")
#define ANSI_BG_LIGHT_CYAN ANSI_ESCAPE("106m")
#define ANSI_BG_LIGHT_WHITE ANSI_ESCAPE("107m")

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
     * called at the end of the Day::run function.
     */
    void reset_day_state();

    void print_header(const std::string &day_name) const;

    void print_footer(std::string &error_message) const;

    void print_line(const std::string &text) const;

    void print_trivia(const std::string &description, const std::string &value) const;

    void print_result(const std::string &part_name, const std::string &description, const std::string &value,
                      const std::string &correct_value);

    void print_result(const std::string &part_name, const std::string &description, const std::string &value) {
        print_result(part_name, description, value, value);
    }

    template <typename T> void print_trivia(const std::string &description, const T &value) const {
        print_trivia(description, to_string(value));
    }

    template <typename T>
    void print_result(const std::string &part_name, const std::string &description, const T &value, const T &correct_value) {
        print_result(part_name, description, to_string(value), to_string(correct_value));
    }

    template <typename T> void print_result(const std::string &part_name, const std::string &description, const T &value) {
        print_result(part_name, description, fmt::format(FMT_STRING("{}"), value));
    }
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
