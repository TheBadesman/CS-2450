#include <iostream>
#include <cassert>
#include "Milestone2UnitTests.h"

using namespace std;


void testAddition() {
	//Test 1: adding two positive numbers
	string testList[100]{};
	testList[0] = "5";
	int result = ADD(2, testList, "0");
	assert(result == 7);
	//Test 2: adding with two negative numbers
	testList[1] = "-19";
	result = ADD(-1, testList, "1");
	assert(result == -20);
	cout << "ADDITION tests passed" << endl;


}

void testSubtract() {
	//Test 1: subtracting two positive numbers
	string testList[100]{};
	testList[0] = "11";
	int result = SUBTRACT(29, testList, "0");
	assert(result == 18);
	//Test 2: subtracting a negative number
	testList[1] = "-8";
	result = SUBTRACT(8, testList, "1");
	assert(result == 16);
	cout << "SUBTRACT tests passed" << endl;
}

void testMultiply() {
	//test multiplying two positive numbers
	bool passed = true;
	string testList[100]{};
	testList[0] = "5";
	int result = MULTIPLY(5, testList, "0");
	assert(result == 25);
	//test multiplying a positive and a negative number
	testList[1] = "-4";
	result = MULTIPLY(50, testList, "1");
	assert(result == -200);
	cout << "MULTIPLY tests passed" << endl;
}

void testDIVIDE() {
	//test regular division
	string testList[100]{};
	testList[0] = "2";
	int result = DIVIDE(8, testList, "0");
	assert(result == 4);
	//test dividing by zero
	testList[1] = "0";
	try {
		result = DIVIDE(15, testList, "1");
	}
	catch (...) {}
	cout << "DIVIDE tests passed" << endl;

}

void test_BRANCH() {
    // Test 1: normal branch
    int result = BRANCH(10);
    assert(result == 9);

    // Test 2: branch to zero
    result = BRANCH(0);
    assert(result == -1);

    std::cout << "BRANCH tests passed\n";
}

void test_BRANCHNEG() {
    // Test 1: accumulator is negative → branch
    int result = BRANCHNEG(-5, 4, 20);
    assert(result == 19);

    // Test 2: accumulator is NOT negative → do not branch
    result = BRANCHNEG(10, 4, 20);
    assert(result == 4);

    std::cout << "BRANCHNEG tests passed\n";
}

void test_BRANCHZERO() {
    // Test 1: accumulator is zero → branch
    int result = BRANCHZERO(0, 7, 30);
    assert(result == 29);

    // Test 2: accumulator is NOT zero → do not branch
    result = BRANCHZERO(3, 7, 30);
    assert(result == 7);

    std::cout << "BRANCHZERO tests passed\n";
}

void test_LOAD() {
    // Test 1: accumulator loads correct value from memory
    string memory[100]{};
    int accumulator = 0;
    int address = 0;

    memory[0] = "+2010";
    memory[10] = "+0042";

    LOAD(memory, address, accumulator);
    assert(accumulator == 42);

    // Test 2: accumulator changes from previous value
    memory[10] = "-0015";
    LOAD(memory, address, accumulator);
    assert(accumulator == -15);

    cout << "LOAD tests passed\n";
}

void test_STORE() {
    // Test 1: store positive accumulator value into memory
    string memory[100]{};
    int accumulator = 25;
    int address = 0;

    // instruction: STORE into memory location 20
    memory[0] = "+2120";

    STORE(memory, address, accumulator);
    assert(memory[20] == "+0025");

    // Test 2: store negative accumulator value into memory
    accumulator = -9;
    STORE(memory, address, accumulator);
    assert(memory[20] == "-0009");

    cout << "STORE tests passed\n";
}

void test_WRITE() {
	//Test1: write a positive value
	string memory[100]{};
	memory[5] = "0042";

	cout << "Expected output: The word stored in 5 is +0042" <<endl;
	WRITE(memory, 5);

	//Test 2: write a negative value
	memory[12] = "-0019";

	cout << "Expected output: The word stored in 12 is -0019" <<endl;
	WRITE(memory, 12);

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
