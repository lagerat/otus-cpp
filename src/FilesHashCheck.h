#ifndef FILESDUPLICATE_FILESHASHCHECK_H
#define FILESDUPLICATE_FILESHASHCHECK_H

#include <vector>
#include <string>
#include <map>

enum class HashType {
    CRC16,
    CRC32
};

class FilesHashCheck {
public:
    FilesHashCheck(std::vector<std::string> filesToScan, size_t blockSize, HashType type);
    std::map<std::string, std::vector<std::string>> Run();
private:

    void FindDuplicate();
    bool IsSameFiles(const std::string &firstFileName, const std::string &secondFileName);
    bool IsSameBlocks(const std::string &lhs, const std::string &rhs) const;

    size_t Hash(const std::string &str) const;

    std::vector<std::string> m_filesToScan;
    std::map<std::string, std::vector<std::string>> m_duplicates;
    size_t m_blockSize = 5;
    HashType m_type = HashType::CRC32;
};

#endif //FILESDUPLICATE_FILESHASHCHECK_H
