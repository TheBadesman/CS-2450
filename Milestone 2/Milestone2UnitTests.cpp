#include <iostream>
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


int main() {
	testAddition();
	testSubtract();
	testDIVIDE();
	testMultiply();
	string testList[100]{};
	testList[0] = "0";
	int result = DIVIDE(8, testList, "0");

	return 0;
}