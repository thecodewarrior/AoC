#ifndef AOC_UTILS_H
#define AOC_UTILS_H

#include <iostream>
#include <vector>
#include <map>

namespace aoc {
     #define ANSI_RESET "\x1b[0m"
     #define ANSI_BOLD_ON "\x1b[1m"
     #define ANSI_BOLD_OFF "\x1b[22m"
     #define ANSI_UNDERSCORE_ON "\x4b[4m"
     #define ANSI_UNDERSCORE_OFF "\x1b[24m"
     #define ANSI_BLINK_ON "\x4b[5m"
     #define ANSI_BLINK_OFF "\x1b[25m"

     #define ANSI_FG_DEFAULT "\x1b[39m"

     #define ANSI_FG_BLACK "\x1b[30m"
     #define ANSI_FG_RED "\x1b[31m"
     #define ANSI_FG_GREEN "\x1b[32m"
     #define ANSI_FG_YELLOW "\x1b[33m"
     #define ANSI_FG_BLUE "\x1b[34m"
     #define ANSI_FG_MAGENTA "\x1b[35m"
     #define ANSI_FG_CYAN "\x1b[36m"
     #define ANSI_FG_WHITE "\x1b[37m"

     #define ANSI_FG_LIGHT_BLACK "\x1b[90m"
     #define ANSI_FG_LIGHT_RED "\x1b[91m"
     #define ANSI_FG_LIGHT_GREEN "\x1b[92m"
     #define ANSI_FG_LIGHT_YELLOW "\x1b[93m"
     #define ANSI_FG_LIGHT_BLUE "\x1b[94m"
     #define ANSI_FG_LIGHT_MAGENTA "\x1b[95m"
     #define ANSI_FG_LIGHT_CYAN "\x1b[96m"
     #define ANSI_FG_LIGHT_WHITE "\x1b[97m"

     #define ANSI_BG_DEFAULT "\x1b[49m"

     #define ANSI_BG_BLACK "\x1b[40m"
     #define ANSI_BG_RED "\x1b[41m"
     #define ANSI_BG_GREEN "\x1b[42m"
     #define ANSI_BG_YELLOW "\x1b[43m"
     #define ANSI_BG_BLUE "\x1b[44m"
     #define ANSI_BG_MAGENTA "\x1b[45m"
     #define ANSI_BG_CYAN "\x1b[46m"
     #define ANSI_BG_WHITE "\x1b[47m"

     #define ANSI_BG_LIGHT_BLACK "\x1b[100m"
     #define ANSI_BG_LIGHT_RED "\x1b[101m"
     #define ANSI_BG_LIGHT_GREEN "\x1b[102m"
     #define ANSI_BG_LIGHT_YELLOW "\x1b[103m"
     #define ANSI_BG_LIGHT_BLUE "\x1b[104m"
     #define ANSI_BG_LIGHT_MAGENTA "\x1b[105m"
     #define ANSI_BG_LIGHT_CYAN "\x1b[106m"
     #define ANSI_BG_LIGHT_WHITE "\x1b[107m"

    struct ResultPart {
        std::string part_name;
        bool is_trivia;
        std::string description;
        std::string value;
        std::string correct_value;

        ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value);
        ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value, std::string correct_value);
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
    struct IntcodeProgram {
    private:
        std::vector<int> program;

    public:
        explicit IntcodeProgram(std::istream *stream);

        size_t program_length();
        std::vector<int> create_memory();
    };

    struct IntcodeOperation {
        int insn;
        int opcode;

        explicit IntcodeOperation(int insn) : insn(insn) {
            opcode = insn % 100;
        }

        int pmode(int parameter) const {
            int mode = insn / 100;
            for(int i = 0; i < parameter; ++i) {
                mode = mode / 10;
            }
            return mode % 10;
        }
    };

    class IntcodeComputer {
    private:
        std::vector<int> memory;

    public:
        explicit IntcodeComputer(IntcodeProgram *program);

        int &operator[](size_t address);

        std::vector<int> run(const std::vector<int> &input);

    private:
        int get(int parameter_mode, int parameter);
        void set(int parameter_mode, int parameter, int value);
    };

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