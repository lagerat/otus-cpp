#include "filters.h"

void printIPs(std::vector<std::array<uint8_t, 4>> &ip_pool) {
    for (auto ip : ip_pool) {
        for (size_t i = 0; i < ip.size(); i++) {
            std::cout << static_cast<int>(ip[i]);
            if(i != 3){
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}


void filter(const std::vector<std::array<uint8_t, 4>> &ip_pool, int firstBlock, int secondBlock) {
    for (auto &ip : ip_pool) {
        auto elem = ip;
        if (secondBlock == -1) {
            if (elem[0] != firstBlock) {
                continue;
            }
        } else if (elem[0] != firstBlock || elem[1] != secondBlock) {
            continue;
        }
        std::cout << (int)ip[0] << '.' << (int)ip[1] << '.' << (int)ip[2] << '.' << (int)ip[3] << "\n";
    }
}

void filter_any(const std::vector<std::array<uint8_t, 4>> &ip_pool,
                                                 int block) {
    std::vector<std::vector<std::string>> result;
    for (auto &ip : ip_pool) {
        auto elem = ip;
        if (elem[0] != block && elem[1] != block && elem[2] != block && elem[3] != block) {
            continue;
        }
        std::cout << (int)ip[0] << '.' << (int)ip[1] << '.' << (int)ip[2] << '.' << (int)ip[3] << "\n";
    }
}