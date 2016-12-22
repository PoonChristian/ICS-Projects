// Digraph.hpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <limits>
#include <queue>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException
{
public:
    DigraphException(const std::string& reason): reason_{reason} { }

    std::string reason() const { return reason_; }

private:
    std::string reason_;
};



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a template
// struct.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a template struct.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph();

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;

private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> allVertices;
    int numberOfVertices;
    int numberOfEdges;

    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    void depthFirstTraversalRecursive(int vertex, std::map<int, bool>& visited) const;
    void printDigraph() const;
};



// You'll need to define the member functions of your Digraph class
// template here.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
    : numberOfVertices{0}, numberOfEdges{0}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
    : allVertices{d.allVertices},
    numberOfVertices{d.numberOfVertices},
    numberOfEdges{d.numberOfEdges}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph()
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if (this != &d)
    {
        allVertices = d.allVertices;
        numberOfVertices = d.numberOfVertices;
        numberOfEdges = d.numberOfEdges;
    }
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> vertices;

    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        vertices.push_back(i->first);
    }

    return vertices;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> edges;

    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        for (auto j = i->second.edges.begin(); j != i->second.edges.end(); ++j)
        {
            edges.push_back(std::make_pair(j->fromVertex, j->toVertex));
        }
    }

    return edges;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    std::vector<std::pair<int, int>> edgesFromVertex;

    if (allVertices.find(vertex) == allVertices.end())
    {
        throw DigraphException("Vertex does not exist");
    }
    else
    {
        auto i = allVertices.find(vertex);
        for (auto j = i->second.edges.begin(); j != i->second.edges.end(); ++j)
        {
            edgesFromVertex.push_back(std::make_pair(j->fromVertex, j->toVertex));
        }
    }

    return edgesFromVertex;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    if (allVertices.find(vertex) == allVertices.end())
    {
        throw DigraphException{"Vertex does not exist"};
    }
    else
    {
        return allVertices.at(vertex).vinfo;
    }
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if (allVertices.find(fromVertex) == allVertices.end() || allVertices.find(toVertex) == allVertices.end())
    {
        throw DigraphException("A vertex does not exist");
    }
    else
    {
        for (auto i = allVertices.at(fromVertex).edges.begin(); i != allVertices.at(fromVertex).edges.end(); ++i)
        {
            if (i->toVertex == toVertex)
            {
                return i->einfo;
            }
        }
        throw DigraphException("The edge does not exist");
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if (allVertices.find(vertex) != allVertices.end())
    {
        throw DigraphException{"Vertex already exists"};
    }
    else
    {
        allVertices[vertex] = DigraphVertex<VertexInfo, EdgeInfo>{vinfo};
        numberOfVertices++;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if (allVertices.find(fromVertex) == allVertices.end() || allVertices.find(toVertex) == allVertices.end())
    {
        throw DigraphException("A vertex does not exist");
    }
    else
    {
        for (auto i = allVertices[fromVertex].edges.begin(); i != allVertices[fromVertex].edges.end(); ++i)
        {
            if (i->toVertex == toVertex)
            {
                throw DigraphException("The edge already exists");
            }
        }
        DigraphEdge<EdgeInfo> newEdge{fromVertex, toVertex, einfo};
        allVertices[fromVertex].edges.push_back(newEdge);
        numberOfEdges++;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if (allVertices.find(vertex) == allVertices.end())
    {
        throw DigraphException{"Vertex does not exist"};
    }
    else
    {
        allVertices.erase(vertex);
        numberOfVertices--;
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if (allVertices.find(fromVertex) == allVertices.end() || allVertices.find(toVertex) == allVertices.end())
    {
        throw DigraphException("A vertex does not exist");
    }
    else
    {
        for (auto i = allVertices[fromVertex].edges.begin(); i != allVertices[fromVertex].edges.end(); ++i)
        {
            if (i->toVertex == toVertex)
            {
                allVertices[fromVertex].edges.erase(i);
                numberOfEdges--;
                return;
            }
        }
        throw DigraphException("The edge does not exist");
    }
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const
{
    return numberOfVertices;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const
{
    return numberOfEdges;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    if (allVertices.find(vertex) == allVertices.end())
    {
        throw DigraphException("Vertex does not exist");
    }
    else
    {
        return allVertices.at(vertex).edges.size();
    }
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    std::map<int, bool> visited;

    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        visited[i->first] = false;
    }

    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        depthFirstTraversalRecursive(i->first, visited);
        for (std::map<int, bool>::iterator j = visited.begin(); j != visited.end(); ++j)
        {
            if (visited[j->first] == false)
            {
                return false;
            }
            visited[j->first] = false;
        }
    }

    return true;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    std::map<int, bool> knownVertices;
    std::map<int, double> distances;
    std::map<int, int> predecessors;

    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        knownVertices[i->first] = false;
        predecessors[i->first] = i->first;
        if (i->first == startVertex)
        {
            distances[i->first] = 0;
        }
        else
        {
            distances[i->first] = std::numeric_limits<double>::infinity();
        }
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
    queue.push(std::make_pair(distances[startVertex], startVertex));

    while (!queue.empty())
    {
        std::pair<int, int> v = queue.top();
        queue.pop();
        if (knownVertices[v.second] == false)
        {
            for (auto i = allVertices.at(v.second).edges.begin(); i != allVertices.at(v.second).edges.end(); ++i)
            {
                if (distances[i->toVertex] > distances[v.second] + edgeWeightFunc(i->einfo))
                {
                    distances[i->toVertex] = distances[v.second] + edgeWeightFunc(i->einfo);
                    predecessors[i->toVertex] = v.second;
                    queue.push(std::make_pair(distances[i->toVertex], i->toVertex));
                }
            }
        }
    }

    return predecessors;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::depthFirstTraversalRecursive(int vertex, std::map<int, bool>& visited) const
{
    visited[vertex] = true;
    for (auto i = allVertices.at(vertex).edges.begin(); i != allVertices.at(vertex).edges.end(); ++i)
    {
        if (visited[i->toVertex] == false)
        {
            depthFirstTraversalRecursive(i->toVertex, visited);
        }
    }
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::printDigraph() const
{
    for (auto i = allVertices.begin(); i != allVertices.end(); ++i)
    {
        std::cout << "Vertex #" << i->first << ", Vertex Info = " << i->second.vinfo << std::endl;
        for (auto j = i->second.edges.begin(); j != i->second.edges.end(); ++j)
        {
            std::cout << "\tfromVertex = " << j->fromVertex << std::endl;
            std::cout << "\ttoVertex = " << j->toVertex << std::endl;
            std::cout << "\tedgeInfo = " << j->einfo << std::endl;
            std::cout << std::endl;
        }
    }
}



#endif // DIGRAPH_HPP

