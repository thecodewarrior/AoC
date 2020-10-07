#include "aoc_utils.h"
#include "days.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>
#include <main.h>

using namespace aoc;

int main(int argc, char **argv) {
    std::vector<aoc::DayResult(*)(std::ostream &)> days{
            day1::run,
            day2::run,
            day3::run,
            day4::run,
            day5::run,
            day6::run,
    };

    for (int i = 1; i < argc; i++) {
        int day = std::stoi(argv[i]);
        if (day <= 0 || day > days.size()) {
            std::cerr << "Day " << day << " is not in range [1, " << days.size() << "]" << std::endl;
        } else {
            run_day(day, days[day - 1]);
        }
    }
    if(argc == 1) {
        for (size_t day = 0; day < days.size(); day++) {
            run_day(day + 1, days[day]);
        }
    }

    return 0;
}


int run_day(int day, aoc::DayResult(*function)(std::ostream &)) {
    size_t pad_width = 80;
    {
        size_t width = 0;

        std::stringstream text;
        text << ANSI_FG_LIGHT_GREEN << ANSI_BOLD_ON << " Advent of Code 2019" << ANSI_BOLD_OFF;
        width += 20;
        text << ANSI_FG_GREEN << ", day ";
        width += 6;

        std::string num = std::to_string(day);
        text << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << num << ANSI_BOLD_OFF;
        width += num.size();

        text << " " << ANSI_FG_GREEN;
        width++;

        std::cout << ANSI_FG_GREEN << "╔" << center("═", pad_width, text.str(), width) << "╗" << ANSI_FG_DEFAULT;
    }
    PadBuf buf(std::cout, "\x1b[32m║\x1b[39m ");
    std::ostream out(&buf);
    out << std::endl;
    aoc::DayResult day_result = function(out);
    out.flush();
    if (day_result.return_code == 0) {
        bool was_success = true;
        for (const auto &result : day_result.results) {
            size_t width = 0;

            std::stringstream text;
            text << " ";
            width++;

            if (result.is_trivia) {
                text << ANSI_FG_GREEN << result.description;
            } else {
                text << ANSI_FG_LIGHT_GREEN << ANSI_BOLD_ON << result.description << ANSI_BOLD_OFF;
            }
            width += result.description.size();
            text << ANSI_FG_GREEN << ": ";
            width += 2;

            std::string line_color;
            if (result.value != result.correct_value) {
                line_color = ANSI_FG_RED;
                was_success = false;
                if (result.is_trivia) {
                    text << ANSI_FG_RED << result.value << ANSI_FG_GREEN << " (" << ANSI_FG_LIGHT_GREEN
                         << result.correct_value << ANSI_FG_GREEN << ")";
                } else {
                    text << ANSI_FG_RED << ANSI_BOLD_ON << result.value << ANSI_BOLD_OFF << ANSI_FG_GREEN << " ("
                         << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << result.correct_value << ANSI_BOLD_OFF
                         << ANSI_FG_GREEN << ")";
                }
                width += result.value.size() + result.correct_value.size() + 3;
            } else {
                line_color = ANSI_FG_GREEN;
                if (result.is_trivia) {
                    text << ANSI_FG_LIGHT_GREEN << result.value;
                } else {
                    text << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << result.value << ANSI_BOLD_OFF;
                }
                width += result.value.size();
            }

            text << line_color << " ";
            width++;

            std::string pad, lcap, rcap;
            if (result.is_trivia) {
                pad = " ";
                lcap = "║";
                rcap = "║";
            } else {
                pad = "─";
                lcap = "╟";
                rcap = "╢";
            }

            std::string centered = center(pad, pad_width, text.str(), width);
            if (!result.part_name.empty()) {
                std::string part;
                if (result.is_trivia) {
                    part = std::string(" ") + ANSI_FG_LIGHT_GREEN + result.part_name + line_color + " ";
                } else {
                    part = std::string(" ") + ANSI_FG_LIGHT_YELLOW + result.part_name + line_color + " ";
                }
                size_t l = pad.size();
                centered.replace(l, (result.part_name.size() + 2) * l, part);
            }

            std::cout << ANSI_FG_GREEN << lcap << line_color << centered << ANSI_FG_GREEN << rcap << ANSI_FG_DEFAULT
                      << std::endl;
        }

        std::stringstream result_message;
        size_t result_length = 0;

        if(was_success) {
            result_message << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << " Success " << ANSI_BOLD_OFF << ANSI_FG_GREEN;
            result_length += 9;
        } else {
            result_message << ANSI_FG_RED << ANSI_BOLD_ON << " Failure " << ANSI_BOLD_OFF << ANSI_FG_GREEN;
            result_length += 9;
        }
        std::cout << ANSI_FG_GREEN << "╚" << center("═", pad_width, result_message.str(), result_length) << "╝"
                  << ANSI_FG_DEFAULT << std::endl;
    } else {
        size_t width = 0;
        std::stringstream text;
        text << ANSI_FG_RED << " Error: ";
        width += 8;

        std::string num = std::to_string(day_result.return_code);
        text << ANSI_BOLD_ON << num << ANSI_BOLD_OFF;
        width += num.size();

        text << " " << ANSI_FG_GREEN;
        width++;

        std::cout << ANSI_FG_GREEN << "╚" << center("═", pad_width, text.str(), width) << "╝" << ANSI_FG_DEFAULT
                  << std::endl;
    }

    return day_result.return_code;
}

std::string center(std::string pad, size_t width, std::string text, size_t visual_width) {
    if (visual_width > width)
        return text;
    size_t left_pad = (width - visual_width) / 2;
    size_t right_pad = width - visual_width - left_pad;
    std::ostringstream out;
    for (size_t i = 0; i < left_pad; i++)
        out << pad;
    out << text;
    for (size_t i = 0; i < right_pad; i++)
        out << pad;
    return out.str();
}

PadBuf::PadBuf(std::ostream &out, std::string newline)
        : basic_stringbuf(), out(out), newline(std::move(newline)), was_nl(false) {}

int PadBuf::overflow(int __c) {
    if (__c == EOF)
        return EOF;
    if (was_nl) {
        out << newline;
    }
    was_nl = __c == '\n';
    out.put(__c);
    return __c;
}
