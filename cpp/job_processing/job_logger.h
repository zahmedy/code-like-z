#pragma once

#include <fstream>
#include <string>

class JobLogger
{
public:
    explicit JobLogger(const std::string &filename);
    ~JobLogger();

private:
    std::ofstream file;
};