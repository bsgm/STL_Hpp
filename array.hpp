#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include "iterator.hpp"

namespace STL{

template <typename T,size_t N>
class Array
{
protected:

    using size_type=size_t;
    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_ptr_type=const T*;
    using const_ref_type=const T&;
    using right_ref_type=T&&;

    using self_type=Array<T,N>;
    using ref_self_type=Array<T,N>&;
    using const_ref_self_type=const Array<T,N>&;

public:
    struct iterator:public base_iterator<random_access_iterator_tag,value_type,size_type>
    {
        ptr_type  index;

        iterator():index(nullptr){}
        iterator(ptr_type ptr):index(ptr){}

        bool operator>(const iterator & i)const{return (index-i.index)>0;}
        bool operator<(const iterator & i)const{return (index-i.index)<0;}
        bool operator<=(const iterator & i)const{return (index-i.index)<=0;}
        bool operator>=(const iterator & i)const{return (index-i.index)>=0;}
        bool operator==(const iterator & i)const{return !(index-i.index);}
        bool operator!=(const iterator& i)const{return (index-i.index);}

        ref_type operator*(){return *index;}
        ptr_type operator->(){return index;}

        iterator  operator=(const iterator& i)
        {
            index=i.index;
            return *this;
        }
        iterator& operator++()
        {
            index=index+1;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp = *this;
            index=index+1;
            return temp;
        }
        iterator& operator--()
        {
            index=index-1;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp = *this;
            index=index-1;
            return temp;
        }
        iterator operator-(size_type i)const
        {
            iterator t;
            t.index=index-i;
            return t;
        }
        iterator operator+(size_type i)const
        {
            iterator t;
            t.index=index+i;
            return t;
        }
        size_type operator -(const iterator & i)const{return index-i.index;}

    };
    using reverse_iterator       =typename STL::reverse_iterator<iterator>;
    using const_iterator         =typename STL::const_iterator<iterator>;
    using const_reverse_iterator =typename STL::const_iterator<reverse_iterator>;
private:
    template <typename ...Args>
    void initialize_data(size_type i,T v,Args...args)
    {
        if(i<N)
        {
            data[i]=v;
            initialize_data(i+1,args...);
        }
    }
    void initialize_data(size_type){}

public:
    Array(){}

    Array(const_ref_self_type array)
    {
        for(size_type i=0;i<N;++i)data[i]=array.data[i];
    }


    template <typename ...Args>
    Array(Args...args)
    {
        initialize_data(0,args...);
    }

    template <typename InputIterator>
    Array(InputIterator first,InputIterator last)
    {
        for(size_type i=0;first!=last&&i<N;++first,++i)
            data[i]=*first;
    }

    iterator begin(){return iterator(data);}
    iterator end(){return iterator(data+N);}

    reverse_iterator rbegin(){return iterator(data+N-1);}
    reverse_iterator rend(){return iterator(data-1);}

    const_iterator cbegin(){return iterator(data);}
    const_iterator cend(){return iterator(data+N);}

    const_reverse_iterator crbegin(){return rbegin();}
    const_reverse_iterator crend(){return rend();}

    ref_type operator [](size_type i){return data[i];}
    ref_type at(size_type i){return data[i];}
    ref_type front(){return *begin();}
    ref_type back(){return *rbegin();}
    size_type length()const{return N;}
    bool isEmpty()const{return N;}
    void fill(const_ref_type v)
    {
        for(size_type i=0;i<N;++i)
            data[i]=v;
    }

    ref_self_type operator <<(const_ref_type v){
        index=0;
        data[index]=v;
        ++index;
        return *this;
    }
    ref_self_type operator ,(const_ref_type v){
        data[index]=v;
        ++index;
        return *this;
    }

private:
    T data[N];
    size_type index;
};
}

#endif // ARRAY_HPP
