#ifndef FILESDUPLICATE_DUPLICATESFINDER_H
#define FILESDUPLICATE_DUPLICATESFINDER_H

#include "FileScanner.h"
#include "FilesHashCheck.h"

#include <boost/program_options.hpp>
#include <utility>
#include <iostream>

namespace po = boost::program_options;

class DuplicatesFinder{
public:
    explicit DuplicatesFinder(const po::variables_map& varMap);
    void Run();
private:
    bool m_isRecursive = false;
    size_t m_minimumSize = 1;
    size_t m_blockSize = 5;
    HashType m_type = HashType::CRC32;
    std::vector<boost::regex> m_masks;
    std::vector<std::string> m_dirToScan;
    std::vector<std::string> m_dirNoScan;
};

#endif //FILESDUPLICATE_DUPLICATESFINDER_H
