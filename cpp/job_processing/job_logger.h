#pragma once

#include <fstream>
#include <string>

class JobLogger
{
public:
    explicit JobLogger(const std::string &filename);
    void log(const std::string &message);

private:
    std::ofstream file;
};