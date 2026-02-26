#ifndef UVSIM_H
#define UVSIM_H

#include <string>

class UVSim
{
public:
    std::string memory[100]{};
    int accumulator{};
    int address{};

    UVSim();

    // Memory access
    std::string get(int memory_address);

    // I/O Operations
    void READ(int memory_address);
    void WRITE(int memory_address);

    // Load/Store
    void LOAD();
    void STORE();

    // Arithmetic
    int ADD(int accum, std::string location);
    int SUBTRACT(int accum, std::string location);
    int DIVIDE(int accum, std::string location);
    int MULTIPLY(int accum, std::string location);

    // Branching
    int BRANCH(int memory_address);
    int BRANCHNEG(int accumulator, int old_address, int memory_address);
    int BRANCHZERO(int accumulator, int old_address, int memory_address);

    void Execute();
};

#endif