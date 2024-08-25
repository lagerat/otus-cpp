#ifndef BULK_LOGWRITER_H
#define BULK_LOGWRITER_H
#include "IObserver.h"
#include <thread>

class LogWriter : public IObserver
{
public:
    void update(const Data &data) override;
private:
    static void write(Data data);
};

#endif //BULK_LOGWRITER_H
