#ifndef BULK_FILEWRITER_H
#define BULK_FILEWRITER_H

#include "IObserver.h"
#include <fstream>
#include <queue>
#include <mutex>
#include <atomic>

class CommandQueue
{
public:
    CommandQueue(const Data &data);
    std::string popCommand();
    bool isEmpty();
private:
    std::queue<std::string> m_queue;
    std::mutex m_mutex;
};

class FileWriter : public IObserver
{
public:
    FileWriter();
    ~FileWriter() override;
    void update(const Data &data) override;
private:

    static void write(CommandQueue& queue, const std::string &fileName);
    static void write_block(const std::string& command, const std::string &fileName);
    static void FinishUpdate( const std::string &fileName);

    std::string     m_fileName;
    std::ofstream   m_file;

    static std::atomic<bool>    isDone;
    static std::atomic<int>     threadCount;
};

#endif //BULK_FILEWRITER_H
