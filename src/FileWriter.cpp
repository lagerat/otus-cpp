#include "FileWriter.h"
#include <chrono>
#include <thread>


ThreadPool FileWriter::threadPool(2);
std::mutex FileWriter::mutex;
//-----------------------------------------------------------
FileWriter::FileWriter()
{
    auto start = std::chrono::system_clock::now();
    m_fileName = "bulk" + std::to_string(start.time_since_epoch().count()) + ".txt";
}
//-----------------------------------------------------------
FileWriter::~FileWriter()
{
    threadPool.wait_all();
}
//-----------------------------------------------------------
void FileWriter::write(Data data, const std::string &fileName)
{
    std::lock_guard<std::mutex> guard(mutex);

    std::ofstream file(fileName, std::ofstream::out | std::ofstream::app);

    for(auto& command : data)
    {
        file << command << " ";
    }

    file << std::endl;
}
//-----------------------------------------------------------
void FileWriter::update(const Data &data)
{
    if (data.empty())
        return;

    auto taskId = threadPool.add_task(write, data, std::cref(m_fileName));
    threadPool.wait(taskId);
}
//-----------------------------------------------------------