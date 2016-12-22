#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <string>

class OutofBoundsException : public std::exception
{
};

template <typename T>
class ArrayList
{
public:
    ArrayList();

    ArrayList(const ArrayList& a);

    ~ArrayList();

    ArrayList& operator=(const ArrayList& a);

    T& at(unsigned int index);
    const T& at(unsigned int index) const;

    void add(const T& t);

    unsigned int size() const;

    unsigned int capacity() const;


private:
    T* items;
    unsigned int sz;
    unsigned int cap;
};

namespace
{
    const unsigned int initialCapacity = 10;

    template <typename T>
    void arrayCopy(T* target, T* source, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            target[i] = source[i];
        }
    }
}

template <typename T>
ArrayList<T>::ArrayList()
    : items{nullptr}, sz{0}, cap{initialCapacity}
{
    //std::cout << "ArrayList::ArrayList()" << std::endl;
    try
    {
        items = new T[initialCapacity];
    }
    catch (...)
    {
        delete[] items;
        throw;
    }
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& a)
    : items{nullptr}, sz{a.sz}, cap{a.cap}
{
    //std::cout << "ArrayList::ArrayList(const ArrayList&)" << std::endl;
    try
    {
        items = new T[a.cap];
    }
    catch (...)
    {
        delete[] items;
        throw;
    }
    arrayCopy(items, a.items, sz);
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    //std::cout << "ArrayList::~ArrayList()" << std::endl;
    delete[] items;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& a)
{
    //std::cout << "ArrayList& ArrayList::operator=(const ArrayList&)" << std::endl;

    if (this != &a)
    {
        T* newItems = nullptr;
        try
        {
            newItems = new T[a.cap];
        }
        catch (...)
        {
            delete[] newItems;
            throw;
        }
        arrayCopy(newItems, a.items, a.sz);
        sz = a.sz;
        cap = a.cap;
        delete[] items;
        items = newItems;
    }

    return *this;
}

template <typename T>
T& ArrayList<T>::at(unsigned int index)
{
    if (index >= 0 && index < sz) 
    {
        return items[index];
    }
    else
    {
        throw OutofBoundsException{};
    }
}

template <typename T>
const T& ArrayList<T>::at(unsigned int index) const
{
    if (index >= 0 && index < sz)
    {
        return items[index];
    }
    else
    {
        throw OutofBoundsException{};
    }
}

template <typename T>
void ArrayList<T>::add(const T& s)
{
    if (sz == cap)
    {
        T* newItems = nullptr;
        int newCap = cap * 2 + 1;
        try
        {
            newItems = new T[newCap];
        }
        catch (...)
        {
            delete[] newItems;
            throw;
        }
        arrayCopy(newItems, items, sz);
        cap = newCap;
        delete[] items;
        items = newItems;
    }

    items[sz] = s;
    sz++;
}

template <typename T>
unsigned int ArrayList<T>::size() const
{
    return sz;
}

template <typename T>
unsigned int ArrayList<T>::capacity() const
{
    return cap;
}


#endif // ARRAYLIST_HPP

