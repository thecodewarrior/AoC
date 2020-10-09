#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <iostream>
#include <vector>

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
    struct ResultPart {
        std::string part_name;
        bool is_trivia;
        std::string description;
        std::string value;
        std::string correct_value;

        ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value);

        ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value,
                   std::string correct_value);

        ResultPart(std::string part_name, bool is_trivia, std::string description, int value);

        ResultPart(std::string part_name, bool is_trivia, std::string description, int value, int correct_value);

        ResultPart();
    };

    struct DayResult {
        int return_code{};
        std::vector<ResultPart> results;

        explicit DayResult(int return_code);

        DayResult();
    };

    // first used in day 2

    template<typename T>
    struct point {
    public:
        T x, y;

        point(T x, T y) : x(x), y(y) {}

        point() : x(0), y(0) {}

        point operator+(const point &other) const {
            return point(x + other.x, y + other.y);
        }

        point operator-(const point &other) const {
            return point(x - other.x, y - other.y);
        }

        point operator*(const point &other) const {
            return point(x * other.x, y * other.y);
        }

        point operator*(const T &other) const {
            return point(x * other, y * other);
        }

        bool operator==(const point &rhs) const {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const point &rhs) const {
            return !(rhs == *this);
        }

        T manhattan_distance(const point &other) const {
            T distance_x = x < other.x ? other.x - x : x - other.x;
            if (distance_x < 0) {
                distance_x = -distance_x;
            }
            T distance_y = y < other.y ? other.y - y : y - other.y;
            if (distance_y < 0) {
                distance_y = -distance_y;
            }
            return distance_x + distance_y;
        }

    };

} // namespace aoc

#endif