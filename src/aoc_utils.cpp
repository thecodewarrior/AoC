#include "aoc_utils.h"
#include <fstream>
#include <string>
#include <utility>

namespace aoc {
    IntcodeProgram::IntcodeProgram(std::istream *stream) {
        std::string line;
        while (getline(*stream, line, ',')) {
            program.push_back(std::stoi(line));
        }
    }

    size_t IntcodeProgram::program_length() {
        return program.size();
    }

    std::vector<int> IntcodeProgram::create_memory() {
        return std::vector<int>(program);
    }

    IntcodeComputer::IntcodeComputer(IntcodeProgram *program) : memory(program->create_memory()) {
    }

    int &IntcodeComputer::operator[](size_t address) {
        return memory[address];
    }

    std::vector<int> IntcodeComputer::run(const std::vector<int> &input) {
        bool halted = false;
        size_t pc = 0;
        size_t inpos = 0;
        std::vector<int> output;

        while (!halted) {
            IntcodeOperation op(memory[pc]);
            switch (op.opcode) {
                case 1: {
                    int a = get(op.pmode(0), memory[pc + 1]);
                    int b = get(op.pmode(1), memory[pc + 2]);
                    set(op.pmode(2), memory[pc + 3], a + b);
                    pc += 4;
                }
                    break;
                case 2: {
                    int a = get(op.pmode(0), memory[pc + 1]);
                    int b = get(op.pmode(1), memory[pc + 2]);
                    set(op.pmode(2), memory[pc + 3], a * b);
                    pc += 4;
                }
                    break;
                case 3: {
                    set(op.pmode(0), memory[pc + 1], input[inpos++]);
                    pc += 2;
                }
                    break;
                case 4: {
                    output.push_back(get(op.pmode(0), memory[pc + 1]));
                    pc += 2;
                }
                    break;
                case 5: {
                    int test = get(op.pmode(0), memory[pc + 1]);
                    int jump = get(op.pmode(1), memory[pc + 2]);
                    pc += 3;
                    if(test != 0)
                        pc = jump;
                }
                    break;
                case 6: {
                    int test = get(op.pmode(0), memory[pc + 1]);
                    int jump = get(op.pmode(1), memory[pc + 2]);
                    pc += 3;
                    if(test == 0)
                        pc = jump;
                }
                    break;
                case 7: {
                    int a = get(op.pmode(0), memory[pc + 1]);
                    int b = get(op.pmode(1), memory[pc + 2]);
                    set(op.pmode(2), memory[pc + 3], a < b ? 1 : 0);
                    pc += 4;
                }
                    break;
                case 8: {
                    int a = get(op.pmode(0), memory[pc + 1]);
                    int b = get(op.pmode(1), memory[pc + 2]);
                    set(op.pmode(2), memory[pc + 3], a == b ? 1 : 0);
                    pc += 4;
                }
                    break;
                case 99:
                    halted = true;
                    break;
                default:
                    std::cout << "Unknown opcode " << op.opcode << std::endl;
                    halted = true;
            }
        }
        return output;
    }

    int IntcodeComputer::get(int parameter_mode, int parameter) {
        switch (parameter_mode) {
            case 0:
                return memory[parameter];
            case 1:
                return parameter;
            default:
                std::cout << "Unknown parameter mode " << parameter_mode << std::endl;
                return 0;
        }
    }

    void IntcodeComputer::set(int parameter_mode, int parameter, int value) {
        switch (parameter_mode) {
            case 0:
                memory[parameter] = value;
                break;
            case 1:
                std::cout << "Can't write to immediate mode parameter" << std::endl;
                break;
            default:
                std::cout << "Unknown parameter mode " << parameter_mode << std::endl;
        }
    }

    DayResult::DayResult() = default;

    DayResult::DayResult(int return_code) : return_code(return_code) {}

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, std::string value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)), value(std::move(value)) {
    }

    ResultPart::ResultPart(std::string part_name, bool is_trivia, std::string description, int value) :
            part_name(std::move(part_name)), is_trivia(is_trivia), description(std::move(description)),
            value(std::to_string(value)) {
    }

    ResultPart::ResultPart() = default;
} // namespace aoc