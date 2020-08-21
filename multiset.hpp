#ifndef MULTISET_H
#define MULTISET_H


#include "avltree.hpp"
#include "iterator.hpp"
#include "pair.hpp"
namespace STL{


template<
    typename Key,
    typename CMP=STL::less<Key>,
    typename Basic=STL::AvlTree<Key,CMP>
    >
class MultiSet{
protected:
    using key_type=Key;
    using key_cmp=CMP;
    using ptr_type=Key*;
    using ref_type=Key&;
    using const_ptr_type=const Key*;
    using const_ref_type=const Key&;
    using right_ref_type=Key&&;

    using self_type=MultiSet<Key,CMP,Basic>;
    using const_ref_self_type=const MultiSet<Key,CMP,Basic>&;
    using right_ref_self_type=MultiSet<Key,CMP,Basic>&&;

public:
    using iterator        =typename STL::const_iterator<typename Basic::iterator>;
    using reverse_iterator=typename STL::const_iterator<typename Basic::reverse_iterator>;
public:
    MultiSet():basic(){}
    MultiSet(const CMP &cmp):basic(cmp){}

    template<typename iter_type>
    MultiSet(iter_type first,iter_type last){insert(first,last);}

    MultiSet(const_ref_self_type set):basic(set.basic){}
    MultiSet(right_ref_self_type set):basic(std::move(set.basic)){}

    ~MultiSet(){empty();}

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

    void insert(const_ref_type key){basic.insert_equal(key);}
    void insert(right_ref_type key){basic.insert_equal(std::move(key));}

    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {for(;first!=last;++first)insert(*first);}

    bool erase(const_ref_type key){return basic.erase(key);}
    bool erase(iterator i){return basic.erase(i.iter);}

    template<typename iter_type>
    void erase(iter_type first,iter_type last){basic.erase(first,last);}

    iterator find(const_ref_type key){return iterator(basic.find(key));}

    Pair<iterator,iterator> equal_range(const_ref_type key)
    {
        Pair<typename Basic::iterator,typename Basic::iterator>
        pair=basic.equal_range(key);
        return Pair<iterator,iterator>(pair.first_value,pair.second_value);
    }

    typename iterator_traits<iterator>::difference_type
    count(const_ref_type key){return basic.count(key);}

private:
    Basic basic;
    CMP cmp;
};

}

#endif // MULTISET_H
