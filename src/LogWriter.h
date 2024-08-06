#ifndef BULK_LOGWRITER_H
#define BULK_LOGWRITER_H
#include "IObserver.h"

class LogWriter : public IObserver
{
public:
    void update(const Data &data) override;
};

#endif //BULK_LOGWRITER_H
