#include "LogWriter.h"
#include <iostream>

void LogWriter::update(const Data &data)
{
    std::cout << "bulk:";
    for (const auto& chunk : data)
    {
        std::cout << ' ' << chunk;
    }
    std::cout << std::endl;
}