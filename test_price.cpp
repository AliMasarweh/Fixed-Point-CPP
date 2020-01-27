//
// Created by ali-masa on 1/27/20.
//
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PriceBasicTests, DefaultPrice)
{
    Price p();
    stringstream ss;
    ASSERT_EQ(p, 0.00);
    ss << p;
    ASSERT_EQ(ss.str(), "0.00");
}

TEST(PriceBasicTests, PriceWithoutCents)
{
    Price p(10);
    ASSERT_EQ(p, 10);
    ss << p;
    ASSERT_EQ(ss.str(), "10.00");
}

TEST(PriceBasicTests, PriceWithCents)
{
    Price p(10, 90);
    ASSERT_EQ(p, 10.9);
    ss << p;
    ASSERT_EQ(ss.str(), "10.90");
}