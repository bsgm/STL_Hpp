#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include "iterator.hpp"
namespace STL{


template<typename T,typename Distance=unsigned long>
class LinkedList
{

public:
    template<typename data_type>
    struct Node
    {
        data_type data;
        Node<data_type>* prev;
        Node<data_type>* next;

        Node():prev(nullptr),next(nullptr){}
        Node(const data_type& data):
            data(data),prev(nullptr),next(nullptr){}
        Node(data_type&& data):
            data(std::move(data)),prev(nullptr),next(nullptr){}
        Node(const Node<data_type>& n):
            data(n.data),prev(nullptr),next(nullptr){}
        Node(Node<data_type>&& n):
            data(n.data),prev(nullptr),next(nullptr){}
    };
    struct iterator;


protected: //define

    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_value_type=const T;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_value_type=T&&;
    using ptr_right_value_type=T* &&;

    using size_type=Distance;

    using Node_type=Node<value_type>;
    using ptr_Node_type=Node<value_type>*;
    using ref_Node_type=Node<value_type>&;
    using const_Node_type=const Node<value_type>;
    using const_ptr_Node_type=const Node<value_type> *;
    using const_ref_Node_type=const Node<value_type> &;
    using right_Node_type=Node<value_type>&&;

    using iter_type=iterator;
    using ptr_iter_type=iterator *;
    using ref_iter_type=iterator&;
    using const_ref_iter_type=const iterator&;


    using self_type=LinkedList<value_type,Distance>;
    using ref_self_type=LinkedList<value_type,Distance>&;
    using right_self_type=LinkedList<value_type,Distance>&&;
    using const_ref_self_type=const LinkedList<value_type,Distance>&;


public: //iterator ~ reverse_iterator

    struct iterator:public base_iterator<bidirectional_iterator_tag,value_type,size_type>
    {
        ptr_Node_type ptr;

        bool operator==(const_ref_iter_type i){return ptr==i.ptr;}
        bool operator!=(const_ref_iter_type i){return ptr!=i.ptr;}
        const_ref_iter_type  operator=(ptr_Node_type i)
        {
            ptr=i;
            return *this;
        }
        const_ref_iter_type  operator=(const iterator& i)
        {
            ptr=i.ptr;
            return *this;
        }
        ref_type virtual operator*(){return ptr->data;}
        ptr_type virtual operator->(){return &(ptr->data);}
        ref_iter_type operator++()
        {
            ptr=ptr->next;
            return *this;
        }
        iter_type operator++(int)
        {
            iter_type t = *this;
            ptr=ptr->next;
            return t;
        }
        ref_iter_type operator--()
        {
            ptr=ptr->prev;
            return *this;
        }
        iter_type operator--(int)
        {
            iter_type t = *this;
            ptr=ptr->prev;
            return t;
        }
        iter_type operator-(size_type i)const
        {
            iterator t=*this;
            while(i--) t.ptr=t.ptr->prev;
            return t;
        }
        iter_type operator+(size_type i)const
        {
            iterator t=*this;
            while(i--) t.ptr=t.ptr->next;
            return t;
        }
    };

    using const_iterator        =typename STL::const_iterator<iterator>;
    using reverse_iterator      =typename STL::reverse_iterator<iterator>;
    using const_reverse_iterator=typename STL::const_iterator<reverse_iterator>;

public://constructor ~ destructor

    LinkedList()
    {
        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
        size=0;
    }
    LinkedList(const_ptr_type array,size_type n)
    {
        size=0;
        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
        for(size_type i=0;i<n;i++)
            push_back(array[i]);
    }
    LinkedList(ptr_right_value_type array,size_type n)
    {
        size=0;
        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
        for(size_type i=0;i<n;i++)
            push_back(std::move(array[i]));
        array=nullptr;
    }

    template<typename iterator_type>
    LinkedList(iterator_type first,iterator_type last)
    {
        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
        size=0;
        for(;first!=last;++first)
            push_back(*first);
    }

    LinkedList(const_ref_self_type list)
    {
        size=0;
        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
        for(iterator i=list.begin();i!=list.end();i++)
            push_back(*i);
    }
    LinkedList(right_self_type list)
    {
        start=list.start;
        finish=list.finish;
        size=list.size;
        ptr_Node_type node=new Node_type;
        node->next=node;
        node->prev=node;
        iter_type i;
        i.ptr=node;
        list.start=i;
        list.finish=i;
    }

    const_ref_self_type operator =(const_ref_self_type list)
    {
        empty();
        delete finish.ptr;

        start.ptr=finish.ptr=new Node_type;
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;

        for(iter_type i=list.begin();i!=list.end();i++)
            push_back(*i);
        return *this;
    }
    const_ref_self_type operator =(right_self_type list)
    {
        start=list.start;
        finish=list.finish;
        size=list.size;
        ptr_Node_type node=new Node_type;
        node->next=node;
        node->prev=node;
        iter_type i;
        i.ptr=node;
        list.start=i;
        list.finish=i;

        return *this;
    }

    ~LinkedList()
    {
        empty();
        delete finish.ptr;
    }

public: //insert

    void push_front(const_ref_type x)
    {
        insert(begin(),x);
    }
    void push_front(right_value_type x)
    {
        insert(begin(),std::move(x));
    }
    void push_back(const_ref_type x)
    {
        insert(end(),x);
    }
    void push_back(right_value_type x)
    {
        insert(end(),std::move(x));
    }
    iter_type insert(iter_type position,const_ref_type x)
    {
        ++size;
        iter_type prev=position-1;
        ptr_Node_type node=new Node_type(x);
        node->next=position.ptr;
        position.ptr->prev=node;
        node->prev=prev.ptr;
        prev.ptr->next=node;

        return position-1;
    }
    iter_type insert(iter_type position,right_value_type x)
    {
        ++size;
        iter_type prev=position-1;
        ptr_Node_type node=new Node_type(std::move(x));
        node->next=position.ptr;
        position.ptr->prev=node;
        node->prev=prev.ptr;
        prev.ptr->next=node;

        return position-1;
    }
    void splice(iter_type position,iter_type first,iter_type last)
    {
        iter_type prev=position-1;
        iter_type last_prev=last-1;
        prev.ptr->next=first.ptr;
        first.ptr->prev=prev.ptr;
        last_prev.ptr->next=position.ptr;
        position.ptr->prev=last_prev.ptr;
    }

public: //remove

    void empty()
    {
        size=0;
        iter_type iter=start+1;
        while(iter!=finish)
        {
            ptr_Node_type node=iter.ptr->next;
            delete iter.ptr;
            iter.ptr=node;
        }
        start.ptr->next=start.ptr;
        start.ptr->prev=start.ptr;
    }
    void erase(iter_type position)
    {
        --size;
        iter_type prev=position-1;
        iter_type next=position+1;
        prev.ptr->next=next.ptr;
        next.ptr->prev=prev.ptr;
        delete position.ptr;
    }
    template <typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(first);
    }

    value_type pop_front()
    {
        value_type t=*begin();
        erase(begin());
        return t;
    }
    value_type pop_back()
    {
        value_type t=*(end()-1);
        erase(end()-1);
        return t;
    }
    void remove(const_ref_type value)
    {
        iter_type first=begin();
        iter_type last=end();
        iter_type next;
        while(first!=last)
        {
            next=first+1;
            if(value==*first)
                erase(first);
            first=next;
        }
    }
    void unique()
    {
        if(!isEmpty())
            return;
        iter_type first=begin();
        iter_type last=end();
        iter_type next=first;
        while(++next!=last)
        {
            if(*first==*next)
                erase(next);
            else
                first=next;
            next=first;
        }
    }

public: //const function

    iter_type begin()const{return start+1;}
    iter_type end() const{return finish;}

    reverse_iterator rbegin()const{return finish-1;}
    reverse_iterator rend()const{return start;}

    const_iterator cbegin()const{return start+1;}
    const_iterator cend()const{return finish;}

    const_reverse_iterator crbegin()const{return rbegin();}
    const_reverse_iterator crend()const{return rend();}

    bool isEmpty()const{return begin()!=end();}
    size_type  length()const{return size;}
    const_ref_type back()const{return *crbegin();}
    const_ref_type front()const{return *cbegin();}

private: //data
    iter_type start;
    iter_type finish;
    size_type size;
};


}
#endif // LINKEDLIST_H
