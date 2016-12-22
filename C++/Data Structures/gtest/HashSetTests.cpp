#include <gtest/gtest.h>
#include <HashSet.hpp>
#include <StringHashing.hpp>


TEST(HashSetTests, sizeOfInitializedHashSetIsZero)
{
    HashSet<std::string> empty(hashStringAsZero);
    ASSERT_EQ(0, empty.size());
}

TEST(HashSetTests, bucketCountOfInitializedHashSetIsTen)
{
    HashSet<std::string> h1(hashStringAsSum);
    ASSERT_EQ(10, h1.bucketCount());
}

TEST(HashSetTests, copyConstructorIsFunctional)
{
    HashSet<std::string> h1(hashStringAsProduct);
    h1.add("ACA");
    HashSet<std::string> h2 = h1;
    ASSERT_EQ(true, h2.contains("ACA"));
}

TEST(HashSetTests, assignmentOperatorIsFunctional)
{
    HashSet<std::string> h1(hashStringAsProduct);
    HashSet<std::string> h2(hashStringAsProduct);
    h1.add("UCI");
    h1.add("UCSB");
    h2 = h1;
    ASSERT_EQ(true, h2.contains("UCI"));
    ASSERT_EQ(true, h2.contains("UCSB"));
}

TEST(HashSetTests, canAddElementToHashTable)
{
    HashSet<std::string> h1(hashStringAsSum);
    h1.add("Hello");
    h1.add("Goodbye");
    h1.add("World");
    ASSERT_EQ(3, h1.size());
}

TEST(HashSetTests, doesNotAddAnElementThatIsAlreadyInTheHashTable)
{
    HashSet<std::string> h1(hashStringAsProduct);
    h1.add("LVO");
    h1.add("VSU Modern");
    h1.add("LVO");
    ASSERT_EQ(2, h1.size());
}

TEST(HashSetTests, canDetermineWhetherHashTableContainsAnElement)
{
    HashSet<std::string> h1(hashStringAsProduct);
    h1.add("Christian");
    ASSERT_EQ(true, h1.contains("Christian"));
    ASSERT_EQ(false, h1.contains("Poon"));
}

TEST(HashSetTests, hashSetReturnsCorrectLoadFactor)
{
    HashSet<std::string> h1(hashStringAsSum);
    h1.add("Hello");
    ASSERT_EQ(0.1, h1.loadFactor());
}

TEST(HashSetTests, doesChangeBucketCountWhenLoadFactorGetsTooLarge)
{
    HashSet<std::string> danceTeams(hashStringAsSum);
    danceTeams.add("Kaba Modern");
    danceTeams.add("CADC");
    danceTeams.add("Common Ground");
    danceTeams.add("MCIA");
    danceTeams.add("INSA");
    danceTeams.add("Urban Motus");
    danceTeams.add("LVO");
    danceTeams.add("BBA");
    danceTeams.add("ACA");
    danceTeams.add("Team Millenia");
    ASSERT_EQ(21, danceTeams.bucketCount());
}
