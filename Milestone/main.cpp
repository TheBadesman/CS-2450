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

//using name space std to make coding easier
using namespace std;



//function to open a file and read its contents
void reader(std::string fileName){

    UVSim Simulator;

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
        if (Simulator.address >= 100){
            cout << "Program too large for memory!" << endl;
            exit(1);
        }
    
        //adds the line to the memory and increases the address
        Simulator.memory[Simulator.address++] = line;
    }
    
    //resets address to its base value of zero

    Simulator.address = 0;

    //reads the contents of the file one line at a time, spliting off the command and what word is attached
    while (true){
        if (Simulator.memory[Simulator.address].length() != 5) {
            throw runtime_error("Invalid instruction length");
        }

        string command = Simulator.memory[Simulator.address].substr(1, 2);

        //try catch block in case for some reason halt is never called
        try
        {
            if (Simulator.address < 0 || Simulator.address >= 100) {
                throw runtime_error("Memory address out of bounds");
            }

            //if else block to run the commands
            if (command == "10"){Simulator.READ(stoi(Simulator.memory[Simulator.address].substr(3,2)));}
            else if (command == "11"){Simulator.WRITE(stoi(Simulator.memory[Simulator.address].substr(3,2)));}
            else if (command == "20"){Simulator.LOAD(Simulator.address, Simulator.accumulator);}
            else if (command == "21"){Simulator.STORE(Simulator.address, Simulator.accumulator);}
            else if (command == "30"){Simulator.accumulator = Simulator.ADD(Simulator.accumulator, Simulator.memory[Simulator.address].substr(3,2));}
            else if (command == "31"){Simulator.accumulator = Simulator.SUBTRACT(Simulator.accumulator, Simulator.memory[Simulator.address].substr(3,2));}
            else if (command == "32"){Simulator.accumulator = Simulator.DIVIDE(Simulator.accumulator, Simulator.memory[Simulator.address].substr(3,2));}
            else if (command == "33"){Simulator.accumulator = Simulator.MULTIPLY(Simulator.accumulator, Simulator.memory[Simulator.address].substr(3,2));}
            else if (command == "40"){Simulator.address = Simulator.BRANCH(stoi(Simulator.memory[Simulator.address].substr(3,2)));
                continue;    
            }
            else if (command == "41"){Simulator.address = Simulator.BRANCHNEG(Simulator.accumulator, Simulator.address, stoi(Simulator.memory[Simulator.address].substr(3,2)));
                continue;
            }
            else if (command == "42"){Simulator.address = Simulator.BRANCHZERO(Simulator.accumulator, Simulator.address, stoi(Simulator.memory[Simulator.address].substr(3,2)));
                continue;
            }
            else if (command == "43"){
                //breaks the while true, leaving the loop if halt (command 43) is called
                break;
            }

            //prints the current value of the Accumulator, might add a check to see if it has changed, and make it stop when ever there is a change
            cout << "Accumulator's current value is = " << Simulator.accumulator << '\n';
        }
        catch(const exception& e)
        {
            cout << "\nError: " << e.what() << endl;
            break;
        }
        
        Simulator.address++;
        
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
} */