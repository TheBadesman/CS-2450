#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
	ifstream file("Test1.txt");

	int memory[100];
	int input_val;
	int i = 0; 
	while (file >> input_val) { //could do a for loop then have it check if the statement was true per iter. but that seems more inefficient than this
		memory[i++] = input_val;//inserts values at i then increments after,
		cout << memory[--i] << endl;
	}

	
	return 0;
}
