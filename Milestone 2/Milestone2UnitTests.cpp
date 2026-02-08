#include <iostream>
#include <cassert>
#include "Milestone2UnitTests.h"

using namespace std;


void testAddition() {
	//test adding two positive numbers
	bool passed = true;
	string testList[100]{};
	testList[0] = "5";
	int result = ADD(2, testList, "0");
	if (result != 7) {
		cout << "Test failed. 5 + 2 != " << result << endl;
		passed = false;
	}
	//test adding with two negative numbers
	testList[1] = "-19";
	result = ADD(-1, testList, "1");
	if (result != -20) {
		cout << "Test failed. -19 + -1 != " << result << endl;
		passed = false;
	}
	if (passed) {
		cout << "All addition tests passed" << endl;
	}

}

void testSubtract() {
	//test subtracting two positive numbers
	bool passed = true;
	string testList[100]{};
	testList[0] = "11";
	int result = SUBTRACT(29, testList, "0");
	if (result != 18) {
		cout << "Test failed. 29 - 11 != " << result << endl;
		passed = false;
	}
	//test subtracting a negative number
	testList[1] = "-8";
	result = SUBTRACT(8, testList, "1");
	if (result != 16) {
		cout << "Test failed. 8 - (-8) != " << result << endl;
		passed = false;
	}
	if (passed) {
		cout << "All subtraction tests passed" << endl;
	}
}

void testMultiply() {
	//test multiplying two positive numbers
	bool passed = true;
	string testList[100]{};
	testList[0] = "5";
	int result = MULTIPLY(5, testList, "0");
	if (result != 25) {
		cout << "Test failed. 5 * 5 != " << result << endl;
		passed = false;
	}
	//test multiplying a positive and a negative number
	testList[1] = "-4";
	result = MULTIPLY(50, testList, "1");
	if (result != -200) {
		cout << "Test failed. -4 * 50 != " << result << endl;
		passed = false;
	}
	if (passed) {
		cout << "All multiplication tests passed" << endl;
	}
}

void testDIVIDE() {
	//test regular division
	bool passed = true;
	string testList[100]{};
	testList[0] = "2";
	int result = DIVIDE(8, testList, "0");
	if (result != 4) {
		cout << "Test failed. 8 / 2 != " << result << endl;
		passed = false;
	}
	//test dividing by zero
	testList[1] = "0";
	try {
		result = DIVIDE(15, testList, "1");
		passed = false; // if something isn't thrown, then something went wrong
	}
	catch (...) {}
	if (passed) {
		cout << "All division tests passed" << endl;
	}

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

	return 0;
}