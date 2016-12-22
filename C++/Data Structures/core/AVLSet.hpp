// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    // getHeight() returns the height of the entire tree by calling the
    // private height() function on the root of the tree.
    int getHeight() const;

    // getBalanceFactor() returns the balanceFactor of the root of the tree
    // by calling the private balanceFactor() function to return the root's
    // left subtree height minus its right subtree height.
    int getBalanceFactor() const;

private:
    struct Node
    {
        T key;
        Node* left;
        Node* right;
        int height;
    };

    Node* root;
    unsigned int sz;

private:
    void copyTree(Node*& newCurr, Node* sourceCurr);
    void destroyTree(Node* curr);
    void addLeaf(const T& element, Node*& curr);
    bool treeContainsElement(const T& element, Node* curr) const;
    int height(Node* curr) const;
    int balanceFactor(Node* curr) const;
    void rotateLL(Node*& topNode);
    void rotateRR(Node*& topNode);
    void rotateLR(Node*& topNode);
    void rotateRL(Node*& topNode);

};


template <typename T>
AVLSet<T>::AVLSet()
    : root{nullptr}, sz{0}
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    destroyTree(root);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    copyTree(root, s.root);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    addLeaf(element, root);
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return treeContainsElement(element, root);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return sz;
}


template <typename T>
int AVLSet<T>::getHeight() const
{
    return height(root);
}


template <typename T>
int AVLSet<T>::getBalanceFactor() const
{
    return balanceFactor(root);
}


template <typename T>
void AVLSet<T>::copyTree(Node*& newCurr, Node* sourceCurr)
{
    if (sourceCurr == nullptr)
    {
        newCurr = nullptr;
    }
    else
    {
        newCurr = new Node{sourceCurr->key, sourceCurr->left, sourceCurr->right, sourceCurr->height};
        copyTree(newCurr->left, sourceCurr->left);
        copyTree(newCurr->right, sourceCurr->right);
    }
}


template <typename T>
void AVLSet<T>::destroyTree(Node* curr)
{
    if (curr != nullptr)
    {
        destroyTree(curr->left);
        destroyTree(curr->right);
        delete curr;
    }
}


template <typename T>
void AVLSet<T>::addLeaf(const T& element, Node*& curr)
{
    if (curr == nullptr)
    {
        curr = new Node{element, nullptr, nullptr, 0};
        sz++;
    }
    else if (element < curr->key)
    {
        addLeaf(element, curr->left);
        int currentBalanceFactor = balanceFactor(curr);
        if (currentBalanceFactor < -1 || currentBalanceFactor > 1)
        {
            //std::cout << "Balance Factor = " << currentBalanceFactor << std::endl;
            //std::cout << "Current key = " << curr->key << std::endl;
            //std::cout << "Current->left->key = " << curr->left->key << std::endl;
            //std::cout << "Element inserted = " << element << std::endl;
            if (element < curr->left->key)
            {
                //std::cout << "Performing an LL rotation" << std::endl;
                rotateLL(curr);
            }
            else 
            {
                //std::cout << "Performing an LR rotation" << std::endl;
                rotateLR(curr);
            }
        }
    }
    else if (element > curr->key)
    {
        addLeaf(element, curr->right);
        int currentBalanceFactor = balanceFactor(curr);
        if (currentBalanceFactor < -1 || currentBalanceFactor > 1)
        {
            //std::cout << "Balance Factor = " << currentBalanceFactor << std::endl;
            //std::cout << "Current key = " << curr->key << std::endl;
            //std::cout << "Current->right->key = " << curr->right->key << std::endl;
            //std::cout << "Element inserted = " << element << std::endl;
            if (element > curr->right->key)
            {
                //std::cout << "Performing an RR rotation" << std::endl;
                rotateRR(curr);
            }
            else
            {
                //std::cout << "Performing an RL rotation" << std::endl;
                rotateRL(curr);
            }
        }
    }
    else
    {
        return;
    }
    //std::cout << std::endl;
    curr->height = std::max(height(curr->left), height(curr->right)) + 1;
}


template <typename T>
bool AVLSet<T>::treeContainsElement(const T& element, Node* curr) const
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


template <typename T>
int AVLSet<T>::height(Node* curr) const
{
    if (curr == nullptr)
    {
        return -1;
    }
    return curr->height;
}


template <typename T>
int AVLSet<T>::balanceFactor(Node* curr) const
{
    return height(curr->left) - height(curr->right);
}


template <typename T>
void AVLSet<T>::rotateLL(Node*& topNode)
{
    topNode->height -= 1;
    Node* temp = topNode->left;
    topNode->left = temp->right;
    temp->right = topNode;
    topNode = temp;
}


template <typename T>
void AVLSet<T>::rotateRR(Node*& topNode)
{
    topNode->height -= 1;
    Node* temp = topNode->right;
    topNode->right = temp->left;
    temp->left = topNode;
    topNode = temp;
}


template <typename T>
void AVLSet<T>::rotateLR(Node*& topNode)
{
    rotateRR(topNode->left);
    rotateLL(topNode);
}


template <typename T>
void AVLSet<T>::rotateRL(Node*& topNode)
{
    rotateLL(topNode->right);
    rotateRR(topNode);
}



#endif // AVLSET_HPP

