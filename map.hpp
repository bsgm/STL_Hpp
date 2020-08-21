#ifndef MAP_H
#define MAP_H

#include "avltree.hpp"
#include "pair.hpp"
#include "iterator.hpp"

namespace STL{
template <
    typename Key,typename Value,
    typename CMP=STL::less<Key>,
    typename Basic=STL::AvlTree<Pair<Key,Value>,STL::PairCmpFirst<CMP>>
    >
class Map
{
protected:
    using key_type=Key;
    using ref_key_type=Key&;
    using const_ref_key_type=const Key&;
    using right_ref_key_type=Key&&;

    using value_type=Value;
    using ref_value_type=Value&;
    using const_ref_value_type=const Value&;
    using right_ref_value_type=Value&&;

    typedef typename STL::Pair<Key,Value> pair_type;
    typedef const pair_type& const_ref_pair_type;
    typedef const pair_type* const_ptr_pair_type;
    typedef pair_type&& right_ref_pair_type;

    using self_type=Map<Key,Value,CMP,Basic>;
    using const_ref_self_type=const Map<Key,Value,CMP,Basic>&;
    using right_ref_self_type=Map<Key,Value,CMP,Basic>&&;

public:
    using iterator        =typename STL::const_iterator<typename Basic::iterator>;
    using reverse_iterator=typename STL::const_iterator<typename Basic::reverse_iterator>;
public:
    Map():basic(){}

    Map(const CMP & cmp):basic(PairCmpFirst<CMP>(cmp)){}

    template<typename iter_type>
    Map(iter_type first,iter_type last){insert(first,last);}

    Map(const_ref_self_type map):basic(map.basic){}
    Map(right_ref_self_type map):basic(std::move(map.basic)){}

    ~Map(){empty();}

    const_ref_self_type operator =(const_ref_self_type set)
    {basic=set.basic;return *this;}
    const_ref_self_type operator =(right_ref_self_type set)
    {basic=std::move(set.basic);return *this;}

    iterator end()const {return basic.end();}
    iterator begin()const {return basic.begin();}

    reverse_iterator rbegin()const{return basic.rbegin();}
    reverse_iterator rend()const{return basic.rend();}

    bool isEmpty()const {return basic.isEmpty();}

    typename iterator_traits<iterator>::difference_type
    length()const {return basic.length();}

    void empty(){return basic.empty();}

    bool insert(const_ref_pair_type pair){return basic.insert_unique(pair);}

    bool insert(right_ref_pair_type pair)
    {return basic.insert_unique(std::move(pair));}

    bool insert(const_ref_key_type key,const_ref_value_type value)
    {return basic.insert_unique(pair_type(key,value));}

    bool insert(right_ref_key_type key,right_ref_value_type value)
    {return basic.insert_unique(std::move(pair_type(std::move(key),std::move(value))));}

    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {for(;first!=last;++first)insert(*first);}

    bool erase(const_ref_key_type key)
    {return basic.erase(pair_type(key,value_type()));}

    bool erase(iterator i){return basic.erase(i.iter);}

    bool erase(const_ref_pair_type pair){return basic.erase(pair);}

    template<typename iter_type>
    void erase(iter_type first,iter_type last){basic.erase(first,last);}

    iterator find(const_ref_key_type key)
    {return iterator(basic.find(pair_type(key,value_type())));}

    typename iterator_traits<iterator>::difference_type
    count(const_ref_key_type key)
    {return basic.count(pair_type(key,value_type()));}

    ref_value_type operator[](const_ref_key_type key)
    {return (*(basic.find(pair_type(key,value_type())))).second_value;}

private:
    Basic basic;
};

}
#endif // MAP_H
