#include <iostream>
#include <fstream>
#include <string>

using namespace std;


#pragma once

int ADD(int accum, string memory[100], string location);
int SUBTRACT(int accum, string memory[100], string location);
int DIVIDE(int accum, string memory[100], string location);
int MULTIPLY(int accum, string memory[100], string location);
void LOAD(string memory[100], int& address, int& accumulator);
void STORE(string memory[100], int& address, int& accumulator);
int BRANCH(int memory_address);
int BRANCHNEG(int accumulator,int old_address, int memory_address);
int BRANCHZERO(int accumulator, int old_address, int memory_address);
