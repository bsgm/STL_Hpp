#ifndef LINKEDARRAY_HPP
#define LINKEDARRAY_HPP

#include "vector.hpp"

namespace STL{

template <typename T,typename Distance=int>
class LinkedArray
{
protected:
    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_value_type=const T;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_ref_type=T&&;

    using size_type=Distance;

public:
    struct iterator{
        typename Vector<T*>::iterator index;
        LinkedArray * LA;
        iterator():index(nullptr),LA(nullptr){}
        iterator(typename Vector<T*>::iterator ptr,LinkedArray * la):index(ptr),LA(la){
            while(index!=LA->_end()&&!*index){++index;}
        }

        bool operator>(const iterator & i)const{return (index-i.index)>0;}
        bool operator<(const iterator & i)const{return (index-i.index)<0;}
        bool operator<=(const iterator & i)const{return (index-i.index)<=0;}
        bool operator>=(const iterator & i)const{return (index-i.index)>=0;}
        bool operator==(const iterator & i)const{return !(index-i.index);}
        bool operator!=(const iterator& i)const{return (index-i.index);}

        ref_type operator*(){return **index;}
        ptr_type operator->(){return *index;}

        iterator  operator=(const iterator& i)
        {
            index=i.index;
            LA=i.LA;
            return *this;
        }
        iterator& operator++()
        {
            do{++index;}while(index!=LA->_end()&&!*index);
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp = *this;
            ++index;
            return tmp;
        }
        iterator& operator--()
        {
            do{--index;}while(index!=LA->_begin()&&!*index);
            return *this;
        }
        iterator operator--(int)
        {
            iterator tmp = *this;
            --index;
            return tmp;
        }
    };
private:
    typename Vector<T*>::iterator _begin()const{return data.begin();}
    typename Vector<T*>::iterator _end()const{return data.end();}
public:
    LinkedArray():size(0){}
    LinkedArray(size_type n):size(0){
        data.resize(n,nullptr);
    }
    template<typename InputIterator>
    LinkedArray(InputIterator first,InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n=STL::distance(first,last);
        data.resize(n,nullptr);

    }

    ~LinkedArray()
    {
        for(size_type i=0;i<data.length();++i)
            if(data[i]) delete data[i];
    }


    iterator begin() {return iterator(data.begin(),this);}
    iterator end() {return iterator(data.end(),this);}

    ref_type operator [](size_type i)
    {
        if(!data[i])
        {
            data[i]=new value_type;
            ++size;
        }
        return *data[i];
    }

    size_type length()const{return size;}

private:
    Vector<T*> data;
    size_type size;
};


}


#endif // LINKEDARRAY_HPP
