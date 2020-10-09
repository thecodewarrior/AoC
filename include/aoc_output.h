#ifndef AOC_OUTPUT_H
#define AOC_OUTPUT_H

#include <string>

namespace aoc {
    /**
     * Handles pretty printing of AoC results/output.
     */
    class aoc_output {
    private:
        bool had_failure = false;
        std::string return_error_message;
        int pad_width = 80;
    public:
        void print_header(const std::string &day_name) const;

        void print_footer() const;

        void print_line(const std::string &text) const;

        void print_trivia(const std::string &description, const std::string &value) const;

        void print_trivia(const std::string &description, int value) const {
            print_trivia(description, std::to_string(value));
        }

        void print_result(const std::string &part_name, const std::string &description,
                          const std::string &value, const std::string &correct_value);

        void print_result(const std::string &part_name, const std::string &description, const std::string &value) {
            print_result(part_name, description, value, value);
        }

        void print_result(const std::string &part_name, const std::string &description, int value, int correct_value) {
            print_result(part_name, description, std::to_string(value), std::to_string(correct_value));
        }

        void print_result(const std::string &part_name, const std::string &description, int value) {
            print_result(part_name, description, std::to_string(value));
        }

        void return_error(const std::string &error) {
            return_error_message = error;
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
}


#endif //AOC_OUTPUT_H
