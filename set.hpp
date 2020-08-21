#ifndef SET_H
#define SET_H

#include "avltree.hpp"
#include "iterator.hpp"
namespace STL{


template<
    typename Key,
    typename CMP=STL::less<Key>,
    typename Basic=STL::AvlTree<Key,CMP>
    >
class Set{
protected:
    using key_type=Key;
    using key_cmp=CMP;
    using ptr_type=Key*;
    using ref_type=Key&;
    using const_ptr_type=const Key*;
    using const_ref_type=const Key&;
    using right_ref_type=Key&&;

    using self_type=Set<Key,CMP,Basic>;
    using const_ref_self_type=const Set<Key,CMP,Basic>&;
    using right_ref_self_type=Set<Key,CMP,Basic>&&;

public:
    using iterator        =typename STL::const_iterator<typename Basic::iterator>;
    using reverse_iterator=typename STL::const_iterator<typename Basic::reverse_iterator>;

public:
    Set():basic(){}
    Set(const CMP &cmp):basic(cmp){}

    template<typename iter_type>
    Set(iter_type first,iter_type last){insert(first,last);}

    Set(const_ref_self_type set):basic(set.basic){}
    Set(right_ref_self_type set):basic(std::move(set.basic)){}

    ~Set(){empty();}

    const_ref_self_type operator =(const_ref_self_type set)
    {basic=set.basic;return *this;}
    const_ref_self_type operator =(right_ref_self_type set)
    {basic=std::move(set.basic);return *this;}

    iterator begin()const {return basic.begin();}
    iterator end()const {return basic.end();}

    reverse_iterator rbegin()const{return basic.rbegin();}
    reverse_iterator rend()const{return basic.rend();}
    bool isEmpty()const {return basic.isEmpty();}

    typename iterator_traits<iterator>::difference_type
    length()const {return basic.length();}

    void empty(){return basic.empty();}

    bool insert(const_ref_type key){return basic.insert_unique(key);}
    bool insert(right_ref_type key){return basic.insert_unique(std::move(key));}

    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {for(;first!=last;++first)insert(*first);}

    bool erase(const_ref_type key){return basic.erase(key);}
    bool erase(iterator i){return basic.erase(i.iter);}

    template<typename iter_type>
    void erase(iter_type first,iter_type last){basic.erase(first,last);}

    iterator find(const_ref_type key){return iterator(basic.find(key));}

    typename iterator_traits<iterator>::difference_type
    count(const_ref_type key){return basic.count(key);}

private:
    Basic basic;
};

}
#endif // SET_H
