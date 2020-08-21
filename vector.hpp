#ifndef VECTOR_H
#define VECTOR_H

#include "algorithms.hpp"
#include "iterator.hpp"
#include <iostream>

namespace STL{
template<typename T,typename Distance=int>
class Vector{
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

    using reverse_iterator      =typename STL::reverse_iterator<iterator>;
    using const_iterator        =typename STL::const_iterator<iterator>;
    using const_reverse_iterator=typename STL::const_iterator<reverse_iterator>;

private:

    template<typename... Args>
    void argsInit(size_type i,const_ref_type value,const Args&... args)
    {
        argsInit(i+1,args...);
        *(start+i)=value;
    }
    template<typename... Args>
    void argsInit(size_type i,right_ref_type value,Args&&... args)
    {
        argsInit(i+1,std::move(args)...);
        *(start+i)=std::move(value);
    }
    void argsInit(size_type i)
    {
        this->start.index=new value_type[i];
        this->end_of_storage.index=&this->start.index[i];
        this->finish.index=&this->start.index[i];
    }

public: //constructor ~ destructor
    Vector()
    {
        this->start.index=nullptr;
        this->finish.index=nullptr;
        this->end_of_storage.index=nullptr;
    }
    Vector(size_type size)
    {
        this->start.index=new value_type[size];
        this->end_of_storage.index=start.index+size;
        this->finish.index=this->start.index;
    }

    Vector(Vector<value_type>&&  v)
    {
        end_of_storage=v.end_of_storage;
        start=v.start;
        finish=v.finish;
        v.start.index=nullptr;
        v.finish.index=nullptr;
        v.end_of_storage.index=nullptr;
    }
    Vector(const Vector<value_type>&  v)
    {
        this->start.index=new value_type[v.end_of_storage-v.start];
        this->end_of_storage.index=start.index+(v.end_of_storage-v.start);
        this->finish.index=start.index+(v.finish-v.start);
        copy(v.begin(),v.begin()+length(),begin());
    }

    const Vector<value_type>& operator=(const Vector<value_type>& v)
    {
        clear();
        this->start.index=new value_type[v.end_of_storage-v.start];
        this->end_of_storage.index=start.index+(v.end_of_storage-v.start);
        this->finish.index=start.index+(v.finish-v.start);
        copy(v.begin(),v.begin()+length(),begin());
        return *this;
    }
    const Vector<value_type>& operator=(Vector<value_type>&& v)
    {
        clear();
        end_of_storage=v.end_of_storage;
        start=v.start;
        finish=v.finish;
        v.start.index=nullptr;
        v.finish.index=nullptr;
        v.end_of_storage.index=nullptr;

        return *this;
    }

    template <typename InputIterator>
    Vector(InputIterator first,InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n=distance(first,last);
        this->start.index=new value_type[n];
        this->end_of_storage.index=start.index+n;
        this->finish.index=this->start.index+n;

        STL::copy_n(first,last,start);
    }

    template <typename ...Args>
    Vector(Args...args)
    {
        argsInit(0,args...);
    }


    ~Vector(){clear();}

public: //const function

    const_ref_type at(size_type i)const{return *(start.index+i);}
    ref_type operator[](size_type i){return *(start+i);}
    size_type length()const{return finish-start;}
    size_type max_size(){return end_of_storage-start;}
    iterator storage_end()const{return end_of_storage;}
    iterator begin()const{return start;}
    iterator end()const{return finish;}

    reverse_iterator rbegin()const{return finish-1;}
    reverse_iterator rend()const{return start-1;}

    const_iterator cbegin()const{return start;}
    const_iterator cend()const{return finish;}

    const_reverse_iterator crbegin()const{return rbegin();}
    const_reverse_iterator crend()const{return rend();}

    bool isEmpty(){return finish-start;}
    bool isfull(){return end_of_storage==finish;}
    const_ref_type back(){return *(start+length()-1);}
    const_ref_type top() {return *start;}

public: //insert
    void push_back(right_ref_type x)
    {
        if(finish!=end_of_storage)
        {
            *finish=x;
            finish++;
        }
        else
        {
            resize(length()+1);
            push_back(x);
        }
    }
    void push_back(const_ref_type x)
    {
        if(finish!=end_of_storage)
        {
            *finish=x;
            finish++;
        }
        else
        {
            resize(length()+1);
            push_back(x);
        }
    }

    iterator insert(iterator position,const_ref_type x)
    {
        return insert(position-start,x);
    }
    iterator insert(size_type position,const_ref_type x)
    {
        if(finish!=end_of_storage)
        {
            if(position==length())
                push_back(x);
            else {
                finish++;
                STL::copy(start+position,finish-1,start+position+1);
                *(start+position)=x;
                return start+position;
            }
        }
        else
        {
            resize(length()+1);
            return insert(position,x);
        }
    }
public: //remove

    void clear()
    {
        if(start.index)
        {
            delete[] start.index;
            start.index=nullptr;
            finish.index=nullptr;
            end_of_storage.index=nullptr;
        }
    }
    void empty()  {finish=start;}
    void erase(iterator position)
    {
        STL::copy(position+1,finish,position);
        --finish;
    }
    void erase(iterator first,iterator last)
    {
        STL::copy(last,finish,first);
        finish=finish-(last-first);
    }
    void erase(size_type first,size_type last)
    {
        erase(start+first,start+last);
    }

    value_type pop_back()
    {
        if(start!=finish)
        {
            iterator t=finish-1;
            finish--;
            return *t;
        }
        else
        {
            return *start;
        }
    }
    void erase(size_type index)
    {
        erase(start+index);
    }
    void resize(size_type n,const_ref_type v)
    {
        if(n<=end_of_storage-start)
        {
            finish=start+n;
            for(iterator i=start;i!=finish;++i) *i=v;
        }
        else
        {
            clear();

            this->start.index=new T[n];
            this->end_of_storage.index=start.index+n;
            this->finish.index=start.index+n;

            for(iterator i=start;i!=finish;++i) *i=v;

        }
    }


    void resize(size_type n)
    {
        if(n<=end_of_storage-start)
            finish=start+n;
        else
        {
            iterator t_start=start;
            iterator t_finish=finish;

            this->start.index=new T[n];
            this->end_of_storage.index=start.index+n;
            this->finish.index=start.index+n;

            STL::copy(t_start,t_finish,begin());
            delete[] t_start.index;
        }
    }
    void swap(Vector<value_type,size_type>&& v)
    {
        iterator t_start=v.start;
        iterator t_finish=v.finish;
        iterator t_end_of_storage=v.end_of_storage;
        v.start=start;
        v.finish=finish;
        v.end_of_storage=end_of_storage;
        start=t_start;
        finish=t_finish;
        end_of_storage=t_end_of_storage;
    }


private:   //data
    iterator start;
    iterator finish;
    iterator end_of_storage;
};

}
#endif // VECTOR_H
