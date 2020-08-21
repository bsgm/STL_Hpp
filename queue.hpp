#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.hpp"
#include "iterator.hpp"
namespace STL{



template<typename T,typename Sequence=LinkedList<T>>
class Queue
{
protected:
    using value_type=T;
    using ref_type=T&;
    using ptr_type=T*;
    using const_ref_type=const T&;
    using const_ptr_type=const T*;
    using right_ref_type=T&&;

    using self_type=Queue<T>;
    using ref_self_type=Queue<T>&;
    using const_ref_self_type=const Queue<T>&;
    using right_ref_self_type=Queue<T>&&;

public:
    Queue(){}
    Queue(const_ref_self_type x){list.operator =(x.list);}
    Queue(right_ref_self_type x){list.operator =(std::move(x.list));}
    const_ref_self_type operator =(const_ref_self_type x)
    {
        list.operator =(x.list);
        return *this;
    }
    right_ref_self_type operator =(right_ref_self_type x)
    {
        list.operator =(std::move(x.list));
        return *this;
    }

public:
    void push(const_ref_type x){list.push_back(x);}
    void push(right_ref_type x){list.push_back(std::move(x));}
    value_type pop(){return list.pop_front();}
    const_ref_type front(){return list.front();}
    void empty(){list.empty();}
public:
    typename STL::iterator_traits<typename Sequence::iterator>::difference_type
    length(){return list.length();}
    bool isEmpty(){return list.isEmpty();}

private:
    Sequence list;
};


}

#endif // QUEUE_H
