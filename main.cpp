#include <iostream>
#include <map>
#include <vector>

#include "limited_allocator.h"
#include "allocator.h"


unsigned long long factorial(int value) {
    if (value <= 1) {
        return 1;
    } else {
        return factorial(value - 1) * (unsigned long long) value;
    }

}

int main(int, char **) {
    std::cout << "Allocator, limited on 10 elements, limited_allocator.h\n";
    try {
        std::map<int, int, std::less<>, limited_allocator<std::map<int, int>>> myMap;
        for (int i = 0; i < 10; ++i) {
            myMap.insert(std::make_pair(i, factorial(i)));
        }
        for (const auto &element: myMap) {
            std::cout << element.first << " " << element.second << "\n";
        }
    } catch (std::exception &err) {
        std::cout << err.what();
    }
    std::cout << "Unlimited allocator, allocator.h\n";
    try {
        std::map<int, int, std::less<>, allocator<std::map<int, int>>> myMap;
        for (int i = 0; i < 13; ++i) {
            myMap.insert(std::make_pair(i, factorial(i)));
        }
        for (const auto &element: myMap) {
            std::cout << element.first << " " << element.second << "\n";
        }
    } catch (std::exception &err) {
        std::cout << err.what();
    }
    return 0;
}
