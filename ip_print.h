#ifndef SFINAE_IP_IP_PRINT_H
#define SFINAE_IP_IP_PRINT_H

#include "additional_func.h"
#include <type_traits>
#include <iostream>
#include <cstdint>
#include <iterator>
#include <algorithm>
#include <vector>

//Integers
template <typename T,
        typename Fake = std::enable_if_t<std::is_integral_v<T>, void>>
void print_ip(T ip)
{
    std::vector<u_int8_t> result;
    for(size_t i = 0; i < sizeof(ip); ++i){
        result.push_back(ip & 0xFF);
        ip = ip >> 8;
    }
    for(int i = result.size() - 1; i >= 0; --i){
        if(i < static_cast<int>(result.size()) - 1){
            std::cout << '.';
        }
        std::cout << static_cast<int>(result[i]);
    }
    std::cout << std::endl;
}

//Containers
template <typename T,
        typename Fake = std::enable_if_t<additional::has_iterator_v<T> && !additional::is_string_v<T>, void>>
void print_ip(const T& ip)
{
    if (ip.empty())
        return;
    const char* delim = ".";
    std::copy(ip.begin(), std::prev(ip.end()),
              std::ostream_iterator<typename T::value_type>(std::cout, delim));
    std::cout << *ip.rbegin() << std::endl;
}

//String
template <typename T,
        typename Fake = std::enable_if_t<additional::is_string_v<T>, void>>
void print_ip(const T& ip, Fake* = nullptr)
{
    std::cout << ip << std::endl;
}


#endif //SFINAE_IP_IP_PRINT_H
