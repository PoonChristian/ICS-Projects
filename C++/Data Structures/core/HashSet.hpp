// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;

    // bucketCount() returns the number capacity or current bucket count
    // of the hash table
    unsigned int bucketCount() const;

    // loadFactor() returns the proportion of the size of the hash table
    // to its capacity or current bucket count. The load factor is checked
    // before adding an element into the hash table. If it is greater
    // than 0.8, then the hash table will be resized, and all the elements
    // will be rehashed into different buckets.
    double loadFactor() const;

private:
    struct Node
    {
        T key;
        Node* next;
    };
    HashFunction hashFunction;
    unsigned int currentBucketCount;
    unsigned int sz;
    Node** HashTable;

private:
    void copyAll(const HashSet& s);
    void destroyAll();
    unsigned int getBucket(unsigned int hashValue) const;
};

template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}, currentBucketCount{DEFAULT_CAPACITY},
    sz{0}, HashTable{new Node*[DEFAULT_CAPACITY]{nullptr}}
{
}


template <typename T>
HashSet<T>::~HashSet()
{
    destroyAll();
}

template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}, currentBucketCount{s.currentBucketCount},
    sz{s.sz}, HashTable{new Node*[s.currentBucketCount]{nullptr}}
{
    copyAll(s);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        destroyAll();
        HashTable = new Node*[currentBucketCount]{nullptr};
        copyAll(s);
        hashFunction = s.hashFunction;
        currentBucketCount = s.currentBucketCount;
        sz = s.sz;
    }
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    if (loadFactor() > 0.8)
    {
        unsigned int newBucketCount = currentBucketCount * 2 + 1;
        Node** newHashTable = new Node*[newBucketCount]{nullptr};
        for (int i = 0; i < currentBucketCount; ++i)
        {
            if (HashTable[i] != nullptr)
            {
                Node* head = HashTable[i];
                while (head != nullptr)
                {
                    unsigned int newBucket = hashFunction(head->key) % newBucketCount;
                    if (newHashTable[newBucket] == nullptr)
                    {
                        newHashTable[newBucket] = new Node{head->key, nullptr};
                        delete head;
                    }
                    else
                    {
                        Node* newHead = newHashTable[newBucket];
                        Node* newNext = new Node{head->key, nullptr};
                        while (newHead->next != nullptr)
                        {
                            newHead = newHead->next;
                        }
                        newHead->next = newNext;
                        delete head;
                    }
                    head = head->next;
                }
            }
        }
        currentBucketCount = newBucketCount;
        delete[] HashTable;
        HashTable = newHashTable;
    }
    if (contains(element))
    {
        return;
    }
    else
    {
        unsigned int bucket = getBucket(hashFunction(element));
        if (HashTable[bucket] == nullptr)
        {
            HashTable[bucket] = new Node{element, nullptr};
        }
        else
        {
            Node* next = HashTable[bucket];
            HashTable[bucket] = new Node{element, next};
        }
        sz++;
    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    unsigned int bucket = getBucket(hashFunction(element));
    Node* curr = HashTable[bucket];
    while (curr != nullptr)
    {
        if (curr->key == element)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return sz;
}


template <typename T>
unsigned int HashSet<T>::bucketCount() const
{
    return currentBucketCount;
}


template <typename T>
double HashSet<T>::loadFactor() const
{
    return sz / static_cast<double>(currentBucketCount);
}


template <typename T>
unsigned int HashSet<T>::getBucket(unsigned int hashValue) const
{
    return hashValue % currentBucketCount;
}


template <typename T>
void HashSet<T>::copyAll(const HashSet& s)
{
    for (int i = 0; i < currentBucketCount; ++i)
    {
        if (s.HashTable[i] != nullptr)
        {
            Node* sourceHead = s.HashTable[i];
            while (sourceHead != nullptr)
            {
                if (HashTable[i] == nullptr)
                {
                    HashTable[i] = new Node{sourceHead->key, nullptr};
                }
                else
                {
                    Node* newHead = HashTable[i];
                    Node* newNext = new Node{sourceHead->key, nullptr};
                    while (newHead->next != nullptr)
                    {
                        newHead = newHead->next;
                    }
                    newHead->next = newNext;
                }
                sourceHead = sourceHead->next;
            }
        }
    }
}


template <typename T>
void HashSet<T>::destroyAll()
{
    for (int i = 0; i < currentBucketCount; ++i)
    {
        Node* curr = HashTable[i];
        while (curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] HashTable;
}



#endif // HASHSET_HPP

