CS-2450, Milestone 2, Group 6
Group Members: Cameron Ottley, Jacen Taylor, James Pohl, Davin Lott
Overview: This program will simulate excecuting programs written in BasicML, and can load a BasicML program in using a text file
After this, it will excecute each instruction from top to bottom

System Requirements: Windows, using a complier that runs C++17 or newer

How To Compile:
Using the Command Line: cl main.cpp

How to Run:
//Ensure that a text file containing signed 4 digit numbers i.e. +2007, +1108, +4300
Run the program: main.exe
When the program requests it, enter the name of the text file

I/O Operations:
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
