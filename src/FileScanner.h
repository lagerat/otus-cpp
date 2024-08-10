#ifndef FILESDUPLICATE_FILESCANNER_H
#define FILESDUPLICATE_FILESCANNER_H

#pragma once

#include <boost/container/map.hpp>
#include <boost/container/vector.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/regex.hpp>

class FileScanner {
    size_t m_minimumSize = 1;
    std::vector<boost::regex> m_masks;
    std::vector<std::string> m_pathsToScan;
    std::vector<std::string> m_pathsToExclude;
    std::vector<std::string> m_filesToScan;

public:
    FileScanner(std::vector<std::string> pathsToScan, std::vector<std::string> pathsNoScan,
                std::vector<boost::regex> masks, size_t minimumSize = 1);

    std::vector<std::string> Scan(bool isRecursive = false);

private:
    void Scan(const std::string &path);
    void ScanRecursive(const std::string &path);
    void AddFile(const boost::filesystem::directory_entry &dir);
    bool CheckMasks(const std::string &file) const;
};

#endif //FILESDUPLICATE_FILESCANNER_H
