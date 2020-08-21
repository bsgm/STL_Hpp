#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>
#include "basicmeta.hpp"

namespace STL{

template<typename...Args>class Tuple;


template<typename...Args>
Tuple<Args...> make_tuple(Args...args)
{
    return Tuple<Args...>(std::move(args)...);
}

//partial speclialization
template<typename T,typename...Args>
class Tuple<T,Args...>
{
protected: //define

    using value_type=T;
    using ref_type=T&;
    using ptr_type=T*;
    using const_ref_type=const T&;
    using const_ptr_type=const T*;
    using right_ref_type=T&&;

    using self_type=Tuple<T,Args...>;
    using const_ref_self_type=const Tuple<T,Args...>&;
    using right_ref_self_type=Tuple<T,Args...>&&;

    using next_self_type=Tuple<Args...>;
    using const_ref_next_self_type=const Tuple<Args...>&;


public:

    void _ostream_tuple(std::ostream& out)const
    {
        out<<value<<",";
        child_tuple._ostream_tuple(out);
    }

    template<typename T1,typename T2>
    void _read_one(int i, T1 &v1 ,const T2&)const
    {
        child_tuple._read_one(i-1,v1,child_tuple.first_element());
    }
    void _read_one(int i, T &v1,const T &)const
    {
        if(i==0)
            v1=value;
        else
            child_tuple._read_one(i-1,v1,child_tuple.first_element());
    }
    template<typename T1,typename T2>
    void _write_one(int i, const T1 &v ,const T2&)
    {
        child_tuple._write_one(i-1,v,child_tuple.first_element());
    }
    void _write_one(int i, const T &v,const T &)
    {
        if(i==0)
            value=v;
        else
            child_tuple._write_one(i-1,v,child_tuple.first_element());
    }

public: //constructor ~ destructor
    Tuple(){}

    Tuple(const ref_type v,const Args&...args):
        value(v),
        child_tuple(args...){}

    Tuple(right_ref_type v,Args&&...args):
        value(v),
        child_tuple(std::move(args)...){}

    Tuple(const_ref_self_type t):
        value(t.value),
        child_tuple(t.child_tuple){}
    Tuple(right_ref_self_type t):
        value(std::move(t.value)),
        child_tuple(std::move(t.child_tuple)){}

public:  //const function
    int length()const{return Length<T,Args...>::size;}
    const_ref_type first_element()const{return value;}
    const_ref_next_self_type residue()const{return child_tuple;}


public: // operator

    const_ref_self_type operator =(const_ref_self_type x)
    {
        this->value=x.value;
        this->child_tuple.operator =(x.child_tuple);
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type x)
    {
        this->value=x.value;
        this->child_tuple.operator =(std::move(x.child_tuple));
        return *this;
    }

    friend std::ostream &  operator <<
    (std::ostream& out,const_ref_self_type tuple)
    {
        out<<"<";
        tuple._ostream_tuple(out);
        return out;
    }

public:  //read write
    void write(const_ref_type v,const Args&...args)
    {
        value=v;
        child_tuple.write(args...);
    }
    void write(right_ref_type v,Args&&...args)
    {
        value=v;
        child_tuple.write(std::move(args)...);
    }
    template<typename Type>
    void write_one(int i, const Type &v)
    {
        _write_one(i,v,value);
    }
    void read(ref_type v,Args&...args)const
    {
        v=value;
        child_tuple.read(args...);
    }
    template<typename Type>
    void read_one(int i, Type &v)const
    {
        _read_one(i,v ,value);
    }

    template<int N>
    const typename  GetType<N,T,Args...>::type
    element()const
    {
        typename  GetType<N,T,Args...>::type v;
        read_one(N,v);
        return v;
    }
    template<int N>
    void set_element(const typename  GetType<N,T,Args...>::type& v)
    {
        write_one(N,v);
    }

protected: //data
    value_type value;
    next_self_type child_tuple;
};

//Conditions of suspension
template<typename T>
class Tuple<T>
{
protected: //define

    using value_type=T;
    using ref_type=T&;
    using ptr_type=T*;
    using const_ref_type=const T&;
    using const_ptr_type=const T*;
    using right_ref_type=T&&;

    using self_type=Tuple<T>;
    using const_ref_self_type=const Tuple<T>&;
    using right_ref_self_type=Tuple<T>&&;

public:

    void _ostream_tuple(std::ostream& out)const{out<<value<<">";}

    template<typename T1,typename T2>
    void _read_one(int, T1 & ,const T2&)const{}
    void _read_one(int i, T &v,const T &)const{if(i==0)v=value;}
    template<typename T1,typename T2>
    void _write_one(int, const T1 & ,const T2&){}
    void _write_one(int i, const T &v,const T &){if(i==0)value=v;}

public: //constructor ~ destructor
    Tuple(){}
    Tuple(const_ref_type v):value(v){}
    Tuple(right_ref_type v):value(v){}
    Tuple(const_ref_self_type t):
        value(t.value){}
    Tuple(right_ref_self_type t):
        value(std::move(t.value)){}

public:  //const function
    int length()const{return Length<T>::size;}
    const_ref_type first_element()const{return value;}
    const_ref_self_type operator =(const_ref_self_type x)
    {
        this->value=x.value;
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type x)
    {
        this->value=x.value;
        return *this;
    }

    friend std::ostream &  operator <<
    (std::ostream& out,const_ref_self_type tuple)
    {
        out<<"<"<<tuple.first_element()<<">";
        return out;
    }

public: //read write
    template<typename Type>
    void write_one(int i, const Type &v)
    {
        _write_one(i,v ,value);
    }
    void write(const_ref_type v)
    {
        value=v;
    }
    void write(right_ref_type v)
    {
        value=v;
    }
    template<typename Type>
    void read_one(int i, Type &v1)const
    {
        _read_one(i,v1 ,value);
    }
    void read(ref_type v)const
    {
        v=value;
    }

protected: //data
    value_type value;
};

}

#endif // TUPLE_H
