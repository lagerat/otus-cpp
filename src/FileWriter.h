#ifndef BULK_FILEWRITER_H
#define BULK_FILEWRITER_H

#include "IObserver.h"
#include "ThreadPool.h"

#include <fstream>
#include <queue>
#include <mutex>
#include <atomic>

class FileWriter : public IObserver
{
public:
    FileWriter();
    ~FileWriter() override;
    void update(const Data &data) override;
private:
    static void write(Data data, const std::string &fileName);
    static ThreadPool threadPool;
    static std::mutex mutex;
    std::string     m_fileName;
};

#endif //BULK_FILEWRITER_H
