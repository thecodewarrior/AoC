#include "aoc_utils.h"
#include "aoc_output.h"
#include <string>
#include <sstream>
#include <iostream>

namespace aoc {

    std::string center(const std::string &pad, size_t width, std::string text, size_t visual_width) {
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
        for(const char& c: text) {
            if((c & 0xc0) != 80)
                codepoints++;
        }

        // https://en.wikipedia.org/wiki/ANSI_escape_code#CSI_sequences
        // ESC '[' (0x30-0x3f)* (0x20-0x2f)* (0x40-0x7e)

        int total_sequence_length = 0;

        for(int search_pos = 0; search_pos < text.size(); search_pos++) {
            if(text[search_pos] == '\x1b') {
                int i = search_pos + 1;
                // check for the bracket
                if(i == text.size() || text[i] != '[')
                    continue;
                i++;
                // zero or more in the 0x30-0x3f range
                while(i < text.size() && (text[i] & 0xf0) == 0x30) {
                    i++;
                }
                // zero or more in the 0x20-0x2f range
                while(i < text.size() && (text[i] & 0xf0) == 0x20) {
                    i++;
                }
                // exactly one in the 0x40-0x7e range
                if(i == text.size() || text[i] < 0x40 || text[i] > 0x7e)
                    continue;
                i++;
                total_sequence_length += i - search_pos;
                search_pos = i - 1; // this will be incremented at the end of the loop, so decrement it here first
            }
        }

        return codepoints - total_sequence_length;
    }

}
