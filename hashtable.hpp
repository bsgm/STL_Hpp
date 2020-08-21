#ifndef HASHTABLE_H
#define HASHTABLE_H
/**
 * <hashtable.hpp>
 *
 * HashTable (separate chaining)
 * SHash (quadraic probing)
 *
 */
#include <iostream>
#include "vector.hpp"
#include "iterator.hpp"
#include "function.hpp"
#include "pair.hpp"
namespace STL{

template <typename Key>struct Hash{};
inline unsigned long next_prime(unsigned long);

template <
    typename Value,
    typename Key,
    typename ExtractKey,
    typename HashFcn=STL::Hash<Key>,
    typename EqualKey=STL::equal_to<Key>
    >
class HashTable{
protected:
    template <typename T>
    struct Node{
        T data;
        Node<T> * next;
        Node():data(),next(nullptr){}
        Node(const T& value):data(value),next(nullptr){}
        Node(T&& value):data(std::move(value)),next(nullptr){}
        Node(const Node<T>& node):data(node.data),next(node.next){}
        Node(Node<T>&& node):data(std::move(node.data)),next(node.next){}
        ~Node(){}
    };

protected:
    using size_type=unsigned long;
    using value_type=Value;
    using ref_value_type=Value&;
    using ptr_value_type=Value*;
    using const_ref_value_type=const Value&;
    using const_ptr_value_type=const Value*;
    using right_ref_value_type=Value&&;

    using key_type=Key;
    using ref_key_type=Key&;
    using ptr_key_type=Key*;
    using const_ref_key_type=const Key&;
    using const_ptr_key_type=const Key*;
    using right_ref_key_type=Key&&;

    using node_type=Node<Value>;
    using ref_node_type=Node<Value>&;
    using ptr_node_type=Node<Value>*;
    using const_ref_node_type=const Node<Value>&;
    using const_ptr_node_type=const Node<Value>*;
    using right_ref_node_type=Node<Value>&&;

    using self_type=HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>;
    using ptr_self_type=HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>*;
    using ref_self_type=HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>&;
    using const_ptr_self_type=const HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>*;
    using const_ref_self_type=const HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>&;
    using right_ref_self_type=HashTable<Value,Key,ExtractKey,HashFcn,EqualKey>&&;

public:
    struct iterator:public base_iterator<forward_iterator_tag,value_type,size_type>{
        ptr_node_type cur;
        ptr_self_type ht;
        iterator():cur(nullptr),ht(nullptr){}
        iterator(ptr_node_type ptr,ptr_self_type h):cur(ptr),ht(h){
            size_type i=0;
            while(!cur&&i<ht->buckets_size())cur=ht->buckets[i++];
        }
        iterator(const iterator& i):cur(i.cur),ht(i.ht){}

        bool operator == (const iterator& i)const{return i.cur==cur;}
        bool operator != (const iterator& i)const{return i.cur!=cur;}

        const iterator& operator =(const iterator& i){ht=i.ht;cur=i.cur;return *this;}

        iterator operator ++()
        {

                const_ptr_node_type old=cur;
                cur=cur->next;
                if(!cur){
                    size_type bucket=ht->bkt_num(old->data);
                    while(!cur&& ++bucket < ht->buckets.length())
                        cur=ht->buckets[bucket];
            }
            return *this;
        }
        iterator operator ++(int)
        {
            iterator tmp=*this;
            ++(*this);
            return tmp;
        }
        ref_value_type operator *(){return cur->data;}
        ptr_value_type operator ->(){return & (cur->data);}
    };
private:
    void initialize_buckets(size_type n)
    {
        const size_type n_buckets=next_prime(n);
        buckets.resize(n_buckets,nullptr);
    }

    size_type bkt_num(const_ref_value_type v){return bkt_num_key(get_key(v));}

    size_type bkt_num(const_ref_value_type v,size_type n){return bkt_num_key(get_key(v),n);}

    size_type bkt_num_key(const_ref_key_type key){return bkt_num_key(key,buckets.length());}

    size_type bkt_num_key(const_ref_key_type key,size_type n){return hash(key) % n;}

    void delete_node(ptr_node_type first)
    {
        ptr_node_type next=first;
        while(first){
            next=next->next;
            delete first;
            --num_elements;
            first=next;
        }
    }

    void delete_node(ptr_node_type first,ptr_node_type last)
    {
        ptr_node_type next=first;
        while(first!=last){
            next=next->next;
            delete first;
            --num_elements;
            first=next;
        }
    }

    Pair<ptr_node_type,bool> erase_node(ptr_node_type first,const_ref_value_type v)
    {
        if(!first) return Pair<ptr_node_type,bool>(first,false);

        if(equal_key(get_key(v),get_key(first->data)))
        {
            ptr_node_type last=first;
            for(;last&&equal_key(get_key(v),get_key(last->data));last=last->next);
            delete_node(first,last);
            return  Pair<ptr_node_type,bool>(last,true);
        }
        else{
            ptr_node_type prev=first;
            for(ptr_node_type cur=first;cur;prev=cur,cur=cur->next)
            {
                if(equal_key(get_key(v),get_key(cur->data)))
                {
                    ptr_node_type last=cur;
                    for(;last&&equal_key(get_key(v),get_key(last->data));last=last->next);
                    prev->next=last;
                    delete_node(cur,last);

                    return  Pair<ptr_node_type,bool>(first,true);
                }
            }
        }
        return  Pair<ptr_node_type,bool>(first,false);
    }

    Pair<ptr_node_type,bool> erase_node(ptr_node_type first,ptr_node_type cur)
    {
        if(!first) return Pair<ptr_node_type,bool>(first,false);
        if(first==cur)
        {
            first=first->next;
            delete cur;
            --num_elements;
            return Pair<ptr_node_type,bool>(first,true);
        }
        else
        {
            ptr_node_type prev=first;
            for(;prev&&prev->next!=cur;prev=prev->next);
            if(prev) prev->next=cur->next;
            delete cur;
            --num_elements;
            return Pair<ptr_node_type,bool>(first,true);
        }
        return Pair<ptr_node_type,bool>(first,false);
    }

public:
    HashTable():num_elements(0){initialize_buckets(0);}

    HashTable(ref_self_type self) :
        num_elements(0), hash(self.hash),
        get_key(self.get_key), equal_key(self.equal_key){
        initialize_buckets(self.buckets_size());
        insert(self.begin(),self.end());
    }
    HashTable(right_ref_self_type self) :
        num_elements(self.num_elements), hash(self.hash),
        get_key(self.get_key), equal_key(self.equal_key),
        buckets(){
        num_elements=self.num_elements;
        buckets.resize(self.buckets_size(),nullptr);
        STL::copy_n(self.buckets.begin(),self.buckets.end(),buckets.begin());
        self.buckets.resize(self.buckets_size(),nullptr);
        self.num_elements=0;
    }
    const_ref_self_type operator =(ref_self_type self)
    {
        empty();
        num_elements=self.num_elements;
        hash=self.hash;
        get_key=self.get_key;
        equal_key=self.equal_key;
        buckets.resize(self.buckets_size(),nullptr);
        insert(self.begin(),self.end());

        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type self)
    {
        empty();
        num_elements=self.num_elements;
        hash=self.hash;
        get_key=self.get_key;
        equal_key=self.equal_key;
        buckets.resize(self.buckets_size(),nullptr);
        STL::copy_n(self.buckets.begin(),self.buckets.end(),buckets.begin());
        self.buckets.resize(self.buckets_size(),nullptr);
        self.num_elements=0;
        return *this;
    }

    ~HashTable(){empty();}

    iterator begin(){return iterator(*buckets.begin(),this);}
    iterator end(){return iterator();}
    bool isEmpty()const{return num_elements;}
    size_type length()const{return num_elements;}
    size_type buckets_size()const{return buckets.length();}

    void resize(size_type num_elements_hint)
    {
        const size_type old_n=buckets.length();
        if(num_elements_hint>old_n)
        {
            const size_type n=next_prime(num_elements_hint);
            if(n>old_n)
            {
                Vector<ptr_node_type,size_type> tmp;
                tmp.resize(n,nullptr);
                ptr_node_type first=nullptr;
                for(size_type bucket=0;!first&&bucket<old_n;++bucket)
                {
                    first=buckets[bucket];
                    while(first)
                    {
                        size_type new_bucket=bkt_num(first->data,n);
                        buckets[bucket]=first->next;
                        first->next=tmp[new_bucket];
                        tmp[new_bucket]=first;
                        first=buckets[bucket];
                    }

                }
                buckets.swap(std::move(tmp));
            }
        }
    }

    bool insert_unique(const_ref_value_type v)
    {
        resize(num_elements+1);
        const size_type bucket=bkt_num(v);
        ptr_node_type first=buckets[bucket];

        for(ptr_node_type cur=first;cur;cur=cur->next)
            if (equal_key(get_key(v),get_key(cur->data)))
                return false;
        ptr_node_type tmp=new node_type(v);
        tmp->next=first;
        buckets[bucket]=tmp;
        ++num_elements;
        return true;
    }

    void insert_equal(const_ref_value_type v)
    {
        resize(num_elements+1);
        const size_type n=bkt_num(v);
        ptr_node_type first=buckets[n];
        for(ptr_node_type cur=first;cur;cur=cur->next)
            if (equal_key(get_key(v),get_key(cur->data)))
            {
                ptr_node_type tmp=new node_type(v);
                tmp->next=cur->next;
                cur->next=tmp;
                ++num_elements;
                return ;
            }
        ptr_node_type tmp=new node_type(v);
        tmp->next=first;
        buckets[n]=tmp;
        ++num_elements;
    }

    bool insert_unique(right_ref_value_type v)
    {
        resize(num_elements + 1);
        const size_type bucket = bkt_num(v);
        ptr_node_type first = buckets[bucket];

        for (ptr_node_type cur = first; cur; cur = cur->next)
        if (equal_key(get_key(v),get_key(cur->data)))
            return false;
        ptr_node_type tmp = new node_type(std::move(v));
        tmp->next = first;
        buckets[bucket] = tmp;
        ++num_elements;
        return true;
    }

    void insert_equal(right_ref_value_type v)
    {
        resize(num_elements + 1);
        const size_type n = bkt_num(v);
        ptr_node_type first = buckets[n];
        for (ptr_node_type cur = first; cur; cur = cur->next)
        if (equal_key(get_key(v),get_key(cur->data)))
        {
            ptr_node_type tmp = new node_type(std::move(v));
            tmp->next = cur->next;
            cur->next = tmp;
            ++num_elements;
            return;
        }
        ptr_node_type tmp = new node_type(std::move(v));
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
    }

    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {
        for(;first!=last;++first)insert_equal(*first);
    }

    void empty()
    {
        ptr_node_type first;
        for(size_type i=0;i<buckets.length();++i)
        {
            first=buckets[i];
            if(first)
            {
                delete_node(first);
                buckets[i]=nullptr;
            }
        }
        num_elements=0;
    }

    bool erase(const_ref_value_type v)
    {
        size_type bucket=bkt_num(v);
        ptr_node_type first=buckets[bucket];
        Pair<ptr_node_type,bool> pair=erase_node(first,v);
        buckets[bucket]=pair.first_value;
        return pair.second_value;
    }

    bool erase(iterator iter)
    {
        const size_type bucket=bkt_num(iter.cur->data);
        ptr_node_type first=buckets[bucket];
        Pair<ptr_node_type,bool> pair=erase_node(first,iter.cur);
        buckets[bucket]=pair.first_value;
        return pair.second_value;
    }

    template<typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(*first);
    }

    iterator find(const_ref_value_type v)
    {
        ptr_node_type first=buckets[bkt_num(v)];
        ptr_node_type cur=first;
        for(;cur&&!equal_key(get_key(v),get_key(cur->data));cur=cur->next);
        if(cur)
            return iterator(cur,this);
        else
            return iterator();
    }
    iterator get_insert_unique_position(const_ref_value_type v)
    {
        resize(num_elements + 1);
        const size_type bucket = bkt_num(v);
        ptr_node_type first = buckets[bucket];

        for (ptr_node_type cur = first; cur; cur = cur->next)
        if (equal_key(get_key(v),get_key(cur->data)))
        {
            return iterator(cur,this);
        }
        ptr_node_type tmp = new node_type(std::move(v));
        tmp->next = first;
        buckets[bucket] = tmp;
        ++num_elements;
        return iterator(tmp,this);
    }

    Pair<iterator,iterator> equal_iterator_range(const_ref_value_type v)
    {
        size_type bucket=bkt_num(v);
        ptr_node_type first=buckets[bucket];
        ptr_node_type cur=first;
        for(;cur&&!equal_key(get_key(v),get_key(cur->data));cur=cur->next);
        if(!cur)return Pair<iterator,iterator>(end(),end());
        first=cur;
        ptr_node_type last=cur;
        for(;last&&equal_key(get_key(v),get_key(last->data));last=last->next);
        if(!last){ do{++bucket;}while(bucket<buckets_size()&&!buckets[bucket]);last=buckets[bucket];}
        if(bucket>=buckets_size()) return Pair<iterator,iterator>(iterator(first,this),end());
        return Pair<iterator,iterator>(iterator(first,this),iterator(last,this));
    }

    typedef Vector<value_type,size_type> equal_range_type;

    Vector<value_type,size_type>
    equal_range(const_ref_value_type v)
    {
        Vector<value_type,size_type> range(count(v));
        for(ptr_node_type cur=buckets[bkt_num(v)];cur;cur=cur->next)
            if(equal_key(get_key(v),get_key(cur->data)))
                range.push_back(cur->data);
        return range;
    }

    size_type count(const_ref_value_type v)
    {
        ptr_node_type first=buckets[bkt_num(v)];
        ptr_node_type cur=first;
        for(;cur&&!equal_key(get_key(v),get_key(cur->data));cur=cur->next);
        size_type n=0;
        for(;cur&&equal_key(get_key(v),get_key(cur->data));cur=cur->next,++n);
        return n;
    }



private:
    size_type num_elements;
    HashFcn hash;
    ExtractKey get_key;
    EqualKey equal_key;
    Vector<ptr_node_type,size_type> buckets;
};

template <
    typename Value,
    typename Key,
    typename ExtractKey,
    typename HashFcn=STL::Hash<Key>,
    typename EqualKey=STL::equal_to<Key>
    >
class SHash{

protected:
    using size_type=unsigned long;
    using value_type=Value;
    using ref_value_type=Value&;
    using ptr_value_type=Value*;
    using const_ref_value_type=const Value&;
    using const_ptr_value_type=const Value*;
    using right_ref_value_type=Value&&;

    using key_type=Key;
    using ref_key_type=Key&;
    using ptr_key_type=Key*;
    using const_ref_key_type=const Key&;
    using const_ptr_key_type=const Key*;
    using right_ref_key_type=Key&&;

    using self_type=SHash<Value,Key,ExtractKey,HashFcn,EqualKey>;
    using ptr_self_type=SHash<Value,Key,ExtractKey,HashFcn,EqualKey>*;
    using ref_self_type=SHash<Value,Key,ExtractKey,HashFcn,EqualKey>&;
    using const_ptr_self_type=const SHash<Value,Key,ExtractKey,HashFcn,EqualKey>*;
    using const_ref_self_type=const SHash<Value,Key,ExtractKey,HashFcn,EqualKey>&;
    using right_ref_self_type=SHash<Value,Key,ExtractKey,HashFcn,EqualKey>&&;

public:
    struct iterator:public base_iterator<forward_iterator_tag,value_type,size_type>{
        typename Vector<ptr_value_type,size_type>::iterator cur;
        ptr_self_type ht;
        iterator():cur(nullptr),ht(nullptr){}
        iterator(typename Vector<ptr_value_type,size_type>::iterator ptr,ptr_self_type h):cur(ptr),ht(h){
            while(!*cur&&cur!=ht->buckets.end())++cur;
        }
        iterator(const iterator& i):cur(i.cur),ht(i.ht){}

        bool operator == (const iterator& i)const{return i.cur==cur;}
        bool operator != (const iterator& i)const{return i.cur!=cur;}

        const iterator& operator =(const iterator& i){ht=i.ht;cur=i.cur;return *this;}

        iterator operator ++()
        {
            do{++cur;}while(!*cur&&cur!=(ht->buckets.end()));
            return *this;
        }
        iterator operator ++(int)
        {
            iterator tmp=*this;
            ++(*this);
            return tmp;
        }
        ref_value_type operator *(){return *(*cur);}
        ptr_value_type operator ->(){return *cur;}
    };


private:

    void initialize_buckets(size_type n){buckets.resize(next_prime(n),nullptr);}

    size_type bkt_num(const_ref_value_type v){return bkt_num_key(get_key(v));}

    size_type bkt_num(const_ref_value_type v,size_type n){return bkt_num_key(get_key(v),n);}

    size_type bkt_num_key(const_ref_key_type key){return bkt_num_key(key,buckets.length());}

    size_type bkt_num_key(const_ref_key_type key,size_type n){return hash(key) % n;}

public:
    SHash():num_elements(0){initialize_buckets(0);}
    SHash(size_type n):num_elements(0){initialize_buckets(n);}
    SHash(ref_self_type self) :
        num_elements(0), hash(self.hash),
        get_key(self.get_key), equal_key(self.equal_key){
        initialize_buckets(self.buckets_size());
        insert(self.begin(),self.end());
    }
    SHash(right_ref_self_type self) :
        num_elements(self.num_elements), hash(self.hash),
        get_key(self.get_key), equal_key(self.equal_key),
        buckets(){
        num_elements=self.num_elements;
        buckets.resize(self.buckets_size(),nullptr);
        STL::copy_n(self.buckets.begin(),self.buckets.end(),buckets.begin());
        self.buckets.resize(self.buckets_size(),nullptr);
        self.num_elements=0;
    }
    const_ref_self_type operator =(ref_self_type self)
    {
        empty();
        num_elements=self.num_elements;
        hash=self.hash;
        get_key=self.get_key;
        equal_key=self.equal_key;
        buckets.resize(self.buckets_size(),nullptr);
        insert(self.begin(),self.end());
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type self)
    {
        empty();
        num_elements=self.num_elements;
        hash=self.hash;
        get_key=self.get_key;
        equal_key=self.equal_key;
        buckets.resize(self.buckets_size(),nullptr);
        STL::copy_n(self.buckets.begin(),self.buckets.end(),buckets.begin());
        self.buckets.resize(self.buckets_size(),nullptr);
        self.num_elements=0;
        return *this;
    }

    ~SHash(){empty();}

    iterator begin(){return iterator(buckets.begin(),this);}
    iterator end(){return iterator(buckets.end(),this);}
    bool isEmpty()const{return num_elements;}
    size_type length()const{return num_elements;}
    size_type buckets_size()const{return buckets.length();}

    void resize(size_type num_elements_hint)
    {
        const size_type old_n=buckets.length();
        if( num_elements_hint*2 >old_n)
        {
            const size_type n=next_prime(num_elements_hint*2);
            if(n>old_n)
            {
                Vector<ptr_value_type,size_type> tmp;
                tmp.resize(n,nullptr);
                size_type i=0;
                for(size_type bucket=0;bucket<old_n;++bucket)
                {
                    if(buckets[bucket])
                    {
                        for(i=bkt_num(*buckets[bucket],n);tmp[i];i=(i+((i<<1)-1))%n);
                        tmp[i]=buckets[bucket];
                    }
                }
                buckets.swap(std::move(tmp));
            }
        }
    }

    bool insert_unique(right_ref_value_type v)
    {
        resize(num_elements + 1);
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                return false;
        buckets[i]=new value_type;
        *buckets[i]=std::move(v);
        ++num_elements;
        return true;
    }
    bool insert_unique(const_ref_value_type v)
    {
        resize(num_elements + 1);
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                return false;
        buckets[i]=new value_type;
        *buckets[i]=v;
        ++num_elements;
        return true;
    }

    void insert_equal(right_ref_value_type v)
    {
        resize(num_elements + 1);
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size());
        buckets[i]=new value_type;
        *buckets[i]=std::move(v);
        ++num_elements;
    }
    void insert_equal(const_ref_value_type v)
    {
        resize(num_elements + 1);
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size());
        buckets[i]=new value_type;
        *buckets[i]=v;
        ++num_elements;
    }
    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {
        for(;first!=last;++first)insert_equal(*first);
    }
    bool erase(const_ref_value_type v)
    {
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
            {
                delete buckets[i];
                buckets[i]=nullptr;
                --num_elements;
            }
        if(i==bkt_num(v)) return false;

        return true;
    }

    bool erase(iterator iter)
    {
        size_type i=bkt_num(*iter);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(iter.operator->()==buckets[i])
            {
                delete buckets[i];
                buckets[i]=nullptr;
                --num_elements;
                return true;
            }
        return false;
    }

    template<typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(*first);
    }

    iterator find(const_ref_value_type v)
    {
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                return iterator(buckets.begin()+i,this);
        return iterator(buckets.end(),this);
    }
    size_type count(const_ref_value_type v)
    {
        size_type size=0;
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                ++size;
        return size;
    }

    iterator get_insert_unique_position(const_ref_value_type v)
    {
        resize(num_elements + 1);
        size_type i=bkt_num(v);
        for(;buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                return iterator(buckets.begin()+i,this);
        buckets[i]=new value_type;
        *buckets[i]=std::move(v);
        ++num_elements;
        return iterator(buckets.begin()+i,this);
    }

    typedef Vector<value_type,size_type> equal_range_type;
    Vector<value_type,size_type>
    equal_range(const_ref_value_type v)
    {
        Vector<value_type,size_type> range(count(v));
        for(size_type i=bkt_num(v);buckets[i];i=(i+((i<<1)-1))%buckets_size())
            if(equal_key(get_key(v),get_key(*buckets[i])))
                range.push_back(*buckets[i]);
        return range;
    }

    void empty()
    {
        for(size_type i=0;i<buckets_size();++i)
            if(buckets[i])
            {
                delete buckets[i];
                buckets[i]=nullptr;
            }
        num_elements=0;
    }


private:
    size_type num_elements;
    HashFcn hash;
    ExtractKey get_key;
    EqualKey equal_key;
    Vector<ptr_value_type,size_type> buckets;

};




inline size_t hash_string(const char* s)
{
    unsigned long h=0;
    for(;*s;++s) h=5*h+*s;
    return (size_t)h;
}
inline size_t hash_string(const std::string& s)
{
    unsigned long h=0;
    for(size_t i=0;i!=s.length();++i)
        h = 5*h + s[i];
    return (size_t)h;
}

template<>struct Hash<char*>{size_t operator ()(const char* s)const{return hash_string(s);}};
template<>struct Hash<const char*>{size_t operator ()(const char* s)const{return hash_string(s);}};
template<>struct Hash<char>{size_t operator ()(char x)const{return x;}};
template<>struct Hash<unsigned char>{size_t operator ()(unsigned char x)const{return x;}};
template<>struct Hash<signed char>{size_t operator ()(signed char x)const{return x;}};
template<>struct Hash<short>{size_t operator ()(short x)const{return x;}};
template<>struct Hash<unsigned short>{size_t operator ()(unsigned short x)const{return x;}};
template<>struct Hash<int>{size_t operator ()(int x)const{return x;}};
template<>struct Hash<unsigned int>{size_t operator ()(unsigned int x)const{return x;}};
template<>struct Hash<long>{size_t operator ()(long x)const{return x;}};
template<>struct Hash<unsigned long>{size_t operator ()(unsigned long x)const{return x;}};
template<>struct Hash<std::string>{size_t operator ()(const std::string& s){return hash_string(s);}};

static const int num_primes=28;
static const unsigned long prime_array[num_primes]={
    53,         97,         193,        389,        769,
    1543,       3079,       6151,       12289,      24593,
    49157,      98317,      196613,     393241,     786433,
    1572869,    3145739,    6291469,    12582917,   25165843,
    50331653,   100663319,  20326611,   402653189,  805306457,
    1610612741, 3221225473ul,4294967291ul
};
inline unsigned long next_prime(unsigned long n)
{
    for(int i=0;i<num_primes;++i)
        if(n<=prime_array[i])
            return prime_array[i];
    return prime_array[num_primes-1];
}

}
#endif // HASHTABLE_H
