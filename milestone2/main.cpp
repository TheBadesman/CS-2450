#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


//helper function section
std::vector<std::string> get_all_txt(){
	namespace fs = std::filesystem;
	std::vector<std::string> vec;
	for (const auto& entry : fs::directory_iterator(fs::current_path())){
		if (entry.is_regular_file() && entry.path().extension() == ".txt") {//regular file means not a folder, not a .gitignore, nothing weird like that
			std::string file = entry.path().filename().string();
			vec.push_back(file);
		}
	}
	return vec;
}

void print_vec(std::vector<int> &arr){
	for (size_t i = 0; i < arr.size(); i++){
		std::cout << "loc: " << i << ' ' << arr[i] << std::endl;
	}
}

int get(std::vector<int> &arr, int index){
	try{
		return arr.at(index);
	}catch(std::out_of_range& e){
		std::cout << e.what() << std::endl;
		return 0;
	}
}
//end of helpers

void read(std::vector<int> &arr, int index){
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

void write(std::vector<int> &arr, int index){//idk why its called write, it writes to screen, should be called print...
	std::cout << get(arr, index) << std::endl;
}

void load(std::vector<int> &arr, int index, int &accumulator){
	accumulator = get(arr, index);
}

void store(std::vector<int> &arr, int index, const int accumulator){
	//for error checking here, i WAS thinking catch if accumulator is not a int but it will throw error on funciton call and never hit my try if its not an int 
	try{
		arr.at(index) = accumulator;
	}catch(std::out_of_range &e){//i just realized im not using the e, like e.what() to print the error message but my messages say what it wouldav, basically
		std::cout << "Memory has capacity 100 spots, so last addressable place is 99" << std::endl;
	}
}

void add(std::vector<int> &arr, int index, int &accumulator){//updates the accumulator by reference of course
	int word = get(arr, index);
	accumulator = accumulator + word;
}

void subtract(std::vector<int> &arr, int index, int &accumulator){
	accumulator = accumulator - get(arr, index);
}

void multiply(std::vector<int> &arr, int index, int &accumulator){
	accumulator = accumulator * get(arr, index);
}

void divide(std::vector<int> &arr, int index, int &accumulator){
	try{
		int word = get(arr, index);
		if (word == 0){
			throw std::logic_error("");
		}
		accumulator = accumulator / word;//if it is not an integer upon division, i think its truncated into one.
	}catch(std::logic_error &e){
		std::cout << "Cant divide by zero bro, maths gonna yell at you for that one and im inclined to agree" << std::endl;
	}
}

void branch(int index, int &pc){//on all branch guys, make sure pc is not updated, maybe just pc-- in each but thats unclear
	pc = index;
}



int main() {//print out all .txt files in directory, take input on which one and throw error if name is not an existing .txt file
	//select .txt BasicML program part
	std::cout << "Input the exact file name you want, if main.txt, type exactly that: " << std::endl;
	std::vector<std::string> files = get_all_txt();

	for (const auto& i : files){
		std::cout << i << std::endl;
	}

	std::string file_choice;
	std::cin >> file_choice;
	std::ifstream file(file_choice);

	std::vector<int> memory;/*initializes all 100 elements to zeros if vector(100)... gotta reserve space not vector(100)*/
	memory.reserve(100);

	int file_input;
	while (file >> file_input) { //could do a for loop then have it check if the statement was true per iter. but that seems more inefficient than this
		memory.push_back(file_input);//inserts values at i then increments after,
	}

	read(memory, 0);
	write(memory, 0);
	int accumulator = 31;
	load(memory, 0, accumulator);
	std::cout << accumulator << std::endl;
	store(memory, 0, accumulator);
	std::cout << memory.at(0) << std::endl;
	add(memory, 0, accumulator);
	std::cout << accumulator << std::endl;
	subtract(memory, 0, accumulator);
	std::cout << accumulator << std::endl;
	
	//print_vec(memory);

	int pc = 0;
	int instruction, opcode, operand;
	while (memory.size() > 0){ //while loop for executing all instructions, keep looping while array holds stuff

		instruction = memory.at(pc);

		opcode = memory.at(pc) / 100;
		operand = memory.at(pc) % 100; //ex 2006 % 100 == 6


		//last thing of course, remove instruction at index we want
		memory.erase(memory.begin() + 2);//element at index 2 is removed
	}
	
	return 0;
}
