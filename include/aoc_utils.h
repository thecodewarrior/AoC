#ifndef _AOC_UTILS_H
#define _AOC_UTILS_H
#include <iostream>
#include <vector>

namespace aoc
{
    // const char *ansi_reset = "\x1b[0m";
    // const char *ansi_bold_on = "\x1b[1m";
    // const char *ansi_bold_off = "\x1b[22m";
    // const char *ansi_underscore_on = "\x4b[4m";
    // const char *ansi_underscore_off = "\x1b[24m";
    // const char *ansi_blink_on = "\x4b[5m";
    // const char *ansi_blink_off = "\x1b[25m";

    // const char *ansi_fg_default = "\x1b[39m";

    // const char *ansi_fg_black = "\x1b[30m";
    // const char *ansi_fg_red = "\x1b[31m";
    // const char *ansi_fg_green = "\x1b[32m";
    // const char *ansi_fg_yellow = "\x1b[33m";
    // const char *ansi_fg_blue = "\x1b[34m";
    // const char *ansi_fg_magenta = "\x1b[35m";
    // const char *ansi_fg_cyan = "\x1b[36m";
    // const char *ansi_fg_white = "\x1b[37m";

    // const char *ansi_fg_light_black = "\x1b[90m";
    // const char *ansi_fg_light_red = "\x1b[91m";
    // const char *ansi_fg_light_green = "\x1b[92m";
    // const char *ansi_fg_light_yellow = "\x1b[93m";
    // const char *ansi_fg_light_blue = "\x1b[94m";
    // const char *ansi_fg_light_magenta = "\x1b[95m";
    // const char *ansi_fg_light_cyan = "\x1b[96m";
    // const char *ansi_fg_light_white = "\x1b[97m";

    // const char *ansi_bg_default = "\x1b[49m";

    // const char *ansi_bg_black = "\x1b[40m";
    // const char *ansi_bg_red = "\x1b[41m";
    // const char *ansi_bg_green = "\x1b[42m";
    // const char *ansi_bg_yellow = "\x1b[43m";
    // const char *ansi_bg_blue = "\x1b[44m";
    // const char *ansi_bg_magenta = "\x1b[45m";
    // const char *ansi_bg_cyan = "\x1b[46m";
    // const char *ansi_bg_white = "\x1b[47m";

    // const char *ansi_bg_light_black = "\x1b[100m";
    // const char *ansi_bg_light_red = "\x1b[101m";
    // const char *ansi_bg_light_green = "\x1b[102m";
    // const char *ansi_bg_light_yellow = "\x1b[103m";
    // const char *ansi_bg_light_blue = "\x1b[104m";
    // const char *ansi_bg_light_magenta = "\x1b[105m";
    // const char *ansi_bg_light_cyan = "\x1b[106m";
    // const char *ansi_bg_light_white = "\x1b[107m";

    struct IntcodeProgram
    {
    private:
        std::vector<int> program;

    public:
        IntcodeProgram(std::istream *stream);
        std::vector<int> create_memory();
    };

    class IntcodeComputer
    {
    private:
        bool halted = false;
        size_t pc = 0;
        std::vector<int> memory;

    public:
        IntcodeComputer(IntcodeProgram *program);
        int &operator[](size_t address);
        void reset();
        void run();
    };

} // namespace aoc

#endif