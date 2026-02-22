#pragma once
#include <vector>
#include <string>

class Console
{
private:
    std::vector<std::string> logs;

public:
    void addLog(const std::string& message);
    void clear();
    const std::vector<std::string>& getLogs() const;
};
