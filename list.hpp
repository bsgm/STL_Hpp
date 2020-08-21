#ifndef LIST_H
#define LIST_H

#include "iterator.hpp"

namespace STL{

template<typename T,typename Distance=unsigned long>
class List
{

public: //define
    template<typename data_type>
    struct Node{
        data_type data;
        Node<data_type>* prev;
        Node<data_type>* next;

        Node()
        {
            prev=nullptr;
            next=nullptr;
        }
        Node(data_type data)
        {
            this->data=data;

            prev=nullptr;
            next=nullptr;

        }
        Node(data_type&& data)
        {
            this->data=data;
            prev=nullptr;
            next=nullptr;
        }
        Node(const Node<data_type>& n)
        {
            this->data=n.data;
            prev=nullptr;
            next=nullptr;
        }
        Node(Node<data_type>&& n)
        {
            this->data=n.data;
            prev=nullptr;
            next=nullptr;
        }
    };

    struct iterator;

    using size_type=Distance;

    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_value_type=const T;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_value_type=T&&;

    using Node_type=Node<value_type>;
    using ptr_Node_type=Node<value_type>*;

    using iter_type=iterator;
    using ref_iter_type=iterator&;
    using const_ref_iter_type=const iterator&;



public: //iterator ~ const_iterator

    struct iterator:public base_iterator<bidirectional_iterator_tag,value_type,size_type>
    {
        ptr_Node_type ptr;

        bool operator==(const_ref_iter_type i){return ptr==i.ptr;}
        bool operator!=(const_ref_iter_type i){return ptr!=i.ptr;}
        iter_type  operator=(ptr_Node_type i)
        {
            ptr=i;
            return *this;
        }
        iter_type  operator=(const iterator& i)
        {
            ptr=i.ptr;
            return *this;
        }
        ref_type operator*(){return ptr->data;}
        ptr_type operator->(){return &(ptr->data);}
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
        iter_type operator-(int i)const
        {
            iterator t=*this;
            for(int j=0;j<i;j++)
                t.ptr=t.ptr->prev;
            return t;
        }
        iter_type operator+(int i)const
        {
            iterator t=*this;
            for(int j=0;j<i;j++)
                t.ptr=t.ptr->next;
            return t;
        }
    };

    using const_iterator        =typename STL::const_iterator<iterator>;
    using reverse_iterator      =typename STL::reverse_iterator<iterator>;
    using const_reverse_iterator=typename STL::const_iterator<reverse_iterator>;

public://constructor ~ destructor

    List()
    {
        start.ptr=new Node_type();
        finish.ptr=new Node_type();
        start.ptr->next=finish.ptr;
        finish.ptr->prev=start.ptr;
        size=0;
    }
    template<typename iterator_type>
    List(iterator_type first,iterator_type last)
    {
        size=0;
        start.ptr=new Node_type();
        finish.ptr=new Node_type();
        start.ptr->next=finish.ptr;
        finish.ptr->prev=start.ptr;
        for(iterator_type i=first;i!=last;++i)
            push_back(*i);
    }

    ~List()
    {
        empty();
        delete start.ptr;
        delete finish.ptr;
    }

public: //insert

    void push_front(const_ref_type x)
    {
        ++size;
        ptr_Node_type node=new Node_type(x);
        node->next=(start+1).ptr;
        node->prev=start.ptr;
        (start+1).ptr->prev=node;
        start.ptr->next=node;
    }
    void push_back(const_ref_type x)
    {
        ++size;
        ptr_Node_type node=new Node_type(x);
        (finish-1).ptr->next=node;
        node->prev=(finish-1).ptr;
        node->next=finish.ptr;
        finish.ptr->prev=node;
    }
    iter_type insert(iter_type position,const_ref_type x)
    {
        ++size;
        iter_type prev=position-1;
        ptr_Node_type node=new Node_type(x);
        prev.ptr->next=node;
        node->prev=prev.ptr;
        node->next=position.ptr;
        position.ptr->prev=node;

        return position-1;
    }


public: //remove

    void empty()
    {
        iter_type iter=start+1;
        while(iter!=finish)
        {
            ptr_Node_type node=iter.ptr->next;
            delete iter.ptr;
            iter.ptr=node;
        }
        start.ptr->next=finish.ptr;
        finish.ptr->prev=start.ptr;
        size=0;
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

public: //const function
    size_type length()const{return size;}
    iter_type begin()const{return start+1;}
    iter_type end() const{return finish;}
    const_iterator cbegin()const{return begin();}
    const_iterator cend()const{return end();}
    reverse_iterator rbegin()const{return end()-1;}
    reverse_iterator rend()const{return begin()-1;}
    const_reverse_iterator crbegin()const{return rbegin();}
    const_reverse_iterator crend()const{return rend();}
    bool isEmpty()const{return begin()!=end();}
    const_ref_type back()const{return *crbegin();}
    const_ref_type front()const{return *cbegin();}

private: //data
    iter_type start;
    iter_type finish;
    size_type size;
};

}
#endif // LIST_H
