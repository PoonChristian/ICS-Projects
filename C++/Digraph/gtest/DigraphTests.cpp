#include <gtest/gtest.h>
#include <Digraph.hpp>

TEST(DigraphTests, copyConstructorIsFunctional)
{
    Digraph<std::string, int> d1;
    d1.addVertex(1, "LVO");
    d1.addVertex(2, "MCIA");
    d1.addEdge(1, 2, 5);
    Digraph<std::string, int> d2 = d1;
    ASSERT_EQ(2, d2.vertexCount());
    ASSERT_EQ("LVO", d2.vertexInfo(1));
    ASSERT_EQ("MCIA", d2.vertexInfo(2));
    ASSERT_EQ(1, d2.edgeCount());
    ASSERT_EQ(5, d2.edgeInfo(1, 2));
}


TEST(DigraphTests, assignmentOperatorIsFunctional)
{
    Digraph<std::string, int> d1;
    Digraph<std::string, int> d2;
    d1.addVertex(1, "Urban Motus");
    d1.addVertex(2, "INSA");
    d1.addEdge(1, 2, 5);
    d2 = d1;
    ASSERT_EQ(2, d2.vertexCount());
    ASSERT_EQ("Urban Motus", d2.vertexInfo(1));
    ASSERT_EQ("INSA", d2.vertexInfo(2));
    ASSERT_EQ(1, d2.edgeCount());
    ASSERT_EQ(5, d2.edgeInfo(1, 2));
}


TEST(DigraphTests, canAddVerticesIntoDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(5, "Hello");
    d1.addVertex(10, "Goodbye");
    ASSERT_EQ(2, d1.vertexCount());
    ASSERT_THROW(d1.addVertex(5, "From the other side"), DigraphException);
}


TEST(DigraphTests, canGetAllVertexNumbersFromDigraph)
{
    Digraph<int, int> d1;
    int vertexArray[] = {10, 20, 30, 40};
    d1.addVertex(vertexArray[3], 7);
    d1.addVertex(vertexArray[0], 14);
    d1.addVertex(vertexArray[2], 21);
    d1.addVertex(vertexArray[1], 28);
    std::vector<int> vertices (vertexArray, vertexArray + sizeof(vertexArray) / sizeof(int));
    ASSERT_EQ(vertices, d1.vertices());
}


TEST(DigraphTests, canGetVertexInfoFromDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(8, "UCI");
    ASSERT_EQ("UCI", d1.vertexInfo(8));
    ASSERT_THROW(d1.vertexInfo(4), DigraphException);
}


TEST(DigraphTests, canRemoveVertexFromDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(3, "UCR");
    d1.addVertex(4, "UCLA");
    ASSERT_EQ("UCR", d1.vertexInfo(3));
    d1.removeVertex(3);
    ASSERT_THROW(d1.vertexInfo(3), DigraphException);
    ASSERT_EQ(1, d1.vertexCount());
}


TEST(DigraphTests, canGetNumberOfVerticesFromDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(2, "Cleveland Cavaliers");
    d1.addVertex(3, "Golden State Warriors");
    ASSERT_EQ(2, d1.vertexCount());
}


TEST(DigraphTests, canAddEdgesIntoDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(0, "UCM");
    d1.addVertex(1, "UCSC");
    d1.addVertex(2, "UCR");
    d1.addEdge(0, 1, 5);
    d1.addEdge(1, 2, 8);
    ASSERT_EQ(2, d1.edgeCount());
    ASSERT_THROW(d1.addEdge(1, 2, 10), DigraphException);
}


TEST(DigraphTests, canGetAllEdgePairsFromDigraph)
{
    Digraph<int, int> d1;
    d1.addVertex(30, 5);
    d1.addVertex(11, 7);
    d1.addEdge(30, 11, 1738);
    d1.addEdge(30, 30, 3005);
    d1.addEdge(11, 11, 9000);
    std::pair<int, int> edgeArray[] = {std::make_pair(11, 11),
                                       std::make_pair(30, 11),
                                       std::make_pair(30, 30)};
    std::vector<std::pair<int, int>> edges(edgeArray, edgeArray + sizeof(edgeArray) / sizeof(std::pair<int, int>));
    ASSERT_EQ(edges, d1.edges());
}


TEST(DigraphTests, canGetEdgesPairsFromCertainVertexOnDigraph)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);
    d1.addEdge(1, 2, 70);
    d1.addEdge(1, 3, 90);
    std::pair<int, int> edgeArray[] = {std::make_pair(1, 2), std::make_pair(1, 3)};
    std::vector<std::pair<int, int>> edges(edgeArray, edgeArray + sizeof(edgeArray) / sizeof(std::pair<int, int>));
    ASSERT_EQ(edges, d1.edges(1));
    ASSERT_THROW(d1.edges(4), DigraphException);
}


TEST(DigraphTests, canGetEdgeInfoFromDigraph)
{
    Digraph<double, double> d1;
    d1.addVertex(5, 4.0);
    d1.addVertex(10, 8.0);
    d1.addEdge(5, 10, 32.0);
    ASSERT_EQ(32.0, d1.edgeInfo(5, 10));
    ASSERT_THROW(d1.edgeInfo(5, 11), DigraphException);
}


TEST(DigraphTests, canRemoveEdgeFromDigraph)
{
    Digraph<std::string, double> d1;
    d1.addVertex(1, "San Francisco");
    d1.addVertex(2, "Oakland");
    d1.addVertex(3, "San Jose");
    d1.addEdge(1, 2, 1.5);
    d1.addEdge(2, 3, 2.5);
    ASSERT_EQ(2, d1.edgeCount());
    d1.removeEdge(1, 2);
    ASSERT_THROW(d1.edgeInfo(1, 2), DigraphException);
    ASSERT_EQ(1, d1.edgeCount());
}


TEST(DigraphTests, canGetTotalNumberOfEdgesFromDigraph)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "J. Cole");
    d1.addVertex(2, "Bas");
    d1.addVertex(3, "Cozz");
    d1.addVertex(4, "Omen");
    d1.addEdge(1, 2, "Dreamvillain 1");
    d1.addEdge(1, 3, "Dreamvillain 2");
    d1.addEdge(1, 4, "Dreamvillain 3");
    d1.addEdge(2, 3, "Fiend 1");
    ASSERT_EQ(4, d1.edgeCount());
}


TEST(DigraphTests, canGetNumberOfEdgesFromCertainVertexOnDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(30, "Stephen Curry");
    d1.addVertex(11, "Klay Thompson");
    d1.addVertex(23, "Draymond Green");
    d1.addVertex(40, "Harrison Barnes");
    d1.addVertex(12, "Andrew Bogut");
    d1.addEdge(30, 11, 41);
    d1.addEdge(30, 23, 53);
    d1.addEdge(11, 23, 44);
    d1.addEdge(40, 12, 52);
    ASSERT_EQ(2, d1.edgeCount(30));
    ASSERT_THROW(d1.edgeCount(31), DigraphException);
}


TEST(DigraphTests, canDetermineStrongConnectivenessOfDigraph)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Hello");
    d1.addVertex(2, "Goodbye");
    d1.addEdge(1, 2, "World");
    d1.addEdge(2, 1, "Universe");
    bool connectiveness = d1.isStronglyConnected();
    ASSERT_EQ(true, connectiveness);

    Digraph<std::string, std::string> d2;
    d2.addVertex(50, "F");
    d2.addVertex(60, "D");
    d2.addVertex(70, "C");
    d2.addVertex(80, "B");
    d2.addVertex(90, "A");
    d2.addVertex(100, "A+");
    d2.addEdge(50, 60, "Failing");
    d2.addEdge(60, 70, "Danger");
    d2.addEdge(70, 80, "Average");
    d2.addEdge(80, 90, "Above Average");
    d2.addEdge(90, 100, "Excellent");
    //d2.addEdge(100, 50, "Disappointment"); // This makes the isStronglyConnected() true
    ASSERT_EQ(false, d2.isStronglyConnected());

    Digraph<std::string, int> d3;
    d3.addVertex(10, "A");
    d3.addVertex(9, "B");
    d3.addVertex(8, "C");
    d3.addVertex(7, "D");
    d3.addVertex(6, "E");
    d3.addEdge(10, 9, 21);
    d3.addEdge(9, 8, 17);
    d3.addEdge(8, 10, 18);
    d3.addEdge(8, 7, 15);
    d3.addEdge(7, 6, 13);
    d3.addEdge(6, 8, 14);
    ASSERT_EQ(true, d3.isStronglyConnected());

    Digraph<int, int> d4;
    d4.addVertex(0, 0);
    d4.addVertex(1, 1);
    d4.addVertex(2, 2);
    d4.addVertex(3, 3);
    d4.addVertex(4, 4);
    d4.addEdge(0, 1, 1);
    d4.addEdge(1, 2, 3);
    d4.addEdge(2, 3, 5);
    d4.addEdge(2, 4, 6);
    d4.addEdge(3, 0, 3);
    d4.addEdge(4, 2, 6);
    ASSERT_EQ(true, d4.isStronglyConnected());

    Digraph<int, int> d5;
    d5.addVertex(0, 0);
    d5.addVertex(1, 1);
    d5.addVertex(2, 2);
    d5.addVertex(3, 3);
    d5.addEdge(0, 1, 1);
    d5.addEdge(2, 3, 5);
    ASSERT_EQ(false, d5.isStronglyConnected());
}


TEST(DigraphTests, canFindTheShortestPathFromVertexOfDigraph)
{
    Digraph<std::string, int> d1;
    d1.addVertex(0, "A");
    d1.addVertex(1, "B");
    d1.addVertex(2, "C");
    d1.addVertex(3, "D");
    d1.addVertex(4, "E");
    d1.addVertex(5, "F");
    d1.addEdge(0, 1, 10);
    d1.addEdge(0, 2, 3);
    d1.addEdge(1, 3, 5);
    d1.addEdge(1, 4, 1);
    d1.addEdge(2, 1, 4);
    d1.addEdge(2, 3, 2);
    d1.addEdge(3, 5, 7);
    d1.addEdge(4, 5, 4);
    std::function<double(const int&)> edgeWeightFunc = [](const int& einfo)
    {
        return einfo;
    };
    std::map<int, int> paths;
    paths[0] = 0;
    paths[1] = 2;
    paths[2] = 0;
    paths[3] = 2;
    paths[4] = 1;
    paths[5] = 3;
    ASSERT_EQ(paths, d1.findShortestPaths(0, edgeWeightFunc));


    Digraph<std::string, int> d2;
    d2.addVertex(7, "A");
    d2.addVertex(4, "B");
    d2.addVertex(5, "C");
    d2.addVertex(3, "D");
    d2.addVertex(2, "E");
    d2.addVertex(1, "F");
    d2.addEdge(7, 4, 10);
    d2.addEdge(7, 5, 3);
    d2.addEdge(4, 3, 5);
    d2.addEdge(4, 2, 1);
    d2.addEdge(5, 4, 4);
    d2.addEdge(5, 3, 2);
    d2.addEdge(3, 1, 7);
    d2.addEdge(2, 1, 4);
    std::map<int, int> paths2;
    paths2[7] = 7;
    paths2[4] = 5;
    paths2[5] = 7;
    paths2[3] = 5;
    paths2[2] = 4;
    paths2[1] = 3;
    ASSERT_EQ(paths2, d2.findShortestPaths(7, edgeWeightFunc));

    Digraph<std::string, int> d3;
    d3.addVertex(1, "A");
    d3.addVertex(2, "B");
    d3.addVertex(3, "C");
    d3.addVertex(4, "D");
    d3.addVertex(5, "E");
    d3.addVertex(6, "F");
    d3.addVertex(7, "G");
    d3.addVertex(8, "H");
    d3.addEdge(1, 2, 20);
    d3.addEdge(1, 4, 80);
    d3.addEdge(1, 7, 90);
    d3.addEdge(2, 6, 10);
    d3.addEdge(3, 4, 10);
    d3.addEdge(3, 6, 50);
    d3.addEdge(3, 8, 20);
    d3.addEdge(4, 3, 10);
    d3.addEdge(4, 7, 20);
    d3.addEdge(5, 2, 50);
    d3.addEdge(5, 7, 30);
    d3.addEdge(6, 3, 10);
    d3.addEdge(6, 4, 40);
    d3.addEdge(7, 1, 20);
    std::map<int, int> otherPaths;
    otherPaths[1] = 1;
    otherPaths[2] = 1;
    otherPaths[3] = 6;
    otherPaths[4] = 3;
    otherPaths[5] = 5;
    otherPaths[6] = 2;
    otherPaths[7] = 4;
    otherPaths[8] = 3;
    ASSERT_EQ(otherPaths, d3.findShortestPaths(1, edgeWeightFunc));

    Digraph<std::string, int> d4;
    d4.addVertex(4, "Drake");
    d4.addVertex(1, "Meek Mill");
    d4.addVertex(3, "Kendrick Lamar");
    d4.addVertex(2, "Desiigner");
    std::map<int, int> finalPaths;
    finalPaths[1] = 1;
    finalPaths[2] = 2;
    finalPaths[3] = 3;
    finalPaths[4] = 4;
    ASSERT_EQ(finalPaths, d4.findShortestPaths(1, edgeWeightFunc));
}



