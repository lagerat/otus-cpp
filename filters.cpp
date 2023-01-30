#include "filters.h"

void printIPs(const std::vector<std::vector<std::string>> &ip_pool) {
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
            if (ip_part != ip->cbegin()) {
                std::cout << ".";

            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}


std::vector<std::vector<std::string>> filter(const std::vector<std::vector<std::string>> &ip_pool,
                                             int firstBlock, int secondBlock) {
    std::vector<std::vector<std::string>> result;
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        auto elem = *ip;
        if (secondBlock == -1) {
            if (elem[0] != std::to_string(firstBlock)) {
                continue;
            }
        } else if (elem[0] != std::to_string(firstBlock) || elem[1] != std::to_string(secondBlock)) {
            continue;
        }
        result.push_back(*ip);
    }
    return result;
}

std::vector<std::vector<std::string>> filter_any(const std::vector<std::vector<std::string>> &ip_pool,
                                                 int block) {
    std::vector<std::vector<std::string>> result;
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        auto elem = *ip;
        auto number = std::to_string(block);
        if (elem[0] != number && elem[1] != number && elem[2] != number && elem[3] != number) {
            continue;
        }
        result.push_back(*ip);
    }
    return result;
}