#include "aoc/Printer.h"
#include <iostream>
#include <sstream>
#include <string>

namespace aoc {

std::string center(const std::string &pad, size_t width, const std::string &text) {
    size_t visual_width = text_width(text);
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

int text_width(const std::string &text) {
    // https://stackoverflow.com/a/3586973/1541907
    int codepoints = 0;
    for (const char &c : text) {
        if ((c & 0xc0) != 80)
            codepoints++;
    }

    // https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_sequences
    // ESC '[' (0x30-0x3f)* (0x20-0x2f)* (0x40-0x7e)

    int total_sequence_length = 0;

    for (int search_pos = 0; search_pos < text.size(); search_pos++) {
        if (text[search_pos] == '\x1b') {
            int i = search_pos + 1;
            // check for the bracket
            if (i == text.size() || text[i] != '[')
                continue;
            i++;
            // zero or more in the 0x30-0x3f range
            while (i < text.size() && (text[i] & 0xf0) == 0x30) {
                i++;
            }
            // zero or more in the 0x20-0x2f range
            while (i < text.size() && (text[i] & 0xf0) == 0x20) {
                i++;
            }
            // exactly one in the 0x40-0x7e range
            if (i == text.size() || text[i] < 0x40 || text[i] > 0x7e)
                continue;
            i++;
            total_sequence_length += i - search_pos;
            search_pos = i - 1; // this will be incremented at the end of the loop, so decrement it here first
        }
    }

    return codepoints - total_sequence_length;
}

void Printer::reset_day_state() {
    this->had_failure = false;
}

void Printer::print_header(const std::string &day_name) const {
    std::stringstream text;
    text << " " << ANSI_FG_LIGHT_GREEN << ANSI_BOLD_ON << "Advent of Code " << year << ANSI_BOLD_OFF << ANSI_FG_GREEN
         << ", day " << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << day_name << ANSI_BOLD_OFF << ANSI_FG_GREEN << " ";

    text_width(text.str());
    std::cout << ANSI_FG_GREEN << "╔" << center("═", pad_width, text.str()) << "╗" << ANSI_FG_DEFAULT << "\n";
}

void Printer::print_footer(std::string &error_message) const {
    std::stringstream text;
    if (!error_message.empty()) {
        text << ANSI_FG_RED << " Error: " << ANSI_BOLD_ON << error_message << ANSI_BOLD_OFF << " " << ANSI_FG_GREEN;
    } else {
        if (had_failure) {
            text << ANSI_FG_RED << ANSI_BOLD_ON << " Failure " << ANSI_BOLD_OFF << ANSI_FG_GREEN;
        } else {
            text << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << " Success " << ANSI_BOLD_OFF << ANSI_FG_GREEN;
        }
    }
    std::cout << ANSI_FG_GREEN << "╚" << aoc::center("═", pad_width, text.str()) << "╝" << ANSI_FG_DEFAULT << "\n";
}

void Printer::print_line(const std::string &text) const {
    std::cout << ANSI_FG_GREEN << "║" << ANSI_FG_DEFAULT << aoc::center(" ", pad_width, text + ANSI_FG_DEFAULT)
              << ANSI_FG_GREEN << "║" << ANSI_FG_DEFAULT << "\n";
}

void Printer::print_trivia(const std::string &description, const std::string &value) const {
    std::stringstream text;
    text << ANSI_FG_GREEN << description << ANSI_FG_GREEN << ": " << ANSI_FG_LIGHT_GREEN << value;
    print_line(text.str());
}

void Printer::print_result(const std::string &part_name, const std::string &description, const std::string &value,
                           const std::string &correct_value) {
    std::stringstream text;
    text << " " << ANSI_FG_LIGHT_GREEN << ANSI_BOLD_ON << description << ANSI_BOLD_OFF << ANSI_FG_GREEN << ": ";

    // the color for the padding lines. This is red if the result was incorrect
    std::string line_color;
    if (value != correct_value) {
        // if the value was incorrect, print `actual_value (correct_value)`
        line_color = ANSI_FG_RED;
        had_failure = true;
        text << ANSI_FG_RED << ANSI_BOLD_ON << value << ANSI_BOLD_OFF << ANSI_FG_GREEN;
        text << " (" << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << correct_value << ANSI_BOLD_OFF << ANSI_FG_GREEN << ")";
    } else {
        line_color = ANSI_FG_GREEN;
        text << ANSI_FG_LIGHT_YELLOW << ANSI_BOLD_ON << value << ANSI_BOLD_OFF;
    }

    text << line_color << " ";

    std::string centered = aoc::center("─", pad_width, text.str());

    // insert the part name (e.g. "Part one", "Part two", "whatever") into the line
    std::string part = std::string(" ") + ANSI_FG_LIGHT_YELLOW + part_name + line_color + " ";
    // the box-drawing characters are multi-byte, but spaces are not, so use this as the base unit.
    size_t l = std::string("─").size();
    // "overwrite" a section of the padded string with the part name
    centered.replace(l, (part_name.size() + 2) * l, part);

    std::cout << ANSI_FG_GREEN << "╟" << line_color << centered << ANSI_FG_GREEN << "╢" << ANSI_FG_DEFAULT << "\n";
}
} // namespace aoc
