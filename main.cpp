#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "filters.h"

std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


int main() {
    try {
        std::vector<std::array<uint8_t, 4>> ip_pool;
        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            auto ip = split(v.at(0), '.');
            if (ip.size() < 4) {
                std::cerr << line << "Is wrong data, fix this record";
                continue;
            }
            std::vector<uint8_t> correctNumbers;
            for(int i = 0; i < 4; ++i){
                try {
                    correctNumbers.push_back(std::stoi(ip[i]));
                } catch (std::invalid_argument &err) {
                    std::cerr << line << "Is wrong data, fix this record";
                    break;
                }
            }
            ip_pool.push_back({correctNumbers[0],correctNumbers[1],correctNumbers[2],correctNumbers[3]});
        }
        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto &a, const auto &b) {
            for (int i = 0; i < 4; ++i) {
                if (a[i] < b[i]) {
                    return false;
                } else if (a[i] > b[i]) {
                    return true;
                }
            }
            return false;
        });

        printIPs(ip_pool);

        filter(ip_pool, 1);


        filter(ip_pool, 46, 70);


        filter_any(ip_pool, 46);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
