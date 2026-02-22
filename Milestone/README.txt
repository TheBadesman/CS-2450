CS-2450, Milestone 2, Group 6
Group Members: Cameron Ottley, Jacen Taylor, James Pohl, Davin Lott
Overview:  UVSim is a simple virtual machine simulator made to help learn basic machine language and how a computer executes instructions. It runs programs written in BasicML, which is a small, assembly-style language. The simulator has a 100-word memory, an accumulator register, and executes instructions one at a time.

There are two main parts to this project. The first part is the simulator itself, which loads a BasicML program from a text file and runs it. The second part is a set of unit tests that make sure each instruction (like ADD, LOAD, BRANCH, etc.) works correctly.

To compile and run this project, you need a C++ compiler that supports C++17 or newer. On Windows, you can use Visual Studio’s cl compiler or MinGW with g++. On macOS, use clang++ from the Xcode Command Line Tools. On Linux, g++ works fine.

The important files are main.cpp, which contains the simulator logic, and Milestone2UnitTests.h / Milestone2UnitTests.cpp, which define the UVSim class and the unit tests. Both .cpp files should be in the same folder when compiling.

On macOS or Linux, you can compile the simulator with:

g++ -std=c++17 -o uvsim main.cpp Milestone2UnitTests.cpp

Or using clang:

clang++ -std=c++17 -o uvsim main.cpp Milestone2UnitTests.cpp

On Windows (Developer Command Prompt):

cl /EHsc main.cpp Milestone2UnitTests.cpp

To run the simulator, create a text file containing a BasicML program. Each line should be a signed four-digit number like +1007 or +4300. Run the program (./uvsim on macOS/Linux or main.exe on Windows), then enter the file name when prompted. The simulator prints the accumulator value as the program runs and stops when it reaches a HALT instruction.

BasicML vocabulary defined as follows:

I/O operation:
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

The last two digits of a BasicML instruction are the operand – the address of the memory location containing the word to which the operation applies.

The unit tests check that all BasicML operations work correctly, including arithmetic, branching, and error cases like division by zero. To run them, compile and run Milestone2UnitTests.cpp by itself. If everything works, the program will print messages saying the tests passed.

