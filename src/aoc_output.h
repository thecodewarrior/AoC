#ifndef AOC_AOC_OUTPUT_H
#define AOC_AOC_OUTPUT_H

#include <string>

namespace aoc {
    std::string center(const std::string &pad, size_t width, std::string text, size_t visual_width);

    /**
     * Get the visual width of a piece of text. This performs a basic process of counting codepoints and subtracting the
     * length of any ANSI escape sequences.
     *
     * @param text The text to measure.
     * @return The visual length of the text.
     */
    int text_width(const std::string &text);
}


#endif //AOC_AOC_OUTPUT_H
