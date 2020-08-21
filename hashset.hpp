#ifndef HASHSET_HPP
#define HASHSET_HPP

#include "hashtable.hpp"
#include "iterator.hpp"

namespace STL{
template <
    typename Key,
    typename HashFcn = STL::Hash<Key>,
    typename EqualKey = STL::equal_to < Key >,
    typename Sequence = STL::HashTable<Key,Key,
                        typename STL::identity<Key>,
                        HashFcn,EqualKey
                        >
        >
class HashSet{
protected:
    using key_type = Key;
    using ref_key_type = Key&;
    using ptr_key_type = Key*;
    using const_ref_key_type = const Key&;
    using const_ptr_key_type = const Key*;
    using right_ref_key_type = Key&&;

    using self_type = HashSet<Key, HashFcn, EqualKey, Sequence>;
    using ref_self_type = HashSet<Key, HashFcn, EqualKey, Sequence>&;
    using const_ref_self_type =const HashSet<Key, HashFcn, EqualKey, Sequence>&;
    using right_ref_self_type = HashSet<Key, HashFcn, EqualKey, Sequence>&&;


public:
    using iterator=typename STL::const_iterator<typename Sequence::iterator>;

public:
    HashSet() :basic(){}

    template<typename iter_type>
    HashSet(iter_type first, iter_type last){ insert(first, last); }

    HashSet(ref_self_type set) :basic(set.basic){}
    HashSet(right_ref_self_type set) :basic(std::move(set.basic)){}

    ~HashSet(){ empty(); }

    const_ref_self_type operator =(ref_self_type set)
    {
        basic = set.basic; return *this;
    }
    const_ref_self_type operator =(right_ref_self_type set)
    {
        basic = std::move(set.basic); return *this;
    }

    iterator begin() { return basic.begin(); }
    iterator end() { return basic.end(); }

    bool isEmpty()const { return basic.isEmpty(); }

    typename iterator_traits<iterator>::difference_type
    length()const { return basic.length(); }

    void empty(){ return basic.empty(); }

    bool insert(const_ref_key_type key){ return basic.insert_unique(key); }
    bool insert(right_ref_key_type key){ return basic.insert_unique(std::move(key)); }

    template<typename iter_type>
    void insert(iter_type first, iter_type last)
    {
        for (; first != last; ++first)insert(*first);
    }

    bool erase(const_ref_key_type key){ return basic.erase(key); }
    bool erase(iterator i){ return basic.erase(i.iter); }

    template<typename iter_type>
    void erase(iter_type first, iter_type last){ basic.erase(first, last); }

    iterator find(const_ref_key_type key){ return iterator(basic.find(key)); }

    typename iterator_traits<iterator>::difference_type
    count(const_ref_key_type key){ return basic.count(key); }


private:
    Sequence basic;
};
}
#endif // HASHSET_HPP
