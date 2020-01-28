//
// Created by ali-masa on 1/27/20.
//
#include <gtest/gtest.h>
#include "price.h"

using namespace std;

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PriceBasicTests, DefaultPrice)
{
    Price<int, char> p;
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char>(0, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "0.00$");
}

TEST(PriceBasicTests, PriceWithoutCents)
{
    Price<int, char> p(10);
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char>(10, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.00$");
}

TEST(PriceBasicTests, PriceWithCents)
{
    Price<int, char> p(10, 90);
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char>(10, 90)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.90$");
}

TEST(PriceBasicOperatorsTests, PriceArthimiticsWithAssigning)
{
    Price<int, char> p;
    ASSERT_EQ(p++, (Price<int, char>(0.0)));
    ASSERT_EQ(++p, (Price<int, char>(2.0)));
    ASSERT_EQ(p += (Price<int, char>(2)), (Price<int, char>(4.0)));
    ASSERT_EQ(p *= (Price<int, char>(2)), (Price<int, char>(8.0)));
    ASSERT_EQ(p /= (Price<int, char>(2)), (Price<int, char>(4.0)));
    ASSERT_EQ(p -= (Price<int, char>(2)), (Price<int, char>(2.0)));
    ASSERT_EQ(p %= (Price<int, char>(2)), (Price<int, char>(0.0)));
}
TEST(PriceBasicOperatorsTests, PriceArthimiticsWithoutAssigning)
{
    Price<int, char> p1(1);
    Price<int, char> p2(2);
    stringstream ss;
    ASSERT_EQ(p1 + (Price<int, char>(2)), (Price<int, char>(1)) + p2);
    ASSERT_EQ(p1 * (Price<int, char>(2)), p2);
    ASSERT_EQ(p2 / (Price<int, char>(2)), p2 - (Price<int, char>(1)));
}
