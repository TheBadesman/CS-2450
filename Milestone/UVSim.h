#pragma once
#include <string>
#include <vector>

class UVSim
{
public:
    UVSim();

    std::vector<int> memory;
    int accumulator;
    int programCounter;
    bool halted;
    int address;
    /*bool loadProgram(const std::string& filename);
    void step();
    void reset();

    bool isHalted() const;

    int getAccumulator() const;
    int getProgramCounter() const;
   */
};
