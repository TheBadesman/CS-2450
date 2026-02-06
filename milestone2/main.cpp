#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*

READ = 10 Read a word from the keyboard into a specific location in memory.
WRITE = 11 Write a word from a specific location in memory to screen.

Load/store operations:
LOAD = 20 Load a word from a specific location in memory into the accumulator.
STORE = 21 Store a word from the accumulator into a specific location in memory.

Arithmetic operation:
ADD = 30 Add a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator)
SUBTRACT = 31 Subtract a word from a specific location in memory from the word in the accumulator (leave the result in the accumulator)
DIVIDE = 32 Divide the word in the accumulator by a word from a specific location in memory (leave the result in the accumulator).
MULTIPLY = 33 multiply a word from a specific location in memory to the word in the accumulator (leave the result in the accumulator).

Control operation:
BRANCH = 40 Branch to a specific location in memory
BRANCHNEG = 41 Branch to a specific location in memory if the accumulator is negative.
BRANCHZERO = 42 Branch to a specific location in memory if the accumulator is zero.
HALT = 43 Pause the program
 */
void print_vec(std::vector<int> &arr){
	for (size_t i = 0; i < arr.size(); i++){
		std::cout << "loc: " << i << ' ' << arr[i] << std::endl;
	}
}

void read(std::vector<int> &arr, int index){//reference to vector
	try{
		std::string input;
		std::cout << "Input the four digit word you want, if data insert opcode 00 then the number you wish thats two digits so if i wanted 69, 0069, if negative 69, -0069: " << std::endl;
		std::cin >> input;
		if (input.length() > 5 || input.length() < 4){//length can only be 4 or 5 characters long
			throw std::out_of_range("");
		}
		arr[index] = std::stoi(input);
	}catch(const std::invalid_argument& e){//reference so you dont copy the exception object, didnt know that helped perforance but good shit ig
		std::cout << "You didnt enter a number at all..." << std::endl;
	}catch(const std::out_of_range& e){
		std::cout << "You inputed a number greater than length five(number 4 digits but 5 for potential sign ie -0099)"  << std::endl;
	}
	catch(...){
		std::cout << "Unknown issue :(" << std::endl;
	}
}

int main() {
	std::ifstream file("Test1.txt");

	std::vector<int> memory;/*initializes all 100 elements to zeros if vector(100)... gotta reserve space not vector(100)*/
	memory.reserve(100);

	int file_input;
	while (file >> file_input) { //could do a for loop then have it check if the statement was true per iter. but that seems more inefficient than this
		memory.push_back(file_input);//inserts values at i then increments after,
	}
	//while loop for executing all instructions, keep looping while array holds stuff
	read(memory, 0);
	print_vec(memory);
	/*
	while (memory.size() > 0){
		

		//last thing of course, remove instruction at index we want
		memory.erase(memory.begin() + 2);//element at index 2 is removed
	}
	*/
	return 0;
}
