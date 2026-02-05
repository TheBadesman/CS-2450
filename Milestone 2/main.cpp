/*
Group 2
Milestone Two file
Purpose: Creating a UVSim that reads basic ML and outputs a respone
Created: 01/28/2026
*/

#include <iostream>
#include <fstream>
#include <string>

//function to open a file and read its contents
void reader(std::string fileName){
    //opens the file
    std::ifstream ML(fileName);

    //makes sure the file is open
    if (!ML.is_open()) {
        std::runtime_error("Error! File is not open!");
    }

    //creating a string to input into the file
    std::string test;

    //reads the contents of the file
    while (ML >> test){
        std::cout << test << std::endl;
    }

    //closes the file
    ML.close();
}

int main()
{
    std::string filename = "Test1.txt";

    reader(filename);
    
    return 0;
}
