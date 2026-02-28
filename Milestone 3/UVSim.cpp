/*
The main class for the Milestone 2 UVSIM
*/

#include "UVSim.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

UVSim::UVSim(){
    accumulator = 0;
    address = 0;
}

void UVSim::AppendOutput(const std::string& text)
{

    if (consoleLog.length() > 5000){consoleLog.clear();}

    consoleLog += text + "\n";
}

void UVSim::ClearOutput()
{
    consoleLog.clear();
}

string UVSim::get(int memory_address){
    if (memory_address < 0 || memory_address >= 100) {
        AppendOutput("Memory access out of bounds!");
        throw std::runtime_error("message");
    }
    return memory[memory_address];
}

void UVSim::READ(const std::string& input)
{
    // Validate instruction format first
    if (memory[address].length() < 5)
    {
        AppendOutput("Invalid instruction format in memory");
        throw runtime_error("Invalid instruction format");
    }

    // Validate user input
    if (input.length() != 5)
    {
        AppendOutput("Input must be 5 characters (+0000 or -0000)");
        throw runtime_error("Invalid input length");
    }

    if (input[0] != '+' && input[0] != '-')
    {
        AppendOutput("Input must start with + or -");
        throw runtime_error("Invalid input sign");
    }

    for (int i = 1; i < 5; i++)
    {
        if (!isdigit(input[i]))
        {
            AppendOutput("Input must contain digits only");
            throw runtime_error("Input contains non-digit characters");
        }
    }

    try
    {
        // Extract operand safely
        string operandStr = memory[address].substr(3, 2);

        int operand = stoi(operandStr);

        if (operand < 0 || operand >= 100)
        {
            AppendOutput("READ memory address out of bounds");
            throw runtime_error("Memory address out of bounds");
        }

        memory[operand] = input;
    }
    catch (const exception& e)
    {
        AppendOutput(e.what());
        throw;
    }
}

void UVSim::WRITE(int memory_address){
    AppendOutput("The word stored in " + std::to_string(memory_address) + " is " + get(memory_address));
}

void UVSim::LOAD(){
        int operand = stoi(memory[address].substr(3,2));
        accumulator = stoi(memory[operand]);
}

void UVSim::STORE(){
        int operand = stoi(memory[address].substr(3,2));
        string val = (accumulator >= 0 ? "+" : "") + to_string(accumulator);
        while (val.length() < 5) val.insert(1, "0");
        memory[operand] = val;
}

int UVSim::ADD(int accum, string location){
        int location_integer = stoi(location);
        try {
                int to_return = accum + stoi(memory[location_integer]);
                return to_return;
        }
        catch (...) {
                AppendOutput("Please input only numbers");
                throw runtime_error("Invalid ADD operation");
        }
}

int UVSim::SUBTRACT(int accum, string location){
        int location_integer = stoi(location);
        int to_return = accum - stoi(memory[location_integer]);
        return to_return;
}

int UVSim::DIVIDE(int accum, string location){
        int location_integer = stoi(location);
        if (memory[location_integer] == "0") {
                throw runtime_error("Divide by zero error");
        }
        else {
                int to_return = accum / stoi(memory[location_integer]);
                return to_return;
        }
}

int UVSim::MULTIPLY(int accum, string location){
        int location_integer = stoi(location);
        int to_return = accum * stoi(memory[location_integer]);
        return to_return;
}

int UVSim::BRANCH(int memory_address){
        return memory_address;
}

int UVSim::BRANCHNEG(int accumulator,int old_address, int memory_address){
        if (accumulator < 0){
                return memory_address;
        }
        return old_address;
}

int UVSim::BRANCHZERO(int accumulator, int old_address, int memory_address){
        if (accumulator == 0){
                return memory_address;
        }
        return old_address;
}

bool UVSim::Execute(){
        string command = memory[address].substr(1,2);
        string location = memory[address].substr(3,2);
        bool jumped = false;

        if (command == "10") {AppendOutput("Double check input, should start with if it is positive or negative, followed by the four digit input"); return false;}
            else if (command == "11"){WRITE(stoi(location));}
            else if (command == "20"){LOAD();}
            else if (command == "21"){STORE();}
            else if (command == "30"){accumulator = ADD(accumulator, location);}
            else if (command == "31"){accumulator = SUBTRACT(accumulator, location);}
            else if (command == "32"){accumulator = DIVIDE(accumulator, location);}
            else if (command == "33"){accumulator = MULTIPLY(accumulator, location);}
            else if (command == "40"){address = BRANCH(stoi(location)); jumped = true;}
            else if (command == "41"){address = BRANCHNEG(accumulator, address, stoi(location)); jumped = true;}
            else if (command == "42"){address = BRANCHZERO(accumulator, address, stoi(location)); jumped = true;}
            else if (command == "43"){
                AppendOutput("Program halted.");
                address = 0;
                return false;
            }
        //If we are not doing a read, increase the address
        if (!jumped && command != "10"){
                address++;
        }
        //exits the execute function
        return true;
}