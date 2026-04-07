#ifndef WINDOW_H
#define WINDOW_H

class Window {
    bool Stopped;
    bool Running;
    std::string readInput;
    bool waitingForRead;
    float timer;
    bool openFile;
    bool done;
    bool showLines;
    int numberOfLines;
    std::string consoleInput;
    bool isBackgroundGreen;

public:
    UVSim windowSim;
    Window();

    void incrementTime(float time);

    void memory(int where, int value);

    bool execute();
    bool isRunning();
    bool getRunning();
    void setRunning(bool myBool);
    bool getStopped();
    void setStopped(bool myBool);
    float getTimer();
    void setTimer(float newTime);
};

#endif