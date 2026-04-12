CS-2450, Milestone 2, Group 6
Group Members: Cameron Ottley, Jacen Taylor, James Pohl, Davin Lott
Overview:  UVSim is a simple virtual machine simulator made to help learn basic machine language and how a computer executes instructions. It runs programs written in BasicML, which is a small, assembly-style language. The simulator has a 100-word memory, an accumulator register, and executes instructions one at a time, It now has a GUI with a few minor features appropriate to a gui

There are two main parts to this project. The first part is the simulator itself, which loads a BasicML program from a text file and runs it. The second part is the gui logic that takes the other components and adds visual elmenents to stuff

To compile and run this project, you need CMake and C++17 or newer. On Windows, you can use Visual Studio’s cl compiler or terminal, first build by entering Main projects current milestone directory, Milestone 3 here, then either enter or create directory build, ie mkdir or cd to it, then when inside that directory type: 'cmake .. -G "Ninja"' , run that line then type: 'cmake --build . ', the UVSim.exe should be created, to run simply type: './UVSim.exe' . On macOS, use clang++ from the Xcode Command Line Tools, then if not already, Install CMake and Ninja (Homebrew)
. Now you can do the exact same thing as on windows, mkdir build, cd build, cmake .. -G "Ninja", cmake --build . 
On Linux, Cmake will work fine, exact same workflow as windows. 

To run t.txt BasicML programs, follow instructions on Gui Console window, or from list ov availalbe .txt files printed, enter the .txt file you want, if in the program it asks for an input, type that into the newly craeted input section that pops up if that happens. to step through the program one word at a time, press step and that will bring you to the next word in memory. After inputing your text file, to simply run the whole thing, type Run, to stop midway for whatever reason, press stop, to be done with it, press halt, halt doesnt exit program as you might want to look at current stack.
if you got some message in the program output telling you what you did wrong but it didnt crash, you can press continue to start the simulator logic again and retry whatever minor thing you did that went wrong. 


