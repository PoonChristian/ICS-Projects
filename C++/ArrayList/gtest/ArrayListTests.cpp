#include <gtest/gtest.h>
#include "ArrayList.hpp"

TEST(ArrayListTests, copyConstructorIsFunctional)
{
    ArrayList<int> a1;
    a1.add(1);
    a1.add(6);
    ArrayList<int> a2 = a1;
    ASSERT_EQ(6, a2.at(1));
}

TEST(ArrayListTests, assignmentOperatorisFunctional)
{
    ArrayList<int> a1;
    a1.add(1);
    a1.add(6);
    ArrayList<int> a2;
    a2 = a1;
    ASSERT_EQ(6, a2.at(1));
}

TEST(ArrayListTests, canReturnTheCorrectSize)
{
    ArrayList<int> a1;
    a1.add(0);
    a1.add(10);
    a1.add(20);
    ASSERT_EQ(3, a1.size());
}

TEST(ArrayListTests, canReturnTheCorrectCapacity)
{
    ArrayList<std::string> a1;
    ASSERT_EQ(10, a1.capacity());
}

TEST(ArrayListTests, canAddOneIntIntoArrayList)
{
    ArrayList<int> a1;
    a1.add(3);
    ASSERT_EQ(3, a1.at(0));
}

TEST(ArrayListTests, canAddOneStringIntoArrayList)
{
    ArrayList<std::string> a1;
    a1.add("Christian Poon");
    ASSERT_EQ("Christian Poon", a1.at(0));
}

TEST(ArrayListTests, canAddMultipleIntsIntoArrayList)
{
    ArrayList<int> a1;
    a1.add(1);
    a1.add(2);
    a1.add(3);
    ASSERT_EQ(1, a1.at(0));
    ASSERT_EQ(2, a1.at(1));
    ASSERT_EQ(3, a1.at(2));
}

TEST(ArrayListTests, canAddMultipleStringsIntoArrayList)
{
    ArrayList<std::string> a1;
    a1.add("Christian");
    a1.add("Tommy");
    a1.add("Poon");
    ASSERT_EQ("Christian", a1.at(0));
    ASSERT_EQ("Tommy", a1.at(1));
    ASSERT_EQ("Poon", a1.at(2));
}

TEST(ArrayListTests, canReturnItemsAtSpecifiedIndices)
{
    ArrayList<double> a1;
    a1.add(3.14);
    a1.add(.143);
    a1.add(43.1);
    ASSERT_EQ(3.14, a1.at(0));
    ASSERT_EQ(.143, a1.at(1));
    ASSERT_EQ(43.1, a1.at(2));
}


TEST(ArrayListTests, doesThrowAnExceptionFromOutofBoundsIndex)
{
    ArrayList<std::string> a1;
    a1.add("Tommy");
    EXPECT_THROW(a1.at(11), OutofBoundsException);
}
