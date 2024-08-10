#include "DuplicatesFinder.h"
#include "FilesHashCheck.h"

namespace
{
    const char* BlockSize =     "block";
    const char* Algorithm =     "hash";
    const char* MinSize =       "minSize";
    const char* DirToScan =     "dirToScan";
    const char* DirToExclude =  "dirToExclude";
    const char* Masks =         "Masks";
    const char* Crc16 =         "crc16";
    const char* Crc32 =         "crc32";
}
//-----------------------------------------------------------
DuplicatesFinder::DuplicatesFinder(const po::variables_map& varMap)
{
    m_blockSize = varMap[BlockSize].as<std::size_t>();
    if (m_blockSize == 0)
    {
        std::cerr << "Blocks size must be at least 1\n";
        exit(1);
    }
    m_minimumSize = varMap[MinSize].as<std::size_t>();
    m_dirToScan = varMap[DirToScan].as<std::vector<std::string>>();
    m_dirNoScan = (varMap.count(DirToExclude) == 0) ? std::vector<std::string>()
                                                    : varMap[DirToExclude].as<std::vector<std::string>>();

    auto mask_strings = (varMap.count(Masks) == 0) ? std::vector<std::string>()
                                                   : varMap[Masks].as<std::vector<std::string>>();

    for (const auto& mask_string : mask_strings)
        m_masks.emplace_back(mask_string, boost::regex_constants::ECMAScript);

    auto hash = varMap[Algorithm].as<std::string>();
    if (hash == Crc16)
        m_type = HashType::CRC16;
    else if (hash == Crc32)
        m_type = HashType::CRC32;
    else
        throw std::invalid_argument(std::string("Incorrect hash algorithm ")
                                        + hash + ". Use --help options for more details");
}
//-----------------------------------------------------------
void DuplicatesFinder::Run()
{
    FileScanner scanner(m_dirToScan, m_dirNoScan, m_masks, m_minimumSize);
    FilesHashCheck hashChecker(scanner.Scan(m_isRecursive), m_blockSize, m_type);
    auto duplicate = hashChecker.Run();

    for (const auto &group : duplicate)
    {
        std::cout << group.first << "  ";

        for (const auto &name : group.second)
            std::cout << name << "  ";

        std::cout << std::endl;
    }
}
//-----------------------------------------------------------