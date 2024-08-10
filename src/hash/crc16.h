#ifndef FILESDUPLICATE_CRC16_H
#define FILESDUPLICATE_CRC16_H

#include <cstddef>
#include <boost/crc.hpp>

struct Crc16
{
    static std::size_t run(const std::string& toHash)
    {
        boost::crc_16_type result;
        result.process_bytes(toHash.data(), toHash.size());
        return result.checksum();
    }
};

#endif //FILESDUPLICATE_CRC16_H
