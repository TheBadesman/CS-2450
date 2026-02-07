/*
Group 2
Milestone Two file
Purpose: Creating a UVSim that reads basic ML and outputs a respone
Created: 01/28/2026
*/

//includes for the project
#include <iostream>
#include <fstream>
#include <string>

//using name space std to make coding easier
using namespace std;

string get(string memory[100], int memory_address){
    if (memory_address < 0 || memory_address >= 100) {
        cout << "Memory access out of bounds!" << endl;
        exit(1);
    }
    return memory[memory_address];
}



void READ(string memory[100], int memory_address){
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
                cout << "You inputed a number greater than length five(number 4 digits but 5 for potential sign ie -0099)"  << std::endl;
                exit(1);
        }
        catch(...){
                cout << "Unknown issue :(" << endl;
                exit(1);
        }
}

void WRITE(string memory[100], int memory_address){
    cout << get(memory, memory_address) << endl;
}

//Loads a word from a specific location in memory into the accumulator
void LOAD(){
    
};

//Stores a word from the accumulator into a specific location in memory
void STORE(){
    
};

//Adds a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator)
int ADD(int accum, string memory[100], string memory_address) {
    //I need to VALIDATE INPUT ON EACH MATH FUNCTION AND MAKE ERROR HANDLING FOR THAT
    int location_integer = stoi(memory_address);
    int to_return = accum + stoi(memory[location_integer]);
    return to_return;
};

//Subtracts a word from a specific location in memory from the word in the accumulator (leaves the result in the accumulator)
int SUBTRACT(int accum, string memory[100], string location){
    int location_integer = stoi(location);
    int to_return = accum - stoi(memory[location_integer]);
    return to_return;
};

//Divides the word in the accumulator by a word from a specific location in memory (leaves the result in the accumulator).
int DIVIDE(int accum, string memory[100], string location){
    int location_integer = stoi(location);
    int to_return = accum / stoi(memory[location_integer]);
    return to_return;

};

//multiplys a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator).
int MULTIPLY(int accum, string memory[100], string location){
    int location_integer = stoi(location);
    int to_return = accum * stoi(memory[location_integer]);
    return to_return;
};

//Branchs to a specific location in memory
int BRANCH(int memory_address){
    return memory_address - 1;
};

//Branchs to a specific location in memory if the accumulator is negative.
int BRANCHNEG(int accumulator,int old_address, int memory_address){
    //checks if the accumaltor is less then zero, and branches if it is
    if (accumulator < 0){
        return memory_address - 1;
    }

    //returns the old address if it is not
    return old_address;
};

//Branchs to a specific location in memory if the accumulator is zero
int BRANCHZERO(int accumulator, int old_address, int memory_address){
    //checks if the accumaltor is equal to zero, and branches if it is
    if (accumulator == 0){
        return memory_address - 1;
    }

    //returns the old address if it is not
    return old_address;
};

//function to open a file and read its contents
void reader(std::string fileName){

    string memory[100] {};
    int accumulator{};
    int address{};

    //opens the file
    ifstream ML(fileName);

    //makes sure the file is open
    if (!ML.is_open()) {
        throw runtime_error("Error! File is not open!");
    }

    //creating a string for input into the UVSim
    string line;

    while (ML >> line){
        //exits the program if the file input is too large for memory
        if (address >= 100){
            cout << "Program too large for memory!" << endl;
            exit(1);
        }
    
        //adds the line to the memory and increases the address
        memory[address++] = line;
    }
    
    //resets address to its base value of zero

    address = 0;

    //reads the contents of the file one line at a time, spliting off the command and what word is attached
    while (true){
        string command = memory[address].substr(1, 2);

        //try catch block in case for some reason halt is never called
        try
        {
            if (address == 100)
            {
                throw 505;
            }

            //if else block to run the commands
            if (command == "10"){READ(memory, stoi(memory[address].substr(3,2)));}
            else if (command == "11"){WRITE(memory, stoi(memory[address].substr(3,2)));}
            else if (command == "20"){LOAD();}
            else if (command == "21"){STORE();}
            else if (command == "30"){accumulator = ADD(accumulator, memory, memory[address].substr(3,2));}
            else if (command == "31"){accumulator = SUBTRACT(accumulator, memory, memory[address].substr(3,2));}
            else if (command == "32"){accumulator = DIVIDE(accumulator, memory, memory[address].substr(3,2));}
            else if (command == "33"){accumulator = MULTIPLY(accumulator, memory, memory[address].substr(3,2));}
            else if (command == "40"){address = BRANCH(stoi(memory[address].substr(3,2)));}
            else if (command == "41"){BRANCHNEG(accumulator, address, stoi(memory[address].substr(3,2)));}
            else if (command == "42"){BRANCHZERO(accumulator, address, stoi(memory[address].substr(3,2)));}
            else if (command == "43"){
                //breaks the while true, leaving the loop if halt (command 43) is called
                break;
            }

            //prints the current value of the Accumulator, might add a check to see if it has changed, and make it stop when ever there is a change
            cout << "Accumulator's current value is = " << accumulator << '\n';
        }
        catch(int e)
        {
            cout << '\n' <<"Error! Halt never called! Please check the file and try again!" << '\n';
            break;
        }
        
        address++;
        
    }
}

int main()
{
    //variable for the file name
    string filename;

    //asking the user for the file name and using it to run the Read/UVSim
    cout << "Enter the txt file with commands that you would like read: ";
    cin >> filename; // Reads until whitespace

    reader(filename);
    
    return 0;
}
