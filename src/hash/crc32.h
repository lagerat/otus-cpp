#ifndef FILESDUPLICATE_CRC32_H
#define FILESDUPLICATE_CRC32_H

#include <cstddef>
#include <boost/crc.hpp>

struct Crc32
{
    static std::size_t run(const std::string& toHash)
    {
        boost::crc_32_type result;
        result.process_bytes(toHash.data(), toHash.size());
        return result.checksum();
    }
};

#endif //FILESDUPLICATE_CRC32_H
