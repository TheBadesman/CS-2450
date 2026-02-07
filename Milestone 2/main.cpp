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


int get(std::vector<int> &arr, int index){//helper with error checking so you dont have to do that try catch shit on every get of the memory array or vector, whatever.
        try{
                return arr.at(index);
        }catch(std::out_of_range& e){
                std::cout << e.what() << std::endl;
                std::exit(1);
                return 0;
        }
}



void read(std::vector<int> &arr, int index){
        try{
                std::string input;
                std::cout << "Input the sign + or - then the four digit word you want, if data insert opcode 00 then the number you wish thats two digits so if i wanted 69, +0069, if negative 69, -0069: " << std::endl;
                std::cin >> input;
                char sign[2] = {'-', '+'};
                if (input.length() != 5){//length can only be 5 characters long
                        throw std::out_of_range("");
                }else if (input[0] != sign[0] && input[0] != sign[1]){
                        throw std::invalid_argument("Instruction read does not hold a sign, it needs to be a signed number dog");
                }for (size_t i = 1; i < input.length(); i++){
                        if (std::isdigit(input[i]) == false){
                                throw std::invalid_argument("Instruction read is not a number");
                        }
                }
                arr[index] = std::stoi(input);
        }catch(const std::invalid_argument& e){//reference so you dont copy the exception object, didnt know that helped perforance but good shit ig
                std::cout << "You didnt enter a number at all..." << std::endl;
                std::exit(1);
        }catch(const std::out_of_range& e){
                std::cout << "You inputed a number greater than length five(number 4 digits but 5 for potential sign ie -0099)"  << std::endl;
                std::exit(1);
        }
        catch(...){
                std::cout << "Unknown issue :(" << std::endl;
                std::exit(1);
        }
}

void write(std::vector<int> &arr, int index){//idk why its called write, it writes to screen, should be called print...
        std::cout << get(arr, index) << std::endl;
}

//Loads a word from a specific location in memory into the accumulator
void LOAD(){
    
};

//Stores a word from the accumulator into a specific location in memory
void STORE(){
    
};

//Adds a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator)
void ADD(){
    
};

//Subtracts a word from a specific location in memory from the word in the accumulator (leaves the result in the accumulator)
void SUBTRACT(){
    
};

//Divides the word in the accumulator by a word from a specific location in memory (leaves the result in the accumulator).
void DIVIDE(){

};

//multiplys a word from a specific location in memory to the word in the accumulator (leaves the result in the accumulator).
void MULTIPLY(){
    
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
    int address{};

    //opens the file
    ifstream ML(fileName);

    //makes sure the file is open
    if (!ML.is_open()) {
        runtime_error("Error! File is not open!");
    }

    //creating a string for input into the UVSim
    string line;

    //reads the file into the memory
    while (ML >> line){

        //reading the line into the memory
        memory[address] = line;

        //moves to the next slot in the array
        address++;
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

            if (command == "10"){READ();}
            else if (command == "11"){WRITE();}
            else if (command == "20"){LOAD();}
            else if (command == "21"){STORE();}
            else if (command == "30"){ADD();}
            else if (command == "31"){SUBTRACT();}
            else if (command == "32"){DIVIDE();}
            else if (command == "33"){MULTIPLY();}
            else if (command == "40"){BRANCH();}
            else if (command == "41"){BRANCHNEG();}
            else if (command == "42"){BRANCHZERO();}
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
