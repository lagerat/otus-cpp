#include "FileWriter.h"
#include <chrono>

//-----------------------------------------------------------
FileWriter::FileWriter()
{
    auto start = std::chrono::system_clock::now();

    m_file =  std::ofstream("bulk" + std::to_string(start.time_since_epoch().count()) + ".txt");
}
//-----------------------------------------------------------
FileWriter::~FileWriter()
{
    m_file.close();
}
//-----------------------------------------------------------
void FileWriter::update(const Data &data)
{
    for (const auto& chunk : data)
    {
        m_file << ' ' << chunk;
    }
    m_file << std::endl;
}