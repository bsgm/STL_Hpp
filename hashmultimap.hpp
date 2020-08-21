#ifndef HASHMULTIMAP_HPP
#define HASHMULTIMAP_HPP

#include "hashtable.hpp"
#include "pair.hpp"
namespace STL{
template <
    typename Key,
    typename Value,
    typename HashFcn = STL::Hash<Key>,
    typename EqualKey = STL::equal_to < Key >,
    typename Sequence = STL::HashTable<
                Pair<Key, Value>,
                Key, get_first<STL::Pair<Key, Value>>,
                HashFcn, EqualKey
                >
    >
class HashMultiMap{
protected:
    using key_type = Key;
    using ref_key_type = Key&;
    using ptr_key_type = Key*;
    using const_ref_key_type = const Key&;
    using const_ptr_key_type = const Key*;
    using right_ref_key_type = Key&&;

    using value_type = Value;
    using ref_value_type = Value&;
    using ptr_value_type = Value*;
    using const_ref_value_type = const Value&;
    using const_ptr_value_type = const Value*;
    using right_ref_value_type = Value&&;

    typedef typename STL::Pair<Key, Value> pair_type;
    typedef const pair_type& const_ref_pair_type;
    typedef const pair_type* const_ptr_pair_type;
    typedef pair_type&& right_ref_pair_type;

    using self_type = HashMultiMap<Key, HashFcn, EqualKey, Sequence>;
    using ref_self_type = HashMultiMap<Key, HashFcn, EqualKey, Sequence>&;
    using const_ref_self_type = const HashMultiMap<Key, HashFcn, EqualKey, Sequence>&;
    using right_ref_self_type = HashMultiMap<Key, HashFcn, EqualKey, Sequence>&&;


public:
    using iterator=typename STL::const_iterator<typename Sequence::iterator>;

public:
    HashMultiMap() :basic(){}

    template<typename iter_type>
    HashMultiMap(iter_type first, iter_type last){ insert(first, last); }

    HashMultiMap(ref_self_type set) :basic(set.basic){}
    HashMultiMap(right_ref_self_type set) :basic(std::move(set.basic)){}

    ~HashMultiMap(){ empty(); }

    const_ref_self_type operator =(ref_self_type set)
    {
        basic = set.basic; return *this;
    }
    const_ref_self_type operator =(right_ref_self_type set)
    {
        basic = std::move(set.basic); return *this;
    }

    ref_value_type operator [](const_ref_key_type key)
    {
        return (basic.get_insert_unique_position(pair_type(key,value_type())))->second_value;
    }

    iterator begin() { return basic.begin(); }
    iterator end() { return basic.end(); }

    bool isEmpty()const { return basic.isEmpty(); }

    typename iterator_traits<typename Sequence::iterator>::difference_type
    length()const { return basic.length(); }

    void empty(){ return basic.empty(); }

    void insert(const_ref_pair_type pair){basic.insert_equal(pair); }
    void insert(right_ref_pair_type pair){basic.insert_equal(std::move(pair)); }
    void insert(const_ref_key_type key, const_ref_value_type value){basic.insert_equal(pair_type(key,value)); }

    template<typename iter_type>
    void insert(iter_type first, iter_type last)
    {
        for (; first != last; ++first)insert(*first);
    }

    bool erase(const_ref_pair_type pair){ return basic.erase(pair); }

    bool erase(const_ref_key_type key){ return basic.erase(pair_type(key,value_type())); }

    bool erase(iterator i){ return basic.erase(i.iter); }

    template<typename iter_type>
    void erase(iter_type first, iter_type last){ basic.erase(first, last); }

    iterator find(const_ref_key_type key){ return basic.find(pair_type(key,value_type())); }

    typename iterator_traits<typename Sequence::iterator>::difference_type
    count(const_ref_key_type key){ return basic.count(pair_type(key,value_type())); }

    Pair<iterator,iterator> equal_range(const_ref_key_type key)
    {
        Pair<typename Sequence::iterator,typename Sequence::iterator> pair=basic.equal_range(pair_type(key,value_type()));
        return Pair<iterator,iterator>(pair.first_value,pair.second_value);
    }

private:
    Sequence basic;
};
}
#endif // HASHMULTIMAP_HPP
