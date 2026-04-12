#include "UVSim.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#pragma once

void READ(int memory_address);
void WRITE(int memory_address);
int ADD(int accum, string location);
int SUBTRACT(int accum, string location);
int DIVIDE(int accum, string location);
int MULTIPLY(int accum, string location);
void LOAD(int& address, int& accumulator);
void STORE(int& address, int& accumulator);
int BRANCH(int memory_address);
int BRANCHNEG(int accumulator,int old_address, int memory_address);
int BRANCHZERO(int accumulator, int old_address, int memory_address);
