#include "FileWriter.h"
#include <chrono>
#include <thread>

std::atomic<bool> FileWriter::isDone = false;
std::atomic<int> FileWriter::threadCount = 0;
//-----------------------------------------------------------
FileWriter::FileWriter()
{
    auto start = std::chrono::system_clock::now();
    m_fileName = "bulk" + std::to_string(start.time_since_epoch().count()) + ".txt";
    m_file = std::ofstream(m_fileName);
}
//-----------------------------------------------------------
FileWriter::~FileWriter()
{
    m_file.close();
}

void FileWriter::write_block(const std::string &command, const std::string &fileName)
{
    std::ofstream file(fileName, std::ofstream::out | std::ofstream::app);

    if(command.empty())
        return;

    file << command << " ";
}

void FileWriter::write(CommandQueue& queue, const std::string &fileName)
{
    threadCount++;

    while (!queue.isEmpty())
    {
        auto block = queue.popCommand();
        write_block(block, fileName);
    }

    threadCount--;
    if(threadCount == 0)
        FinishUpdate(fileName);
}
//-----------------------------------------------------------
void FileWriter::update(const Data &data)
{
    isDone = false;
    threadCount = 0;

    if (data.empty())
        return;

    CommandQueue queue(data);

    std::thread file_1(write, std::ref(queue), m_fileName);
    std::thread file_2(write, std::ref(queue), m_fileName);

    file_1.join();
    file_2.join();
}
void FileWriter::FinishUpdate( const std::string &fileName)
{
    std::ofstream file(fileName, std::ofstream::out | std::ofstream::app);
    file << std::endl;
}

//-----------------------------------------------------------
CommandQueue::CommandQueue(const Data &data)
{
    for (const auto& chunk : data   )
        m_queue.push(chunk);
}

std::string CommandQueue::popCommand()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    if(m_queue.empty())
        return "";

    auto result = m_queue.front();
    m_queue.pop();

    return result;
}

bool CommandQueue::isEmpty()
{
    return m_queue.empty();
}