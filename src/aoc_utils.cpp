#include "aoc_utils.h"
#include <fstream>
#include <string>

namespace aoc
{
    IntcodeProgram::IntcodeProgram(std::istream *stream)
    {
        std::string line;
        while (getline(*stream, line, ','))
        {
            program.push_back(std::stoi(line));
        }

        printf("Loaded program with length %d\n", (int)program.size());
    }
    
    std::vector<int> IntcodeProgram::create_memory() 
    {
        return std::vector<int>(program);
    }

    IntcodeComputer::IntcodeComputer(IntcodeProgram *program) : memory(program->create_memory())
    {
    }

    int &IntcodeComputer::operator[](size_t address)
    {
        return memory[address];
    }

    void IntcodeComputer::reset()
    {
        halted = false;
        pc = 0;
    }

    void IntcodeComputer::run()
    {
        while (!halted)
        {
            int opcode = memory[pc];
            switch (opcode)
            {
            case 1:
            {
                int a = memory[pc + 1];
                int b = memory[pc + 2];
                int out = memory[pc + 3];
                memory[out] = memory[a] + memory[b];
                pc += 4;
            }
            break;
            case 2:
            {
                int a = memory[pc + 1];
                int b = memory[pc + 2];
                int out = memory[pc + 3];
                memory[out] = memory[a] * memory[b];
                pc += 4;
            }
            break;
            case 99:
                halted = true;
                break;
            default:
                std::cout << "Unknown opcode " << opcode;
                return;
            }
        }
    }
} // namespace aoc