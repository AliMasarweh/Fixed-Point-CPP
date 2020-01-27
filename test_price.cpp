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
    Price p;
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

TEST(PriceBasicOperatorsTests, PriceArthimiticsWithAssigning)
{
    Price p;
    ASSERT_EQ(p++, 0.0);
    ASSERT_EQ(++p, 2.0);
    ASSERT_EQ(p += 2, 4.0);
    ASSERT_EQ(p *= 2, 8.0);
    ASSERT_EQ(p /= 2, 4.0);
    ASSERT_EQ(p -= 2, 2.0);
    ASSERT_EQ(p %= 2, 0.0);
}

TEST(PriceBasicOperatorsTests, PriceArthimiticsWithoutAssigning)
{
    Price p1(1);
    Price p2(2);
    ASSERT_EQ(p1 + 2, 1 + p2);
    ASSERT_EQ(p1 * 2, p2);
    ASSERT_EQ(p2 / 2, p2 - 1);
}