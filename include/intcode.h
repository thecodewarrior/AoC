#ifndef AOC_INTCODE_H
#define AOC_INTCODE_H

#include <iostream>
#include <vector>


namespace aoc {
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
            for (int i = 0; i < parameter; ++i) {
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
}


#endif //AOC_INTCODE_H
