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
    Price<int, char, 2> p;
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char, 2>(0, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "0.00$");
}

TEST(PriceBasicTests, PriceWithoutCents)
{
    Price<int, char, 2> p(10);
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char, 2>(10, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.00$");
}

TEST(PriceBasicTests, PriceWithCents)
{
    Price<int, char, 2> p(10, 90);
    stringstream ss;
    ASSERT_EQ(p, (Price<int, char, 2>(10, 90)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.90$");
}

TEST(PriceBasicOperatorsTests, PriceArthimiticsWithAssigning)
{
    Price<int, char, 2> p;
    ASSERT_EQ(p++, (Price<int, char, 2>(0.0)));
    ASSERT_EQ(++p, (Price<int, char, 2>(2.0)));
    ASSERT_EQ(p += (Price<int, char, 2>(2)), (Price<int, char, 2>(4.0)));
    ASSERT_EQ(p *= (Price<int, char, 2>(2)), (Price<int, char, 2>(8.0)));
    ASSERT_EQ(p /= (Price<int, char, 2>(2)), (Price<int, char, 2>(4.0)));
    ASSERT_EQ(p -= (Price<int, char, 2>(2)), (Price<int, char, 2>(2.0)));
    ASSERT_EQ(p %= (Price<int, char, 2>(2)), (Price<int, char, 2>(0.0)));
}
TEST(PriceBasicOperatorsTests, PriceArthimiticsWithoutAssigning)
{
    Price<int, char, 2> p1(1);
    Price<int, char, 2> p2(2);
    ASSERT_EQ(p1 + (Price<int, char, 2>(2)), (Price<int, char, 2>(1)) + p2);
    ASSERT_EQ(p1 * (Price<int, char, 2>(2)), p2);
    ASSERT_EQ(p2 / (Price<int, char, 2>(2)), p2 - (Price<int, char, 2>(1)));
}

TEST(PriceAdvancedOperatorsTests, PriceBigNumberMultiplications)
{
    unsigned long long bigNumber = 3 * pow(10, 9);
    Price<unsigned long long, char, 2> p1(bigNumber);
    Price<unsigned long long, char, 2> p2(bigNumber);

    stringstream ss;
    ss << (p1*p2);

    unsigned long long bigNumbersMulResult = 9 * pow(10, 18);

    stringstream ss2;
    ss2 << bigNumbersMulResult << "$";
    ASSERT_EQ(ss.str(), ss2.str());
}

TEST(PriceAdvancedOperatorsTests, PriceDivisionAccuracy)
{
    Price<int, int, 8> p1(22);
    Price<int, int, 8> p2(7);

    stringstream ss;
    ss << (p1/p2);

    ASSERT_EQ(ss.str(), "3.14285714$");
}