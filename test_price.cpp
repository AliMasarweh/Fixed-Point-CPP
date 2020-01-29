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
    FixedPoint<2, int, char> p;
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<2, int, char>(0, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "0.00$");
}

TEST(FixedPointBasicTests, FixedPointWithoutCents)
{
    FixedPoint<2, int, char> p(10);
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<2, int, char>(10, 0)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.00$");
}

TEST(FixedPointBasicTests, FixedPointWithCents)
{
    FixedPoint<2, int, char> p(10, 90);
    stringstream ss;
    ASSERT_EQ(p, (FixedPoint<2, int, char>(10, 90)));
    ss << p;
    ASSERT_EQ(ss.str(), "10.90$");
}

TEST(FixedPointBasicOperatorsTests, FixedPointArthimiticsWithAssigning)
{
    FixedPoint<2, int, char> p;
    ASSERT_EQ(p++, (FixedPoint<2, int, char>(0.0)));
    ASSERT_EQ(++p, (FixedPoint<2, int, char>(2.0)));
    ASSERT_EQ(p += (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(4.0)));
    ASSERT_EQ(p *= (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(8.0)));
    ASSERT_EQ(p /= (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(4.0)));
    ASSERT_EQ(p -= (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(2.0)));
    ASSERT_EQ(p %= (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(0.0)));
}
TEST(FixedPointBasicOperatorsTests, FixedPointArthimiticsWithoutAssigning)
{
    FixedPoint<2, int, char> p1(1);
    FixedPoint<2, int, char> p2(2);
    ASSERT_EQ(p1 + (FixedPoint<2, int, char>(2)), (FixedPoint<2, int, char>(1)) + p2);
    ASSERT_EQ(p1 * (FixedPoint<2, int, char>(2)), p2);
    ASSERT_EQ(p2 / (FixedPoint<2, int, char>(2)), p2 - (FixedPoint<2, int, char>(1)));
}

TEST(FixedPointAdvancedOperatorsTests, FixedPointBigNumberMultiplications)
{
    unsigned long long bigNumber = 3 * pow(10, 9);
    FixedPoint<2, unsigned long long, char> p1(bigNumber);
    FixedPoint<2, unsigned long long, char> p2(bigNumber);

    stringstream ss;
    ss << (p1*p2);

    unsigned long long bigNumbersMulResult = 9 * pow(10, 18);

    stringstream ss2;
    ss2 << bigNumbersMulResult << ".00$";
    ASSERT_EQ(ss.str(), ss2.str());
}

TEST(FixedPointAdvancedOperatorsTests, FixedPointRealNumersMultiplications)
{
    FixedPoint<2, unsigned long long, long long> p1(13491, 16);
    FixedPoint<2, unsigned long long, long long> p2(1674, 21);

    stringstream ss;
    ss << (p1*p2);

    int completeNumbersMulResult = 22587034;
    int afterCommaMulResult = 98;

    stringstream ss2;
    ss2 << completeNumbersMulResult << "." << afterCommaMulResult << "$";
    ASSERT_EQ(ss.str(), ss2.str());

    FixedPoint<4, int, long long> p3(0, 25);
    FixedPoint<4, int, long long> p4(0, 25);

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
    FixedPoint<10, long, long> p1(22);
    FixedPoint<10, long, long> p2(7);

    stringstream ss;
    ss << (p1/p2);

    ASSERT_EQ(ss.str(), "3.1428571428$");
}

TEST(FixedPointMakeMoney, FixedPointMakeMoneyBasic)
{
    FixedPoint<2> p1(22, 16);
    FixedPoint<2> p2(1946, 46);
    FixedPoint<2> p3(119194, 78);
    FixedPoint<2> p4(2772, 18);
    FixedPoint<2> p5(0, 64);
    FixedPoint<2> p6(124495169, 27);
    FixedPoint<2> p7(2020495169, 27);

    ASSERT_EQ(p1.makeMoney(), "twenty-two dollars and sixteen cents");
    ASSERT_EQ(p2.makeMoney(), "one thousand, nine hundred and forty-six dollars and forty-six cents");
    ASSERT_EQ(p3.makeMoney(), "one hundred and nineteen thousand, one hundred and ninety-four dollars and seventy-eight cents");
    ASSERT_EQ(p4.makeMoney(), "two thousand, seven hundred and seventy-two dollars and eighteen cents");
    ASSERT_EQ(p5.makeMoney(), "sixty-four cents");
    ASSERT_EQ(p6.makeMoney(),"one hundred and twenty-four million, four hundred and ninety-five thousand, one hundred and sixty-nine dollars and twenty-seven cents");
    ASSERT_EQ(p7.makeMoney(),"two billion, twenty million, four hundred and ninety-five thousand, one hundred and sixty-nine dollars and twenty-seven cents");
}