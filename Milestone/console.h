#pragma once
#include <string>
#include <vector>

class Console
{
public:
    std::vector<std::string> log;
    std::string inputBuffer;

    void addLog(const std::string& text);
};
