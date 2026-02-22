#ifndef UVSIM_H
#define UVSIM_H

#include <string>

class UVSim
{
public:
    // Memory and registers
    std::string memory[100]{};
    int accumulator;
    int address;

    // Memory access
    std::string get(int memory_address);

    // I/O operations
    void READ(int memory_address);
    void WRITE(int memory_address);

    // Register operations
    void LOAD(int address, int& accumulator);
    void STORE(int address, int& accumulator);

    // Arithmetic operations
    int ADD(int accum, int location);
    int SUBTRACT(int accum, int location);
    int DIVIDE(int accum, int location);
    int MULTIPLY(int accum, int location);

    // Branch operations
    int BRANCH(int memory_address);
    int BRANCHNEG(int accumulator, int old_address, int memory_address);
    int BRANCHZERO(int accumulator, int old_address, int memory_address);
};

#endif