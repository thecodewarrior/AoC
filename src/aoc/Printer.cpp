#include "aoc/Printer.h"
#include <iostream>
#include <sstream>
#include <string>

#define FG_DARK ANSI_FG_GREEN
#define FG_LIGHT ANSI_FG_LIGHT_GREEN
#define FG_GOLD ANSI_FG_LIGHT_YELLOW
#define FG_RED ANSI_FG_RED
#define FG_NORM ANSI_FG_DEFAULT

#define BOLD_ON ANSI_BOLD_ON
#define BOLD_OFF ANSI_BOLD_OFF

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

void Printer::reset_day_state() { this->had_failure = false; }

void Printer::print_header(const std::string &day_name) const {
    std::stringstream text;
    text << " " << FG_LIGHT << BOLD_ON << "Advent of Code " << year << BOLD_OFF << FG_DARK
         << ", day " << FG_GOLD << BOLD_ON << day_name << BOLD_OFF << FG_DARK << " ";

    text_width(text.str());
    std::cout << FG_DARK << "╔" << center("═", pad_width, text.str()) << "╗" << FG_NORM << "\n";
}

void Printer::print_footer(std::string &error_message) const {
    std::stringstream text;
    if (!error_message.empty()) {
        text << FG_RED << " Error: " << BOLD_ON << error_message << BOLD_OFF << " " << FG_DARK;
    } else {
        if (had_failure) {
            text << FG_RED << BOLD_ON << " Failure " << BOLD_OFF << FG_DARK;
        } else {
            text << FG_GOLD << BOLD_ON << " Success " << BOLD_OFF << FG_DARK;
        }
    }
    std::cout << FG_DARK << "╚" << aoc::center("═", pad_width, text.str()) << "╝" << FG_NORM << "\n";
}

void Printer::print_line(const std::string &text) const {
    std::cout << FG_DARK << "║" << FG_NORM << aoc::center(" ", pad_width, text + FG_NORM)
              << FG_DARK << "║" << FG_NORM << "\n";
}

void Printer::print_trivia(const std::string &description, const LogValue &value) const {
    std::stringstream text;
    text << FG_DARK << description << FG_DARK << ": " << FG_LIGHT << value.text;
    print_line(text.str());
}
void Printer::print_trivia_fmt(const std::string &description, const std::vector<LogValue> &values) const {
    std::stringstream text;
    text << FG_DARK << description << FG_DARK << ": ";
    bool dim = false;
    for (auto &value : values) {
        if(dim) {
            text << FG_DARK << value.text;
        } else {
            text << FG_LIGHT << value.text;
        }
        dim = !dim;
    }
    print_line(text.str());
}

void Printer::print_result(const std::string &part_name, const std::string &description, const LogValue &value) {
    print_result(part_name, description, value, value);
}

void Printer::print_result(const std::string &part_name, const std::string &description, const LogValue &value,
                                const LogValue &correct_value) {
    std::stringstream text;
    text << " " << FG_LIGHT << BOLD_ON << description << BOLD_OFF << FG_DARK << ": ";

    // the color for the padding lines. This is red if the result was incorrect
    std::string line_color;
    if (value.text != correct_value.text) {
        // if the value was incorrect, print `actual_value (correct_value)`
        line_color = FG_RED;
        had_failure = true;
        text << FG_RED << BOLD_ON << value.text << BOLD_OFF << FG_DARK;
        text << " (" << FG_GOLD << BOLD_ON << correct_value.text << BOLD_OFF << FG_DARK << ")";
    } else {
        line_color = FG_DARK;
        text << FG_GOLD << BOLD_ON << value.text << BOLD_OFF;
    }

    text << line_color << " ";

    std::string centered = aoc::center("─", pad_width, text.str());

    // insert the part name (e.g. "Part one", "Part two", "whatever") into the line
    std::string part = std::string(" ") + FG_GOLD + part_name + line_color + " ";
    // the box-drawing characters are multi-byte, but spaces are not, so use this as the base unit.
    size_t l = std::string("─").size();
    // "overwrite" a section of the padded string with the part name
    centered.replace(l, (part_name.size() + 2) * l, part);

    std::cout << FG_DARK << "╟" << line_color << centered << FG_DARK << "╢" << FG_NORM << "\n";
}
} // namespace aoc
