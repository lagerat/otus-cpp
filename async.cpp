#include "async.h"

#include "src/Bulk.h"
#include "src/LogWriter.h"
#include "src/FileWriter.h"

#include <boost/algorithm/string.hpp>

namespace async {
//-----------------------------------------------------------
handle_t connect(size_t bulk)
{
    auto pBulk = new Bulk{bulk};

    pBulk->subscribe(std::make_unique<LogWriter>());
    pBulk->subscribe(std::make_unique<FileWriter>());

    return pBulk;
}
//-----------------------------------------------------------
void receive(handle_t handle, const char *data, size_t size)
{
    std::vector<std::string> parts;
    boost::algorithm::split(parts, data, boost::algorithm::is_any_of("\n"),
                            boost::token_compress_on);
    parts.erase(std::remove(parts.begin(), parts.end(), ""), parts.end());

    if (auto pBulk = static_cast<Bulk*>(handle)) {
        pBulk->setSize(size == 0 ? std::nullopt : std::optional<size_t>{size});

        for (const auto &part : parts)
            pBulk->applyCommand(part);
    }
}
//-----------------------------------------------------------
void disconnect(handle_t handle)
{
    delete static_cast<Bulk*>(handle);
}
}