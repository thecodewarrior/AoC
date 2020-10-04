#ifndef AOC_MAIN_H
#define AOC_MAIN_H

#include <string>

int main(int argc, char *argv[]);

std::string center(std::string pad, size_t width, std::string text, size_t visual_width);

class PadBuf : public std::stringbuf {
    std::ostream &out;
    std::string newline;
    bool was_nl{};
public:
    PadBuf(std::ostream &out, std::string newline);

protected:
    int overflow(int_type __c) override;
};

#endif //AOC_MAIN_H
