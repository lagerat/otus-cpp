#include "FileScanner.h"

#include <boost/crc.hpp>
#include <utility>

FileScanner::FileScanner(std::vector<std::string> pathsToScan, std::vector<std::string> pathsNoScan,
                         std::vector<boost::regex> masks, size_t minimumSize)
                        : m_minimumSize(minimumSize), m_masks(std::move(masks)),
                          m_pathsToScan(std::move(pathsToScan)), m_pathsToExclude(std::move(pathsNoScan)) {}
//-----------------------------------------------------------
std::vector<std::string> FileScanner::Scan(bool isRecursive)
{
    for (const auto &pathToScan : m_pathsToScan)
    {
        if (!boost::filesystem::exists(pathToScan))
            continue;

        if (std::find(m_pathsToExclude.cbegin(), m_pathsToExclude.cend(), pathToScan)
                                                                        == m_pathsToExclude.cend())
            isRecursive ? ScanRecursive(pathToScan) : Scan(pathToScan);
    }

    return m_filesToScan;
}
//-----------------------------------------------------------
void FileScanner::Scan(const std::string &path)
{
    for (const auto &dir_entry : boost::filesystem::directory_iterator(path))
        if (dir_entry.status().type() == boost::filesystem::regular_file)
            AddFile(dir_entry);
}
//-----------------------------------------------------------
void FileScanner::ScanRecursive(const std::string &path)
{
    for (const auto &dir_entry : boost::filesystem::recursive_directory_iterator(path))
        if (dir_entry.status().type() == boost::filesystem::regular_file)
            AddFile(dir_entry);
}
//-----------------------------------------------------------
void FileScanner::AddFile(const boost::filesystem::directory_entry &dir)
{
    if (boost::filesystem::file_size(dir.path()) < m_minimumSize)
        return;

    auto fileName = dir.path().string();
    if (!CheckMasks(fileName))
        return;

    m_filesToScan.push_back(fileName);
}
//-----------------------------------------------------------
bool FileScanner::CheckMasks(const std::string &file) const
{
    if (m_masks.empty())
        return true;

    for (const auto &re : m_masks)
        if (boost::regex_match(file.c_str(), re))
            return true;

    return false;
}
//-----------------------------------------------------------