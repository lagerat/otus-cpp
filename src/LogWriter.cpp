#include "LogWriter.h"
#include <iostream>

void LogWriter::update(const Data &data)
{
    std::thread log1(write, data);

    log1.join();
}
//-----------------------------------------------------------
void LogWriter::write(Data data)
{
    std::cout << "bulk:";
    for (const auto& chunk : data)
    {
        std::cout << ' ' << chunk;
    }
    std::cout << std::endl;
}