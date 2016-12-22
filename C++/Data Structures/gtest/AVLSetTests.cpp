#include <gtest/gtest.h>
#include <AVLSet.hpp>

TEST(AVLSetTests, sizeOfAVLTreeIsZeroAtInitialization)
{
    AVLSet<std::string> a1;
    ASSERT_EQ(0, a1.size());
}

TEST(AVLSetTests, copyConstructorIsFunctional)
{
    AVLSet<std::string> a1;
    a1.add("Ascension");
    a1.add("Chaotic 3");
    AVLSet<std::string> a2 = a1;
    ASSERT_EQ(true, a2.contains("Ascension"));
    ASSERT_EQ(true, a2.contains("Chaotic 3"));
}

TEST(AVLSetTests, assignmentOperatorIsFunctional)
{
    AVLSet<std::string> a1;
    AVLSet<std::string> a2;
    a1.add("UCLA");
    a1.add("UC Berkeley");
    a2 = a1;
    ASSERT_EQ(true, a2.contains("UCLA"));
    ASSERT_EQ(true, a2.contains("UC Berkeley"));
}

TEST(AVLSetTests, canAddElementIntoAVLTree)
{
    AVLSet<std::string> a1;
    a1.add("Choreo Cookies");
    ASSERT_EQ(1, a1.size());
}

TEST(AVLSetTests, doesNotAddAnElementThatIsAlreadyInTheAVLTree)
{
    AVLSet<std::string> a1;
    a1.add("LVO");
    a1.add("VSU Modern");
    a1.add("LVO");
    ASSERT_EQ(2, a1.size());
}

TEST(AVLSetTests, canDetermineSizeOfAVLTreeAfterMultipleAdds)
{
    AVLSet<std::string> a1;
    a1.add("The Company");
    a1.add("PraiseTEAM");
    a1.add("BrotherHood");
    ASSERT_EQ(3, a1.size());
}

TEST(AVLSetTests, canGetHeightFromTreeAfterRotations)
{
    AVLSet<int> a1;
    a1.add(30);
    a1.add(20);
    a1.add(10);
    a1.add(40);
    a1.add(50);
    ASSERT_EQ(2, a1.getHeight());
}

TEST(AVLSetTests, canDetermineWhetherAVLTreeContainsAnElement)
{
    AVLSet<std::string> a1;
    a1.add("GRV");
    a1.add("ACA");
    ASSERT_EQ(true, a1.contains("GRV"));
    ASSERT_EQ(false, a1.contains("ACa"));
}

TEST(AVLSetTests, canDetermineHeightOfAnAVLTree)
{
    AVLSet<std::string> a1;
    a1.add("Hello");
    a1.add("People");
    a1.add("Car");
    a1.add("Dad");
    ASSERT_EQ(2, a1.getHeight());
}

TEST(AVLSetTests, canDetermineBalanceFactorOfAnAVLTree)
{
    AVLSet<std::string> a1;
    a1.add("Hello");
    a1.add("People");
    a1.add("Car");
    a1.add("Dad");
    a1.add("Bad");
    ASSERT_EQ(1, a1.getBalanceFactor());
}

TEST(AVLSetTests, canBalanceAVLTreeProperlyAndManageHeight)
{
    AVLSet<int> numbers;
    numbers.add(30);
    numbers.add(20);
    numbers.add(10);
    numbers.add(25);
    numbers.add(27);
    numbers.add(23);
    numbers.add(5);
    numbers.add(35);
    ASSERT_EQ(3, numbers.getHeight());

}

TEST(AVLSetTests, doesContainAllKeysAfterBalancingAVLTree)
{
    AVLSet<std::string> words;
    words.add("Hello");
    words.add("Eel");
    words.add("Bad");
    words.add("Force");
    words.add("Fat");
    words.add("Gun");
    words.add("Ill");
    ASSERT_EQ(true, words.contains("Hello"));
    ASSERT_EQ(true, words.contains("Eel"));
    ASSERT_EQ(true, words.contains("Bad"));
    ASSERT_EQ(true, words.contains("Bad"));
    ASSERT_EQ(true, words.contains("Force"));
    ASSERT_EQ(true, words.contains("Fat"));
    ASSERT_EQ(true, words.contains("Gun"));
    ASSERT_EQ(true, words.contains("Ill"));
}

TEST(AVLSetTests, doesCorrectlyBalanceMultipleAVLTrees)
{
    AVLSet<std::string> a1;
    a1.add("Hello");
    a1.add("Eel");
    a1.add("Ill");
    a1.add("Bad");
    a1.add("Force");
    a1.add("Fat");
    a1.add("Gun");
    ASSERT_EQ(2, a1.getHeight());

    AVLSet<int> numbers;
    numbers.add(3);
    numbers.add(2);
    numbers.add(1);
    numbers.add(4);
    numbers.add(5);
    numbers.add(6);
    numbers.add(7);
    numbers.add(16);
    numbers.add(15);
    numbers.add(14);
    ASSERT_EQ(3, numbers.getHeight());

    AVLSet<std::string> teams;
    teams.add("Hawks");
    teams.add("Raptors");
    teams.add("Cavs");
    teams.add("Celtics");
    teams.add("Bulls");
    teams.add("Warriors");
    teams.add("Thunder");
    teams.add("Spurs");
    teams.add("Trail Blazers");
    teams.add("Sixers");
    teams.add("Nuggets");
    ASSERT_EQ(3, teams.getHeight());
    
    AVLSet<std::string> words;
    words.add("Hello");
    words.add("People");
    words.add("Car");
    words.add("Dad");
    words.add("Bad");
    words.add("Attitude");
    ASSERT_EQ(2, words.getHeight());
}
