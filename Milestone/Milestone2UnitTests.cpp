#include <iostream>
#include <cassert>
#include "Milestone2UnitTests.h"

using namespace std;


void testAddition() {
	UVSim sim;

	//Test 1: adding two positive numbers
	sim.memory[0] = "5";
	int result = sim.ADD(2, "0");
	assert(result == 7);
	//Test 2: adding with two negative numbers
	sim.memory[1] = "-19";
	result = sim.ADD(-1, "1");
	assert(result == -20);
	cout << "ADDITION tests passed" << endl;
}

void testSubtract() {
	UVSim sim;

	//Test 1: subtracting two positive numbers
	sim.memory[0] = "11";
	int result = sim.SUBTRACT(29, "0");
	assert(result == 18);
	//Test 2: subtracting a negative number
	sim.memory[1] = "-8";
	result = sim.SUBTRACT(8, "1");
	assert(result == 16);
	cout << "SUBTRACT tests passed" << endl;
}

void testMultiply() {
	UVSim sim;

	//test multiplying two positive numbers
	sim.memory[0] = "5";
	int result = sim.MULTIPLY(5, "0");
	assert(result == 25);
	//test multiplying a positive and a negative number
	sim.memory[1] = "-4";
	result = sim.MULTIPLY(50, "1");
	assert(result == -200);
	cout << "MULTIPLY tests passed" << endl;
}

void testDIVIDE() {
	UVSim sim;

	//test regular division
	sim.memory[0] = "2";
	int result = sim.DIVIDE(8, "0");
	assert(result == 4);
	//test dividing by zero
	sim.memory[1] = "0";
	try {
		result = DIVIDE(15, "1");
		assert(false); //if it gets this far, then it failed
	}
	catch (...) {}
	cout << "DIVIDE tests passed" << endl;
}

void test_BRANCH() {
	UVSim sim;

    // Test 1: normal branch
    int result = sim.BRANCH(10);
    assert(result == 10);
    // Test 2: branch to zero
    result = sim.BRANCH(0);
    assert(result == 0);
    std::cout << "BRANCH tests passed\n";
}

void test_BRANCHNEG() {
	UVSim sim;

    // Test 1: accumulator is negative → branch
    int result = sim.BRANCHNEG(-5, 4, 20);
    assert(result == 20);
    // Test 2: accumulator is NOT negative → do not branch
    result = sim.BRANCHNEG(10, 4, 20);
    assert(result == 4);
    std::cout << "BRANCHNEG tests passed\n";
}

void test_BRANCHZERO() {
	UVSim sim;

    // Test 1: accumulator is zero → branch
    int result = sim.BRANCHZERO(0, 7, 30);
    assert(result == 30);
    // Test 2: accumulator is NOT zero → do not branch
    result = sim.BRANCHZERO(3, 7, 30);
    assert(result == 7);
    std::cout << "BRANCHZERO tests passed\n";
}

void test_LOAD() {
	UVSim sim;

    // Test 1: accumulator loads correct value from memory
    sim.memory[0] = "+2010";
    sim.memory[10] = "+0042";
    sim.address = 0;
    sim.LOAD(sim.address, sim.accumulator);
    assert(sim.accumulator == 42);
    // Test 2: accumulator changes from previous value
    sim.memory[10] = "-0015";
    sim.LOAD(sim.address, sim.accumulator);
    assert(sim.accumulator == -15);
    cout << "LOAD tests passed\n";
}

void test_STORE() {
	UVSim sim;

    // Test 1: store positive accumulator value into memory
    sim.accumulator = 25;
    sim.address = 0;
    // instruction: STORE into memory location 20
    sim.memory[0] = "+2120";
    sim.STORE(sim.address, sim.accumulator);
    assert(sim.memory[20] == "+0025");
    // Test 2: store negative accumulator value into memory
    sim.accumulator = -9;
    sim.STORE(sim.address, sim.accumulator);
    assert(sim.memory[20] == "-0009");
    cout << "STORE tests passed\n";
}

void test_WRITE() {
	UVSim sim;

	//Test1: write a positive value
	sim.memory[5] = "+0042";
	cout << "Expected output: The word stored in 5 is +0042" << endl;
	sim.WRITE(5);
	//Test 2: write a negative value
	sim.memory[12] = "-0019";
	cout << "Expected output: The word stored in 12 is -0019" << endl;
	sim.WRITE(12);
	cout << "WRITE tests passed\n";
}


int main() {
	testAddition();
	testSubtract();
	testDIVIDE();
	testMultiply();
	test_BRANCH();
	test_BRANCHNEG();
	test_BRANCHZERO();
	test_LOAD();
	test_STORE();
	test_WRITE();
	
	return 0;
}