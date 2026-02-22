#pragma once
#include <string>
#include <vector>

class UVSim
{
private:
    std::vector<int> memory;
    int accumulator;
    int programCounter;
    bool halted;

public:
    UVSim();

    bool loadProgram(const std::string& filename);
    void step();
    void reset();

    bool isHalted() const;

    int getAccumulator() const;
    int getProgramCounter() const;
};
