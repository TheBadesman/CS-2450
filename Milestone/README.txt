CS-2450, Milestone 2, Group 6
Group Members: Cameron Ottley, Jacen Taylor, James Pohl, Davin Lott
Overview: This program will simulate excecuting programs written in BasicML, and can load a BasicML program in using a text file
After this, it will excecute each instruction from top to bottom

System Requirements: Windows, using a complier that runs C++17 or newer OR on Mac shit

How To Compile for Windows, CL is a default compiler and assembler(create the object files then links them to a main.exe all in one step) tha comes with - Visual Studio
- Visual Studio Build Tools
- or the Developer Command Prompt, I dont think there are any default c++ compilers for windows

Command Line on windows: cl main.cpp


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


Control operation:
BRANCH = 40 Branch to a specific location in memory
BRANCHNEG = 41 Branch to a specific location in memory if the accumulator is negative.
BRANCHZERO = 42 Branch to a specific location in memory if the accumulator is zero.
HALT = 43 Pause the program
