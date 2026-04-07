#include "UVSim.h"
#include "WindowClass.h"



Window::Window() {
    Stopped = false;
    Running = false;
    readInput = "";
    waitingForRead = false;
    timer = 0.0f; //I got rid of static because it didn't like it
    openFile = false;
    done = false;
    showLines = true;
    numberOfLines = 100;
    consoleInput = "";
    isBackgroundGreen = true;

    //starts the memory with x0000
    for (size_t i = 0; i < 100; i++)
    {
        windowSim.memory[i] = "x0000";
    }
}


    void Window::incrementTime(float time) {
        //figure out what to do HERE
        //ImGuiIO& io = ImGui::GetIO(); (void)io;
        timer += time;
    }

    void Window::memory(int where, int value){
        windowSim.memory[where] = value;
    }

    bool Window::execute() {
        return windowSim.Execute();
    }

    bool Window::isRunning() {
        return Running && !Stopped && !waitingForRead;
    }

    bool Window::getRunning() {
        return Running;
    }

    void Window::setRunning(bool myBool) {
        Running = myBool;
    }

    bool Window::getStopped() {
        return Stopped;
    }

    void Window::setStopped(bool myBool) {
        Stopped = myBool;
    }

    float Window::getTimer() {
        return timer;
    }

    void Window::setTimer(float newTime) {
        timer = newTime;
    }
