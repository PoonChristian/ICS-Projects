#include <gtest/gtest.h>
#include <BSTSet.hpp>

TEST(BSTSetTests, sizeOfBinarySearchTreeIsZeroAtInitialization)
{
    BSTSet<std::string> b1;
    ASSERT_EQ(0, b1.size());
}

TEST(BSTSetTests, copyConstructorIsFunctional)
{
    BSTSet<std::string> b1;
    b1.add("Ascension");
    b1.add("Chaotic 3");
    BSTSet<std::string> b2 = b1;
    ASSERT_EQ(true, b2.contains("Ascension"));
    ASSERT_EQ(true, b2.contains("Chaotic 3"));
}

TEST(BSTSetTests, assignmentOperatorIsFunctional)
{
    BSTSet<std::string> b1;
    BSTSet<std::string> b2;
    b1.add("UCLA");
    b1.add("UC Berkeley");
    b2 = b1;
    ASSERT_EQ(true, b2.contains("UCLA"));
    ASSERT_EQ(true, b2.contains("UC Berkeley"));
}

TEST(BSTSetTests, canAddElementIntoBinarySearchTree)
{
    BSTSet<std::string> b1;
    b1.add("Choreo Cookies");
    ASSERT_EQ(1, b1.size());
}

TEST(BSTSetTests, doesNotAddAnElementThatIsAlreadyInTheBinarySearchTree)
{
    BSTSet<std::string> b1;
    b1.add("LVO");
    b1.add("VSU Modern");
    b1.add("LVO");
    ASSERT_EQ(2, b1.size());
}

TEST(BSTSetTests, canDetermineSizeOfBinarySearchTreeAfterMultipleAdds)
{
    BSTSet<std::string> b1;
    b1.add("The Company");
    b1.add("PraiseTEAM");
    b1.add("BrotherHood");
    ASSERT_EQ(3, b1.size());
}

TEST(BSTSetTests, canDetermineWhetherBinarySearchTreeContainsAnElement)
{
    BSTSet<std::string> b1;
    b1.add("GRV");
    b1.add("ACA");
    ASSERT_EQ(true, b1.contains("GRV"));
    ASSERT_EQ(true, b1.contains("ACA"));
}
