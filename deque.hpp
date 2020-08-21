#ifndef DEQUE_H
#define DEQUE_H

#include "linkedlist.hpp"
#include "vector.hpp"
namespace STL{


template <typename T>
class Deque{
protected:
    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_value_type=const T;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_value_type=T&&;


    typedef Vector<Vector<T>> map_type;

public:

public:
    Deque()
    {

    }

    void insert(const_ref_type x)
    {

    }

public:
    iterator begin(){return start;}
    iterator end(){return finish;}
public:

    int buffer_size;
};

}
#endif // DEQUE_H
