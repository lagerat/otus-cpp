#include <gtest/gtest.h>
#include "../allocator.h"
#include "../limited_allocator.h"

TEST(limited_allocator, test1) {
    std::map<int, int, std::less<>, limited_allocator<std::map<int, int>>> myMap;
    for (int i = 0; i < 10; ++i) {
        myMap.insert(std::make_pair(i,i));
    }
    EXPECT_THROW({myMap.insert(std::make_pair(1,1));}, std::bad_alloc);
}