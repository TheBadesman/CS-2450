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

string UVSim::get(int memory_address){
    if (memory_address < 0 || memory_address >= 100) {
        cout << "Memory access out of bounds!" << endl;
        exit(1);
    }
    return memory[memory_address];
}

void UVSim::READ(int memory_address){
    try{
            string input;
            cout << "Input the sign + or - then the four digit word you want, if data insert opcode 00 then the number you wish thats two digits so if i wanted 69, +0069, if negative 69, -0069: " << std::endl;
            cin >> input;
            if (input.length() != 5){
                    throw out_of_range("Your input is either too short or too long!");
            }else if (input[0] != '-' && input[0] != '+'){
                    throw invalid_argument("Instruction read does not hold a sign, it needs to be a signed number dog");
            }
            for (size_t i = 1; i < input.length(); i++){
                    if (isdigit(input[i]) == false){
                            throw invalid_argument("Instruction read is not a number");
                    }
            }
            memory[memory_address] = input;
    }catch(const invalid_argument& e){
            cout << "You didnt enter a number at all..." << endl;
            exit(1);
    }catch(const out_of_range& e){
            cout << "You inputed a number greater or lower than length five(number 4 digits but 5 for potential sign ie -0099)"  << std::endl;
            exit(1);
    }
    catch(...){
            cout << "Unknown issue :(" << endl;
            exit(1);
    }
}

void UVSim::WRITE(int memory_address){
    cout << "The word stored in " << memory_address << " is " << get(memory_address) << endl;
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
            cout << "Please input only numbers" << endl;
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

void UVSim::Execute(){
        string command = memory[address].substr(1,2);
        string location = memory[address].substr(3,2);

        if (command == "10"){READ(stoi(location));}
            else if (command == "11"){WRITE(stoi(location));}
            else if (command == "20"){LOAD();}
            else if (command == "21"){STORE();}
            else if (command == "30"){accumulator = ADD(accumulator, location);}
            else if (command == "31"){accumulator = SUBTRACT(accumulator, location);}
            else if (command == "32"){accumulator = DIVIDE(accumulator, location);}
            else if (command == "33"){accumulator = MULTIPLY(accumulator, location);}
            else if (command == "40"){address = BRANCH(stoi(location));}
            else if (command == "41"){address = BRANCHNEG(accumulator, address, stoi(location));}
            else if (command == "42"){address = BRANCHZERO(accumulator, address, stoi(location));}
            else if (command == "43"){
                address = 0;
                return;
            }

        address++;
        return;
}