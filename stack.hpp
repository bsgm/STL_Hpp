#ifndef STACK_H
#define STACK_H

#include "vector.hpp"
#include "iterator.hpp"
namespace STL{


template<typename T,typename Sequence=Vector<T>>
class Stack
{
protected:
    using value_type=T;
    using ref_type=T&;
    using ptr_type=T*;
    using const_ref_type=const T&;
    using const_ptr_type=const T*;
    using right_ref_type=T&&;

    using self_type=Stack<T>;
    using ref_self_type=Stack<T>&;
    using const_ref_self_type=const Stack<T>&;
    using right_ref_self_type=Stack<T>&&;

public:
    Stack(){}
    Stack(const_ref_self_type s)
    {
        array.operator =(s.array);
    }
    Stack(right_ref_self_type s)
    {
        array.operator =(std::move(s.array));
    }
    const_ref_self_type operator =(const_ref_self_type x)
    {
        array.operator =(x.array);
        return *this;
    }
    right_ref_self_type operator =(right_ref_self_type x)
    {
        array.operator =(std::move(x.array));
        return *this;
    }

public:

    void push(right_ref_type e){array.push_back(std::move(e));}
    void push(const_ref_type e){array.push_back(e);}
    value_type pop(){return array.pop_back();}
    const_ref_type top(){return array.back();}

    void empty(){array.empty();}
    bool isEmpty(){return array.isEmpty();}

    typename STL::iterator_traits<typename Sequence::iterator>::difference_type
    length(){return array.length();}

private:
    Sequence array;
};

}

#endif // STACK_H
