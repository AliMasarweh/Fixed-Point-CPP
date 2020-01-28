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

TEST(FixedPointBasicTests, DefaultFixedPoint)
{
    FixedPoint<int, char, 2> p;
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<int, char, 2>(0, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "0.00$");
}

TEST(FixedPointBasicTests, FixedPointWithoutCents)
{
    FixedPoint<int, char, 2> p(10);
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<int, char, 2>(10, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.00$");
}

TEST(FixedPointBasicTests, FixedPointWithCents)
{
    FixedPoint<int, char, 2> p(10, 90);
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<int, char, 2>(10, 90)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.90$");
}

TEST(FixedPointBasicOperatorsTests, FixedPointArthimiticsWithAssigning)
{
    FixedPoint<int, char, 2> p;
    ASSERT_EQ(p++, (FixedPoint<int, char, 2>(0.0)));
    ASSERT_EQ(++p, (FixedPoint<int, char, 2>(2.0)));
    ASSERT_EQ(p += (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(4.0)));
    ASSERT_EQ(p *= (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(8.0)));
    ASSERT_EQ(p /= (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(4.0)));
    ASSERT_EQ(p -= (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(2.0)));
    ASSERT_EQ(p %= (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(0.0)));
}
TEST(FixedPointBasicOperatorsTests, FixedPointArthimiticsWithoutAssigning)
{
    FixedPoint<int, char, 2> p1(1);
    FixedPoint<int, char, 2> p2(2);
    ASSERT_EQ(p1 + (FixedPoint<int, char, 2>(2)), (FixedPoint<int, char, 2>(1)) + p2);
    ASSERT_EQ(p1 * (FixedPoint<int, char, 2>(2)), p2);
    ASSERT_EQ(p2 / (FixedPoint<int, char, 2>(2)), p2 - (FixedPoint<int, char, 2>(1)));
}

TEST(FixedPointAdvancedOperatorsTests, FixedPointBigNumberMultiplications)
{
    unsigned long long bigNumber = 3 * pow(10, 9);
    FixedPoint<unsigned long long, char, 2> p1(bigNumber);
    FixedPoint<unsigned long long, char, 2> p2(bigNumber);

    stringstream ss;
    ss << (p1*p2);

    unsigned long long bigNumbersMulResult = 9 * pow(10, 18);

    stringstream ss2;
    ss2 << bigNumbersMulResult << ".00$";
    ASSERT_EQ(ss.str(), ss2.str());
}

TEST(FixedPointAdvancedOperatorsTests, FixedPointRealNumersMultiplications)
{
    FixedPoint<unsigned long long, long long, 2> p1(13491, 16);
    FixedPoint<unsigned long long, long long, 2> p2(1674, 21);

    stringstream ss;
    ss << (p1*p2);

    int completeNumbersMulResult = 22587034;
    int afterCommaMulResult = 98;

    stringstream ss2;
    ss2 << completeNumbersMulResult << "." << afterCommaMulResult << "$";
    ASSERT_EQ(ss.str(), ss2.str());

    FixedPoint<int, long long, 4> p3(0, 25);
    FixedPoint<int, long long, 4> p4(0, 25);

    ss.clear();
    ss2.clear();

    ss << (p3*p4);

    completeNumbersMulResult = 0;
    afterCommaMulResult = 625;

    ss2 << completeNumbersMulResult << ".0" << afterCommaMulResult << "$";
    ASSERT_EQ(ss.str(), ss2.str());
}


TEST(FixedPointAdvancedOperatorsTests, FixedPointDivisionAccuracy)
{
    FixedPoint<long, long, 10> p1(22);
    FixedPoint<long, long, 10> p2(7);

    stringstream ss;
    ss << (p1/p2);

    ASSERT_EQ(ss.str(), "3.1428571428$");
}