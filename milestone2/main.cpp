#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

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
		std::exit(1);
		return 0;
	}
}
//end of helpers

void read(std::vector<int> &arr, int index){
	try{
		std::string input;
		std::cout << "Input the sign + or - then the four digit word you want, if data insert opcode 00 then the number you wish thats two digits so if i wanted 69, +0069, if negative 69, -0069: " << std::endl << std::flush;
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

void load(std::vector<int> &arr, int index, int &accumulator){
	accumulator = get(arr, index);
}

void store(std::vector<int> &arr, int index, const int accumulator){
	//for error checking here, i WAS thinking catch if accumulator is not a int but it will throw error on funciton call and never hit my try if its not an int 
	try{
		arr.at(index) = accumulator;
	}catch(std::out_of_range &e){//i just realized im not using the e, like e.what() to print the error message but my messages say what it wouldav, basically
		std::cout << "Memory has capacity 100 spots, so last addressable place is 99" << std::endl;
		std::exit(1);
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
		std::exit(1);
	}
}

void branch(int index, int &pc){//on all branch guys, make sure pc is not updated, maybe just pc-- in each but thats unclear
	pc = index;
}

void branchNeg(int index, int &pc, int &accumulator){
	if (accumulator < 0){
        	pc = index;
	}else{
		pc++;//as if it doesnt branch, pc needs to be incremented and it aint happenin in the switch of course.
	}
}

void branchZero(int index, int &pc, int &accumulator){//on all branch guys, make sure pc is not updated, maybe just pc-- in each but thats unclear
	if (accumulator == 0){
        	pc = index;
	}else{
		pc++;
	}
}

void halt(int pc){
	std::cout << "opcode 43 read, Program Halt at PC: " << pc << " ,Goodbye." << std::endl;
	std::exit(0);
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

	std::vector<int> memory(100, 0);

	std::string file_input;
	int int_file;
	char sign[2] = {'-', '+'};
	int load_index = 0;
	if (!file.is_open()){
		std::cout << "File aint found dog, ig we fuck off then" << std::endl;
		return -1;
	}
	while (file >> file_input) { //could do a for loop then have it check if the statement was true per iter. but that seems more inefficient than this
		try{
			if (file_input.length() != 5){//length can only be 5 characters long
				throw std::out_of_range("");
			}else if (file_input[0] != sign[0] && file_input[0] != sign[1]){
				throw std::invalid_argument("Instruction read does not hold a sign, it needs to be a signed number dog");
			}for (size_t i = 1; i < file_input.length(); i++){
				if (std::isdigit(file_input[i]) == false){
					throw std::invalid_argument("Instruction read is not a number");
				}
			}
			int_file = std::stoi(file_input);
			memory[load_index++] = int_file;
		}catch(const std::invalid_argument& e){
			std::cout << e.what() << std::endl;
			std::exit(1);
		}catch(const std::out_of_range& e){
			std::cout << "File contains instruction not length five(5 for potential sign ie -0099), bad instruction: " << file_input << std::endl;
			std::exit(1);
		}
		catch(...){
			std::cout << "Unknown issue :(" << std::endl;
			std::exit(1);
		}
	}
	for (size_t i = load_index; i < 100; i++){//fill rest of memory with halt instruction so if it ever jumps to a weird place it shouldnt be, halt
		memory.at(i) = 4300;
	}

	int pc = 0;
	int accumulator = 0;
	int instruction, opcode, operand;
	bool executing = true;
	while (executing){ //while loop for executing all instructions, keep looping while array holds stuff
		if (pc < 0 || pc >= 100) {
			std::cout << "PC out of bounds: " << pc << std::endl;
			exit(1);
		}

		instruction = get(memory, pc);
		instruction = std::abs(instruction);

		opcode = instruction / 100;
		operand = instruction % 100; //ex 2006 % 100 == 6
		
		switch (opcode) {
			case 10:
				read(memory, operand); 
				break;
			case 11: 
				write(memory, operand); 
				break;
			case 20:
				load(memory, operand, accumulator); 
				break;
			case 21: 
				store(memory, operand, accumulator); 
				break;
			case 30: 
				add(memory, operand, accumulator);
				break;
			case 31: 
				subtract(memory, operand, accumulator);
				break;
			case 32: 
				divide(memory, operand, accumulator);
				break;
			case 33: 
				multiply(memory, operand, accumulator);
				break;
			case 40: 
				branch(operand, pc); 
				continue;//jumps to next iteration of loop after branch command happens.
			case 41: 
				branchNeg(operand, pc, accumulator);
				continue;
			case 42: 
				branchZero(operand, pc, accumulator);
				continue;
			case 43: 
				halt(pc);
				executing = false;//just in case something weird happens on the exit in halt, break the while here
				break;

			default:
				std::cout << "Invalid opcode: " << opcode << ". PC location: " << pc << std::endl;
				std::exit(1);
		}
		pc++;	
	}
	
	return 0;
}
