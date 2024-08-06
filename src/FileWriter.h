#ifndef BULK_FILEWRITER_H
#define BULK_FILEWRITER_H
#include "IObserver.h"
#include <fstream>

class FileWriter : public IObserver
{
public:
    FileWriter();
    ~FileWriter();
    void update(const Data &data) override;

private:
    std::ofstream m_file;
};

#endif //BULK_FILEWRITER_H
