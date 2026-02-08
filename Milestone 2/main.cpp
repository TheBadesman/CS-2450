/*
Group 2
Milestone Two file
Purpose: Creating a UVSim that reads basic ML and outputs a respone
Created: 01/28/2026
*/

//includes for the project
#include "Milestone2UnitTests.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

//using name space std to make coding easier
using namespace std;

//Reads a word from the keyboard into a specific location in memory
void READ(){
    
};

//Writes a word from a specific location in memory to screen
void WRITE(){
    
};

//Loads a word from a specific location in memory into the accumulator
void LOAD(){
    
};

//Stores a word from the accumulator into a specific location in memory
void STORE(){
    
};

//Adds a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator)
int ADD(int accum, string memory[100], string location) {
    //I need to VALIDATE INPUT ON EACH MATH FUNCTION AND MAKE ERROR HANDLING FOR THAT
    int location_integer = stoi(location);
    try {
        int to_return = accum + stoi(memory[location_integer]);
        return to_return;
    }
    catch (...) {
        cout << "Please input only numbers" << endl;    }
};

//Subtracts a word from a specific location in memory from the word in the accumulator (leaves the result in the accumulator)
int SUBTRACT(int accum, string memory[100], string location){
    int location_integer = stoi(location);
    int to_return = accum - stoi(memory[location_integer]);
    return to_return;
};

//Divides the word in the accumulator by a word from a specific location in memory (leaves the result in the accumulator).
int DIVIDE(int accum, string memory[100], string location){
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
int MULTIPLY(int accum, string memory[100], string location){
    int location_integer = stoi(location);
    int to_return = accum * stoi(memory[location_integer]);
    return to_return;
};

//Branchs to a specific location in memory
void BRANCH(){
    
};

//Branchs to a specific location in memory if the accumulator is negative.
void BRANCHNEG(){
    
};

//Branchs to a specific location in memory if the accumulator is zero
void BRANCHZERO(){
    
};

//function to open a file and read its contents
void reader(std::string fileName){

    string memory[100] {};
    int accumulator{};

    //opens the file
    ifstream ML(fileName);

    //makes sure the file is open
    if (!ML.is_open()) {
        runtime_error("Error! File is not open!");
    }

    //creating a string for input into the UVSim
    string line;

    //reads the contents of the file one line at a time, spliting off the command and what word is attached
    while (ML >> line){
        string command = line.substr(1, 2);

        //if else block to run different commands based off of the input read
        if (command == "10"){READ();}
        else if (command == "11"){WRITE();}
        else if (command == "20"){LOAD();}
        else if (command == "21"){STORE();}
        else if (command == "30"){accumulator = ADD(accumulator, memory, line.substr(3, 2)); }
        else if (command == "31"){accumulator = SUBTRACT(accumulator, memory, line.substr(3, 2)); }
        else if (command == "32"){accumulator = DIVIDE(accumulator, memory, line.substr(3,2));}
        else if (command == "33"){accumulator = MULTIPLY(accumulator, memory, line.substr(3, 2)); }
        else if (command == "40"){BRANCH();}
        else if (command == "41"){BRANCHNEG();}
        else if (command == "42"){BRANCHZERO();}
        else if (command == "43"){
            //closes the file
            ML.close();

            //because there is no more cases it now leaves the function
        }   
    }
}

/*int main()
{
    //variable for the file name
    string filename;

    //asking the user for the file name and using it to run the Read/UVSim
    cout << "Enter the txt file with commands that you would like read: ";
    cin >> filename; // Reads until whitespace

    reader(filename);
    
    return 0;
}*/
