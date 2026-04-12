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
    if (memory_address < 0 || memory_address >= 250) {
        AppendOutput("Memory access out of bounds!");
        throw std::runtime_error("message");
    }
    return memory[memory_address];
}

void UVSim::READ(const std::string& input)
{
    // Validate instruction format first
    if (memory[address].length() < 7)
    {
        AppendOutput("Invalid instruction format in memory");
        throw runtime_error("Invalid instruction format");
    }

    // Validate user input
    if (input.length() != 7)
    {
        AppendOutput("Input must be 7 characters (+000000 or -000000)");
        throw runtime_error("Invalid input length");
    }

    if (input[0] != '+' && input[0] != '-')
    {
        AppendOutput("Input must start with + or -");
        throw runtime_error("Invalid input sign");
    }

    for (int i = 1; i < 7; i++)
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
        string operandStr = memory[address].substr(4,3);

        int operand = stoi(operandStr);

        if (operand < 0 || operand >= 250)
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
        int operand = stoi(memory[address].substr(4,3));
        accumulator = stoi(memory[operand]);
}

void UVSim::STORE(){
        int operand = stoi(memory[address].substr(4,3));
        string val = (accumulator >= 0 ? "+" : "") + to_string(accumulator);
        while (val.length() < 7) val.insert(1, "0");
        memory[operand] = val;
}

int UVSim::ADD(int accum, string location){
        int location_integer = stoi(location);
        try {
            return accum + stoi(memory[location_integer]);
        }
        catch (...) {
                AppendOutput("Please input only numbers");
                throw runtime_error("Invalid ADD operation");
        }
}

int UVSim::SUBTRACT(int accum, string location){
        int location_integer = stoi(location);
        return accum - stoi(memory[location_integer]);
}

int UVSim::DIVIDE(int accum, string location){
        int location_integer = stoi(location);
        if (stoi(memory[location_integer]) == 0) {
                throw runtime_error("Divide by zero error");
        }
        else {
            return accum / stoi(memory[location_integer]);
        }
}

int UVSim::MULTIPLY(int accum, string location){
        int location_integer = stoi(location);
        return accum * stoi(memory[location_integer]);
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
        string command = memory[address].substr(1,3);
        string location = memory[address].substr(4,3);
        bool jumped = false;

        if (command == "010") {AppendOutput("Double check input, should start with if it is positive or negative, followed by the four digit input"); return false;}
            else if (command == "011"){WRITE(stoi(location));}
            else if (command == "020"){LOAD();}
            else if (command == "021"){STORE();}
            else if (command == "030"){accumulator = ADD(accumulator, location);}
            else if (command == "031"){accumulator = SUBTRACT(accumulator, location);}
            else if (command == "032"){accumulator = DIVIDE(accumulator, location);}
            else if (command == "033"){accumulator = MULTIPLY(accumulator, location);}
            else if (command == "040"){address = BRANCH(stoi(location)); jumped = true;}
            else if (command == "041"){address = BRANCHNEG(accumulator, address, stoi(location)); jumped = true;}
            else if (command == "042"){address = BRANCHZERO(accumulator, address, stoi(location)); jumped = true;}
            else if (command == "043"){
                AppendOutput("Program halted.");
                address = 0;
                return false;
            }
        //If we are not doing a read, increase the address
        if (!jumped && command != "010"){
                address++;
        }
        //exits the execute function
        return true;
}

string UVSim::Convert(const string oldWord){
    string sign = oldWord.substr(0,1);
    string opcode = oldWord.substr(1,2);
    string operand = oldWord.substr(3,2);

    return sign + "0" + opcode + "0" + operand;
}