#ifndef PAIR_H
#define PAIR_H

#include <iostream>

namespace STL{

template<typename Arg1,typename Arg2>class Pair;


template <typename pair_type>
class get_first{
public:
    const typename pair_type::first_type&
    operator ()(const pair_type& pair)
    {return pair.first_value;}
};
template <typename pair_type>
class get_second{
public:
    const typename pair_type::second_type&
    operator ()(const pair_type& pair)
    {return pair.second_value;}
};

template <typename T1,typename T2>
Pair<T1,T2> make_pair(T1 v1,T2 v2)
{
    return Pair<T1,T2>(v1,v2);
}


template<typename CMP>
class PairCmpFirst{
public:
    PairCmpFirst(){}
    PairCmpFirst(const CMP& c):cmp(c){}

    template <typename T>
    bool operator ()(const T& x,const T& y)
    {
        return cmp(x.first_value,y.first_value);
    }
    CMP cmp;
};
template<typename CMP>
class PairCmpSecond{
public:
    PairCmpSecond(){}
    PairCmpSecond(const CMP& c):cmp(c){}
    template <typename T>
    bool operator ()(const T& x,const T& y)
    {
        return cmp(x.second_value,y.second_value);
    }
    CMP cmp;
};

template<typename Arg1,typename Arg2>
class Pair{
public:
    using first_type=Arg1;
    using second_type=Arg2;

public:
    Pair(){}
    Pair(const first_type& arg1,const second_type& arg2):
        first_value(arg1),
        second_value(arg2){}

    Pair(first_type&& arg1,second_type&& arg2):
        first_value(std::move(arg1)),
        second_value(std::move(arg2)){}

    Pair(const Pair<first_type,second_type>& pair):
        first_value(pair.first_value),
        second_value(pair.second_value){}

    Pair(Pair<first_type, second_type>&& pair):
        first_value(std::move(pair.first_value)),
        second_value(std::move(pair.second_value)){}

public:

    const Pair<first_type,second_type>&
    operator =(const Pair<first_type,second_type>& pair)
    {
        first_value=pair.first_value;
        second_value=pair.second_value;
        return *this;
    }
    const Pair<first_type,second_type>&
    operator =(Pair<first_type,second_type>&& pair)
    {
        first_value=std::move(pair.first_value);
        second_value=std::move(pair.second_value);
        return *this;
    }

    friend std::ostream &  operator <<
    (std::ostream& out,const Pair<first_type,second_type>& pair)
    {
        out<<"<"<<pair.first_value<<","<<pair.second_value<<">";
        return out;
    }

public:
    first_type first_value;
    second_type second_value;
};

}

#endif // PAIR_H
