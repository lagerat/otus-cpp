#ifndef HELLOWORLD_CLI_FILTERS_H
#define HELLOWORLD_CLI_FILTERS_H

#include <iostream>
#include <string>
#include <vector>
#include <array>

void printIPs(std::vector<std::array<uint8_t, 4>> &ip_pool);

void filter(const std::vector<std::array<uint8_t, 4>> &ip_pool,
                                             int firstBlock, int secondBlock = -1);

void filter_any(const std::vector<std::array<uint8_t, 4>> &ip_pool, int block);

#endif //HELLOWORLD_CLI_FILTERS_H
