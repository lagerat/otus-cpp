#include <cstdlib>
#include <sstream>
#include <algorithm>

#include "filters.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;
        std::istringstream input;
        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        std::sort(ip_pool.begin(), ip_pool.end(), [](const std::vector<std::string>&  a,
                                                                    const  std::vector<std::string>  &b){
            for (int i = 0; i < 4; ++i)
            {
                if (std::atoi(a[i].c_str()) < std::atoi(b[i].c_str())){
                    return false;
                } else if(std::atoi(a[i].c_str()) > std::atoi(b[i].c_str())){
                    return true;
                }
            }
            return false;
        });

        printIPs(ip_pool);

        auto ip = filter(ip_pool, 1);
        printIPs(ip);


        ip = filter(ip_pool, 46, 70);
        printIPs(ip);


        ip = filter_any(ip_pool, 46);
        printIPs(ip);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
