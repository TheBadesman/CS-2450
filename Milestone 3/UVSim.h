#ifndef UVSIM_H
#define UVSIM_H

#include <string>

class UVSim
{
public:
    std::string memory[100]{};
    int accumulator{};
    int address{};

    bool waitingForFilename = false;
    std::string pendingFilename = "";
    std::string consoleLog{};

    UVSim();

    //i add file reading logic, I couldnt seem to find it in latest version, the old version had part of a console.h but...
    void loadMLProgram();
    

    //Console Functions
    void AppendOutput(const std::string& text);
    void ClearOutput();

    void ProvideInput(const std::string& input);
    void loadFileFromName(const std::string& filename);    


    // Memory access
    std::string get(int memory_address);

    // I/O Operations
    void READ(const std::string& input); //compiler error from: UVSim::READ(const std::string& input), this function is declared here, no need to say its a member function here, only in definitions, .cpp file 
 
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

    //runs the files and builds / returns the strings for the console
    bool Execute();
};

#endif
