#ifndef INITIALIZER_ARRAY_HPP
#define INITIALIZER_ARRAY_HPP

#include <iostream>
#include "iterator.hpp"
namespace STL{



template<typename T,T...args>
class initializer_array{
protected:
    using size_type=size_t;
    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_ptr_type=const T*;
    using const_ref_type=const T&;
    using right_ref_type=T&&;
public:

    struct iterator:public base_iterator<random_access_iterator_tag,value_type,size_type>{
        ptr_type index;
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

    using const_iterator         =typename STL::const_iterator<iterator>;
    using reverse_iterator       =typename STL::reverse_iterator<iterator>;
    using const_reverse_iterator =typename STL::const_iterator<reverse_iterator>;
public:
    initializer_array(){}

    iterator begin(){return array;}
    iterator end(){return array+size;}

    reverse_iterator rbegin(){return iterator(array+size-1);}
    reverse_iterator rend(){return iterator(array-1);}

    const_iterator cbegin(){return iterator(array);}
    const_iterator cend(){return iterator(array+size);}

    const_reverse_iterator crbegin(){return rbegin();}
    const_reverse_iterator crend(){return rend();}

    size_type length()const{return size;}
    bool isEmpty()const{return size;}

    const_ref_type front()const{return *begin();}
    const_ref_type back()const{return *(end()-1);}

    void fill(const_ref_type v)
    {for(size_type i=0;i<size;++i)array[i]=v;}

    ref_type operator[](size_type i){return array[i];}    
    ref_type at(size_type i){return array[i];}

private:
    static constexpr size_type size=sizeof...(args);
    value_type array[size]={args...};
};

template <int N,int...Indexes>
struct MakeIndexes:public MakeIndexes<N-1,N-1,Indexes...>{};

template <int...Indexes>
struct MakeIndexes<0,Indexes...>
{using type=initializer_array<int,Indexes...>;};

}
#endif // INITIALIZER_ARRAY_HPP
