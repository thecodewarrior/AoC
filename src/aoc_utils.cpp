#include "aoc_utils.h"
#include <string>
#include <utility>

namespace aoc {
    DayResult::DayResult() = default;

    DayResult::DayResult(int return_code) : return_code(return_code) {}

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)),
            value(value), correct_value(std::move(value)) {
    }

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value,
                           std::string correct_value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)),
            value(std::move(value)), correct_value(std::move(correct_value)) {
    }

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, int value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)),
            value(std::to_string(value)), correct_value(std::to_string(value)) {
    }

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, int value, int correct_value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)),
            value(std::to_string(value)), correct_value(std::to_string(correct_value)) {
    }

    ResultPart::ResultPart() = default;
} // namespace aoc