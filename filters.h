#ifndef HELLOWORLD_CLI_FILTERS_H
#define HELLOWORLD_CLI_FILTERS_H

#include <iostream>
#include <string>
#include <vector>

void printIPs(const std::vector<std::vector<std::string>> &);

std::vector<std::vector<std::string>> filter(const std::vector<std::vector<std::string>> &ip_pool,
                                             int firstBlock, int secondBlock = -1);

std::vector<std::vector<std::string>> filter_any(const std::vector<std::vector<std::string>> &ip_pool, int block);

#endif //HELLOWORLD_CLI_FILTERS_H
