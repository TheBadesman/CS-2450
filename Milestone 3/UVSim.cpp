/*
The main class for the Milestone 2 UVSIM
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

class UVSim
{
public:

    string memory[100]{};
    int accumulator{};
    int address{};

    UVSim(){
        accumulator = 0;
        address = 0;
    }

    string get(string memory[100], int memory_address){
    if (memory_address < 0 || memory_address >= 100) {
        cout << "Memory access out of bounds!" << endl;
        exit(1);
        }
    return memory[memory_address];
    }


    void READ(int memory_address){
        try{
                string input;
                cout << "Input the sign + or - then the four digit word you want, if data insert opcode 00 then the number you wish thats two digits so if i wanted 69, +0069, if negative 69, -0069: " << std::endl;
                cin >> input;
                if (input.length() != 5){//length can only be 5 characters long
                        throw out_of_range("Your input is either too short or too long!");
                }else if (input[0] != '-' && input[0] != '+'){
                        throw invalid_argument("Instruction read does not hold a sign, it needs to be a signed number dog");
                }for (size_t i = 1; i < input.length(); i++){
                        if (isdigit(input[i]) == false){
                                throw invalid_argument("Instruction read is not a number");
                        }
                }
                memory[memory_address] = input;
        }catch(const invalid_argument& e){//reference so you dont copy the exception object
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

    void WRITE(int memory_address){
        cout << "The word stored in " << memory_address << " is " << get(memory, memory_address) << endl;
    }

    //Loads a word from a specific location in memory into the accumulator
    void LOAD(int& address, int& accumulator){
            int operand = stoi(memory[address].substr(3,2));
            accumulator = stoi(memory[operand]);
    };

    //Stores a word from the accumulator into a specific location in memory
    void STORE(int& address, int& accumulator){
            int operand = stoi(memory[address].substr(3,2));
            string val = (accumulator >= 0 ? "+" : "") + to_string(accumulator);
            while (val.length() < 5) val.insert(1, "0");
            memory[operand] = val;
    };

    //Adds a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator)
    int ADD(int accum, string location){
        //I need to VALIDATE INPUT ON EACH MATH FUNCTION AND MAKE ERROR HANDLING FOR THAT
        int location_integer = stoi(location);
        try {
            int to_return = accum + stoi(memory[location_integer]);
            return to_return;
        }
        catch (...) {
            cout << "Please input only numbers" << endl;
            throw runtime_error("Invalid ADD operation");
        }
    };

    //Subtracts a word from a specific location in memory from the word in the accumulator (leaves the result in the accumulator)
    int SUBTRACT(int accum, string location){
        int location_integer = stoi(location);
        int to_return = accum - stoi(memory[location_integer]);
        return to_return;
    };

    //Divides the word in the accumulator by a word from a specific location in memory (leaves the result in the accumulator).
    int DIVIDE(int accum, string location){
        int location_integer = stoi(location); //Catch divide by zero
        if (memory[location_integer] == "0") {
            //cerr << "Divide by zero error" << endl;
            throw runtime_error("Divide by zero error");
        }
        else {
            int to_return = accum / stoi(memory[location_integer]);
            return to_return;
        }


    };

    //multiplys a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator).
    int MULTIPLY(int accum, string location){
        int location_integer = stoi(location);
        int to_return = accum * stoi(memory[location_integer]);
        return to_return;
    };

    //Branchs to a specific location in memory
    int BRANCH(int memory_address){
        return memory_address;
    };

    //Branchs to a specific location in memory if the accumulator is negative.
    int BRANCHNEG(int accumulator,int old_address, int memory_address){
        //checks if the accumaltor is less then zero, and branches if it is
        if (accumulator < 0){
            return memory_address;
        }

        //returns the old address if it is not
        return old_address;
    };

    //Branchs to a specific location in memory if the accumulator is zero
    int BRANCHZERO(int accumulator, int old_address, int memory_address){
        //checks if the accumaltor is equal to zero, and branches if it is
        if (accumulator == 0){
            return memory_address;
        }

        //returns the old address if it is not
        return old_address;
    };
};
