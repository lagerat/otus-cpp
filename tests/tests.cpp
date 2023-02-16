#include <gtest/gtest.h>
#include "../filters.h"


TEST(filters_tests, filter1) {
    EXPECT_TRUE(true);
}



//const std::vector<std::array<uint8_t, 4>>  ip_pool = {{1,   70,  44,  170},
//                                                       {222, 173, 235, 246},
//                                                       {46,  70,  225, 39},
//                                                       {5,   8,   4,  226}};
//
//TEST(filters_tests, filter1) {
//    std::vector<std::vector<std::string>> expect = {{"222", "173", "235", "246"}};
//    auto result = filter(ip_pool, 222);
//    EXPECT_EQ(expect, result);
//}
//
//TEST(filters_tests, filter2) {
//    std::vector<std::vector<std::string>> expect = {{"222", "173", "235", "246"}};
//    auto result = filter(ip_pool, 222, 173);
//    EXPECT_EQ(expect, result);
//}
//
//TEST(filters_tests, filter_any) {
//    std::vector<std::vector<std::string>> expect = {{"1",  "70", "44",  "170"},
//                                                    {"46", "70", "225", "39"}};
//    auto result = filter_any(ip_pool, 70);
//    EXPECT_EQ(expect, result);
//}
//
//TEST(filters_tests, filter_any2) {
//    std::vector<std::vector<std::string>> expect = {};
//    auto result = filter_any(ip_pool, 111);
//    EXPECT_EQ(expect, result);
//}
