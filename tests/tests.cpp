#include <gtest/gtest.h>
#include "../filters.h"

//1.70.44.170
//1.29.168.152
//1.1.234.8
//46.70.225.39
//46.70.147.26
//5.62.153.169
//5.15.220.203
//5.8.47.226
//5.8.47.202
//5.8.47.202
//5.8.47.100
//5.8.47.84
//5.8.47.44
const std::vector<std::vector<std::string>> ip_pool = {{"1","70", "44", "170"}, {"222", "173", "235", "246"},
                                                        {"46", "70", "225", "39"}, {"5", "8", "47", "226" }};

TEST(filters_tests, filter1) {
    std::vector<std::vector<std::string>> expect = {{"222", "173", "235", "246"}};
    auto result = filter(ip_pool,222);
    EXPECT_EQ(expect, result);
}
TEST(filters_tests, filter2) {
    std::vector<std::vector<std::string>> expect = {{"222", "173", "235", "246"}};
    auto result = filter(ip_pool,222, 173);
    EXPECT_EQ(expect, result);
}
TEST(filters_tests, filter_any) {
    std::vector<std::vector<std::string>> expect = {{"1","70", "44", "170"}, {"46", "70", "225", "39"}};
    auto result = filter_any(ip_pool,70);
    EXPECT_EQ(expect, result);
}
TEST(filters_tests, filter_any2) {
    std::vector<std::vector<std::string>> expect = {};
    auto result = filter_any(ip_pool,111);
    EXPECT_EQ(expect, result);
}
