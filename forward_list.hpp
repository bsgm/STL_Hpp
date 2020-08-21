#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <iostream>
#include "iterator.hpp"

namespace STL{
template <typename T,typename Distance=unsigned long>
class ForwardList
{
protected:
    template <typename V>
    struct Node{
        V data;
        Node * next;

        Node():next(nullptr){}
        Node(const V& v):data(v),next(nullptr){}
        Node(V&& v):data(std::move(v)),next(nullptr){}
    };

protected:
    using size_type=Distance;

    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_value_type=const T;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_value_type=T&&;

    using node_type=Node<value_type>;
    using ptr_node_type=Node<value_type>*;

public:
    struct iterator:public base_iterator<forward_iterator_tag,value_type,size_type>{
        ptr_node_type ptr;

        iterator():ptr(nullptr){}
        iterator(ptr_node_type p):ptr(p){}

        bool operator==(const iterator i){return ptr==i.ptr;}
        bool operator!=(const iterator i){return ptr!=i.ptr;}

        iterator  operator=(const iterator i)
        {
            ptr=i.ptr;
            return *this;
        }
        ref_type operator*(){return ptr->data;}
        ptr_type operator->(){return &(ptr->data);}
        iterator operator++()
        {
            ptr=ptr->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator t = *this;
            ptr=ptr->next;
            return t;
        }
    };

    using const_iterator        =typename STL::const_iterator<iterator>;

public:
    ForwardList():size(0){head=new node_type;}
    ~ForwardList(){empty(); delete head;}

    void insert_after(iterator position,const_ref_type x)
    {
        ptr_node_type node=new node_type(x);
        node->next=position.ptr->next;
        position.ptr->next=node;
        ++size;
    }

    void push_front(const_ref_type x)
    {insert_after(before_begin(),x);}

    void pop_front()
    {erase_after(before_begin());}

    void erase_after(iterator position)
    {
        ptr_node_type node=position.ptr->next;
        position.ptr->next=node->next;
        delete node;
        --size;
    }

    void remove(const_ref_type x)
    {
        ptr_node_type prev=head;
        ptr_node_type node=head->next;

        while(node)
        {
            if(node->data==x)
            {
                prev->next=node->next;
                delete node;
                node=prev->next;
                --size;
            }
            else{
                prev=prev->next;
                node=node->next;
            }
        }
    }

    void unique()
    {
        if(!isEmpty())return ;

        ptr_node_type prev=head;
        ptr_node_type node=head->next;

        while(node->next)
        {
            if(node->data==node->next->data){
                erase_after(prev);
                node=prev->next;
            }
            else
            {
                prev=prev->next;
                node=node->next;
            }
        }
    }
    void unique(const_ref_type x)
    {
        if(!isEmpty())return ;

        ptr_node_type prev=head;
        ptr_node_type node=head->next;

        while(node->next)
        {
            if(node->data==x&&node->next->data==x){
                erase_after(prev);
                node=prev->next;
            }
            else
            {
                prev=prev->next;
                node=node->next;
            }
        }
    }

    void reverse()
    {
        if(!isEmpty())return;
        ptr_node_type node=head->next;
        ptr_node_type prev=nullptr;
        ptr_node_type next=nullptr;

        while(node->next)
        {
            next=node->next;
            node->next=prev;
            prev=node;
            node=next;
        }
        node->next=prev;
        head->next=node;
    }

    void empty()
    {
        ptr_node_type node=head->next;
        ptr_node_type tmp=node;
        while(node)
        {
            tmp=tmp->next;
            delete node;
            node=tmp;
        }
        head->next=nullptr;
        size=0;
    }

    iterator before_begin()const{return iterator(head);}

    iterator begin()const{return iterator(head->next);}
    iterator end()const{return iterator(nullptr);}

    const_iterator cbegin()const{return const_iterator(begin());}
    const_iterator cend()const{return const_iterator(end());}

    size_type length()const{return size;}
    bool isEmpty()const{return size;}

private:
    ptr_node_type head;
    size_type size;
};
}

#endif // FORWARD_LIST_HPP
