// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;
    
private:
    struct Node
    {
        T key;
        Node* left;
        Node* right;
    };

    Node* root;
    unsigned int sz;

private:
    void copyTree(Node*& newCurr, Node* sourceCurr);
    void destroyTree(Node* curr);
    void addLeaf(const T& element, Node*& curr);
    bool treeContainsElement(const T& element, Node* curr) const;
};


template <typename T>
BSTSet<T>::BSTSet()
    : root{nullptr}, sz{0}
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    destroyTree(root);
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{
    copyTree(root, s.root);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if (this != &s)
    {
        destroyTree(root);
        root = nullptr;
        copyTree(root, s.root);
        sz = s.sz;
    }
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    addLeaf(element, root);
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    return treeContainsElement(element, root);
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    return sz;
}


template <typename T>
void BSTSet<T>::copyTree(Node*& newCurr, Node* sourceCurr)
{
    if (sourceCurr == nullptr)
    {
        newCurr = nullptr; 
    }
    else
    {
        newCurr = new Node{sourceCurr->key, sourceCurr->left, sourceCurr->right};
        copyTree(newCurr->left, sourceCurr->left);
        copyTree(newCurr->right, sourceCurr->right);
    }
    
}


template <typename T>
void BSTSet<T>::destroyTree(Node* curr)
{
    if (curr != nullptr)
    {
        destroyTree(curr->left);
        destroyTree(curr->right);
        delete curr;
    }
}


template <typename T>
void BSTSet<T>::addLeaf(const T& element, Node*& curr)
{
    if (curr == nullptr)
    {
        curr = new Node{element, nullptr, nullptr};
        sz++;
    }
    else if (element < curr->key)
    {
        addLeaf(element, curr->left);
    }
    else if (element > curr->key)
    {
        addLeaf(element, curr->right);
    }
    else
    {
        return;
    }
}


template <typename T>
bool BSTSet<T>::treeContainsElement(const T& element, Node* curr) const
{
    if (curr == nullptr)
    {
        return false;
    }
    else if (element < curr->key)
    {
        return treeContainsElement(element, curr->left);
    }
    else if (element > curr->key)
    {
        return treeContainsElement(element, curr->right);
    }
    else
    {
        return true;
    }
}



#endif // BSTSET_HPP

