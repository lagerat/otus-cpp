#include "FilesHashCheck.h"
#include "hash/crc16.h"
#include "hash/crc32.h"

#include <algorithm>
#include <fstream>

FilesHashCheck::FilesHashCheck(std::vector<std::string> filesToScan, size_t blockSize, HashType type)
{
    m_filesToScan = std::move(filesToScan);
    m_blockSize = blockSize;
    m_type = type;
}
//-----------------------------------------------------------
std::map<std::string, std::vector<std::string>> FilesHashCheck::Run()
{
    FindDuplicate();
    return m_duplicates;
}
//-----------------------------------------------------------
void FilesHashCheck::FindDuplicate()
{
    if (m_filesToScan.size() <= 1)
        return;

    auto mainFile = m_filesToScan.back();
    m_filesToScan.pop_back();

    for (const auto &file : m_filesToScan)
        if (IsSameFiles(mainFile, file))
        {
            m_duplicates[mainFile].push_back(file);
            m_filesToScan.erase(std::remove(m_filesToScan.begin(), m_filesToScan.end(), file), m_filesToScan.end());
        }

    FindDuplicate();
}
//-----------------------------------------------------------
bool FilesHashCheck::IsSameFiles(const std::string &firstFileName, const std::string &secondFileName)
{
    if (firstFileName.empty() || secondFileName.empty())
        return false;

    std::ifstream firstFileStream(firstFileName, std::ios::in);
    std::ifstream secondFileStream(secondFileName, std::ios::in);

    if (!firstFileStream.is_open() || !secondFileStream.is_open())
        return false;

    bool equal = false;
    for (size_t pos = 0; (firstFileStream.seekg(pos) && secondFileStream.seekg(pos)); pos += m_blockSize)
    {
        std::string l_block(m_blockSize, '\0');
        std::string r_block(m_blockSize, '\0');

        firstFileStream.read(&l_block[0], m_blockSize);
        secondFileStream.read(&r_block[0], m_blockSize);

        equal = IsSameBlocks(l_block, r_block);
        if (!equal)
            return false;
    }

    return equal;
}
//-----------------------------------------------------------
bool FilesHashCheck::IsSameBlocks(const std::string &lhs, const std::string &rhs) const
{
    return Hash(lhs) == Hash(rhs);
}
//-----------------------------------------------------------
size_t FilesHashCheck::Hash(const std::string &str) const
{
    return (m_type == HashType::CRC16) ? Crc16::run(str) : Crc32::run(str);
}
//-----------------------------------------------------------