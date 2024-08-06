#ifndef BULK_IOBSERVER_H
#define BULK_IOBSERVER_H

#include <vector>
#include <string>

using Data = std::vector<std::string>;

class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void update(const Data& data) = 0;
};


#endif //BULK_IOBSERVER_H
