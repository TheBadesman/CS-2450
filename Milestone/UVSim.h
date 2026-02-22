#pragma once
#include <string>
#include <array>

class UVSim
{
public:
    std::array<std::string, 100> memory{};
    int accumulator = 0;
    int address = 0;
    bool halted = false;

    void reset();
    void step();

    void loadProgramFromFile(const std::string& filename);

private:
    std::string get(int memory_address);
    void set(int memory_address, const std::string& value);

    void READ(int memory_address, const std::string& input);
    void WRITE(int memory_address);

    void LOAD(int operand);
    void STORE(int operand);
    void ADD(int operand);
    void SUBTRACT(int operand);
    void DIVIDE(int operand);
    void MULTIPLY(int operand);

    void BRANCH(int operand);
    void BRANCHNEG(int operand);
    void BRANCHZERO(int operand);
};
