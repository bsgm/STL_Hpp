#ifndef BINARYTREE_H
#define BINARYTREE_H
/**
 * <binarytree.hpp>
 *
 * BinaryTree (nonrecursive)
 *
 * RecursiveTree (recursive)
 *
 *
 */

#include <iostream>
#include "function.hpp"
#include "iterator.hpp"

namespace STL{

template <typename T,typename bCMP=STL::less<T>,typename Distance=int>
class BinaryTree{
protected:
    template<typename Type> struct Node;

    using size_type=Distance;

    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_ref_type=T&&;

    using node_type=Node<T>;
    using ptr_node_type=Node<T>*;
    using ref_node_type=Node<T>&;
    using const_ref_node_type=const Node<T>&;
    using const_ptr_node_type=const Node<T>*;
    using const_ref_ptr_node_type=const Node<T>* &;
    using right_node_type=Node<T>&&;

    using self_type=BinaryTree<T,bCMP>;
    using ref_self_type=BinaryTree<T,bCMP>&;
    using const_ref_self_type=const BinaryTree<T,bCMP>&;
    using right_ref_self_type=BinaryTree<T,bCMP>&&;

protected:

    template <typename Type>
    struct Node{
        Type data;
        Node<Type> * parent;
        Node<Type> * left;
        Node<Type> * right;

        Node():parent(nullptr),left(nullptr),right(nullptr){}

        Node(const Type& data):
            data(data),parent(nullptr),left(nullptr),right(nullptr){}

        Node(Type&& data):
            data(std::move(data)),parent(nullptr),left(nullptr),right(nullptr){}

        Node(const Node<Type>& node):
            data(node.data),parent(node.parent),
            left(node.left),right(node.right){}

        Node(Node<Type>&& node):
            data(std::move(node.data)),parent(node.parent),
            left(node.left),right(node.right){}
        ~Node(){}
    };
public:
    struct iterator:public base_iterator<bidirectional_iterator_tag,value_type,size_type>{
        ptr_node_type ptr;
        iterator():ptr(nullptr){}
        iterator(ptr_node_type  ptr):ptr(ptr){}
        iterator(const iterator & i):ptr(i.ptr){}
        ref_type operator*(){return ptr->data;}
        //ptr_type operator->(){return &(ptr->data);}
        ptr_node_type operator->(){return ptr;}
        bool operator == (const iterator& i){return i.ptr==ptr;}
        bool operator != (const iterator& i){return i.ptr!=ptr;}

        const iterator& operator =(ptr_node_type p){ptr=p;return *this;}
        const iterator& operator =(iterator& i){ptr=i.ptr;return *this;}

        iterator operator ++()
        {
            increment();
            return *this;
        }

        iterator operator ++(int)
        {
            iterator tmp=*this;
            ++(*this);
            return tmp;
        }
        iterator operator --()
        {
            decrement();
            return *this;
        }

        iterator operator --(int)
        {
            iterator tmp=*this;
            --(*this);
            return tmp;
        }
    private:
        void increment()
        {
            if(ptr->right!=nullptr)
            {
                ptr=ptr->right;
                while(ptr->left!=nullptr)
                    ptr=ptr->left;
            }
            else
            {
                ptr_node_type y=ptr->parent;
                if(y==nullptr&&ptr->right==nullptr)
                    ptr=nullptr;
                else{
                    while(y!=nullptr&&ptr==y->right){
                        ptr=y;
                        y=y->parent;
                    }
                    if(ptr->right!=y)
                        ptr=y;
                }
            }
        }
        void decrement()
        {
            if(ptr->left!=nullptr)
            {
                ptr=ptr->left;
                while(ptr->right!=nullptr)
                    ptr=ptr->right;
            }
            else
            {
                ptr_node_type y=ptr->parent;
                if(y==nullptr&&ptr->left==nullptr)
                    ptr=nullptr;
                else{
                    while(y!=nullptr&&ptr==y->left){
                        ptr=y;
                        y=y->parent;
                    }
                    if(ptr->left!=y)
                        ptr=y;
                }
            }
        }
    };
    using reverse_iterator=reverse_iterator<iterator>;
    using const_iterator=const_iterator<iterator>;
protected:
    ptr_node_type findMin(ptr_node_type i)
    {
        while(i->left!=nullptr)
            i=i->left;
        return i;
    }

    void make_empty(iterator iter)
    {
        if(iter.ptr!=nullptr)
        {
            //std::cout<<iter->data<<std::endl;
            make_empty(iter->left);
            make_empty(iter->right);
            delete iter.ptr;
        }
    }

public:

    BinaryTree():root(),size(0){}
    BinaryTree(const_ref_self_type tree):root(),size(0)
    {
        insert(tree.begin(),tree.end());
    }
    BinaryTree(right_ref_self_type tree)
    {
        root=tree.root;
        size=tree.size;
        tree.root.ptr=nullptr;
        tree.size=0;
    }
    template<typename iter_type>
    BinaryTree(iter_type first,iter_type last):root(),size(0)
    {
        for(;first!=last;++first)insert(*first);
    }
    const_ref_self_type operator =(const_ref_self_type tree)
    {
        empty();
        insert(tree.begin(),tree.end());
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type tree)
    {
        empty();
        root=tree.root;
        size=tree.size;
        tree.root.ptr=nullptr;
        tree.size=0;
        return *this;
    }

    ~BinaryTree(){empty();}
public:
    iterator begin()const{return findMin();}
    iterator  end()const{return iterator(nullptr);}

    reverse_iterator rbegin()const{return findMax();}
    reverse_iterator rend()const{return iterator(nullptr);}

    const_iterator cbegin()const{return findMin();}
    const_iterator cend()const{return iterator(nullptr);}

    bool isEmpty()const{return root.ptr!=nullptr;}

    size_type length()const {return size;}

    bool count(const_ref_type x)const
    {
        iterator iter=root;
        while(iter.ptr!=nullptr)
            if(cmp(x,*iter))
                iter=iter->left;
            else if(cmp(*iter,x))
                iter=iter->right;
            else
                return true;
        return false;
    }

    iterator find(const_ref_type v)
    {
        iterator iter=root;
        while(iter.ptr!=nullptr)
            if(cmp(v,*iter))
                iter=iter->left;
            else if(cmp(*iter,v))
                iter=iter->right;
            else
                return iter;
        return iterator(nullptr);
    }
    iterator findMin()const
    {
        iterator iter=root;
        if(root.ptr==nullptr)
            return root;
        while(iter->left!=nullptr)
            iter=iter->left;
        return iter;
    }
    iterator findMax()const
    {
        iterator iter=root;
        if(root.ptr==nullptr)
            return root;
        while(iter->right!=nullptr)
            iter=iter->right;
        return iter;
    }

public:
    bool insert(const_ref_type v)
    {
        if(root.ptr==nullptr){
            ++size;
            root=new node_type(v);
            return true;
        }
        iterator iter=root;
        iterator parent;
        bool flag;      //right true,left false;
        for(;;)
        {
            if(iter.ptr==nullptr){
                iter=new node_type(v);
                iter->parent=parent.ptr;
                if(flag)
                    parent->right=iter.ptr;
                else
                    parent->left=iter.ptr;
                ++size;
                return true;
            }
            else{
                if(cmp(v,*iter)){
                    flag=false;
                    parent=iter;
                    iter=iter->left;
                }
                else if(cmp(*iter,v)){
                    flag=true;
                    parent=iter;
                    iter=iter->right;
                }
                else
                    return false;
            }
        }
    }
    bool insert(right_ref_type v)
    {
        if(root.ptr==nullptr){
            ++size;
            root=new node_type(std::move(v));
            return true;
        }
        iterator iter=root;
        iterator parent;
        bool flag;      //right true,left false;
        for(;;)
        {
            if(iter.ptr==nullptr){
                ++size;
                iter=new node_type(std::move(v));
                iter->parent=parent.ptr;
                if(flag)
                    parent->right=iter.ptr;
                else
                    parent->left=iter.ptr;
                return true;
            }
            else{
                if(cmp(v,*iter)){
                    flag=false;
                    parent=iter;
                    iter=iter->left;
                }
                else if(cmp(*iter,v)){
                    flag=true;
                    parent=iter;
                    iter=iter->right;
                }
                else
                    return false;
            }
        }
    }
    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {
        for(;first!=last;++first)insert(*first);
    }

    //Set or Map port
    bool insert_unique(const_ref_type x){return insert(x);}
    bool insert_unique(right_ref_type x){return insert(std::move(x));}

public:
    bool erase(const_ref_type v)
    {
        iterator iter=find(v);
        if(iter.ptr==nullptr)
            return false;
        --size;
        if(iter==root)
        {
            if(root->right!=nullptr)
            {
                iterator left(root->left);
                iterator right(root->right);

                right->parent=nullptr;
                right->left=left.ptr;
                if(left.ptr!=nullptr)
                    left->parent=right.ptr;
                delete iter.ptr;
                root=right;
            }
            else if(root->left!=nullptr)
            {
                root.ptr=root->left;
                root->parent=nullptr;
                delete iter.ptr;
            }
            else
            {
                delete iter.ptr;
                root.ptr=nullptr;
            }
        }
        else if(iter->left&&iter->right)
        {
            iterator right_min;
            right_min.ptr=findMin(iter->right);
            if(right_min.ptr==iter->right){
                    right_min.ptr=iter->left;
                    iter->left=nullptr;
            }
            iter->data=right_min->data;

            if(right_min->parent->left==right_min.ptr){
                right_min->parent->left= (right_min->left)? right_min->left:right_min->right;
                if(right_min->parent->left)
                    right_min->parent->left->parent=right_min->parent;
            }
            else if(right_min->parent->right==right_min.ptr){
                right_min->parent->right= (right_min->left)? right_min->left:right_min->right;
                if(right_min->parent->right)
                    right_min->parent->right->parent=right_min->parent;
            }
            delete right_min.ptr;
        }
        else{
            if(iter->parent->left==iter.ptr){
                iter->parent->left= (iter->left)? iter->left:iter->right;
                if(iter->parent->left)
                    iter->parent->left->parent=iter->parent;
            }
            else if(iter->parent->right==iter.ptr){
                iter->parent->right= (iter->left)? iter->left:iter->right;
                if(iter->parent->right)
                    iter->parent->right->parent=iter->parent;
            }
            delete iter.ptr;
        }

        return true;
    }

    bool erase(iterator v)
    {
        return erase(v->data);
    }

    template<typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(*first);
    }

    void empty()
    {
        make_empty(root);
        root.ptr=nullptr;
        size=0;
    }

private:
    iterator root;
    bCMP cmp;
    size_type size;
};


//递归的方式进行插入和删除
template <typename T,typename CMP=STL::less<T>,typename Distance=int>
class RecursiveTree{

protected:
    template <typename Type>
    struct Node{
        Type data;
        Node<Type> * parent;
        Node<Type> * left;
        Node<Type> * right;

        Node():parent(nullptr),left(nullptr),right(nullptr){
            //cout<<"Node()"<<endl;
        }

        Node(const Type& data):
            data(data),parent(nullptr),left(nullptr),right(nullptr){
            //cout<<"Node(const Type& data)"<<endl;
        }
        Node(Type&& data):
            data(std::move(data)),parent(nullptr),left(nullptr),right(nullptr){
            //cout<<"Node(Type&& data)"<<endl;
        }

        Node(const Node<Type>& node):
            data(node.data),parent(node.parent),
            left(node.left),right(node.right){
            //cout<<"Node(const Node<Type>& node)"<<endl;
        }

        Node(Node<Type>&& node):
            data(std::move(node.data)),parent(node.parent),
            left(node.left),right(node.right){
            //cout<<"Node(Node<Type>&& node)"<<endl;
        }
        ~Node(){
            //cout<<"~Node()"<<endl;
        }
    };

protected:

    using size_type=Distance;

    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_ref_type=T&&;

    using node_type=Node<T>;
    using ptr_node_type=Node<T>*;
    using ref_node_type=Node<T>&;
    using const_ref_node_type=const Node<T>&;
    using const_ptr_node_type=const Node<T>*;
    using const_ref_ptr_node_type=const Node<T>* &;
    using right_ref_node_type=Node<T>&&;

    using self_type=RecursiveTree<T,CMP>;
    using ref_self_type=RecursiveTree<T,CMP>&;
    using const_ref_self_type=const RecursiveTree<T,CMP>&;
    using right_ref_self_type=RecursiveTree<T,CMP>&&;

public:
    struct iterator:public base_iterator<bidirectional_iterator_tag,value_type,size_type>{
        ptr_node_type ptr;
        iterator():ptr(nullptr){}
        iterator(ptr_node_type  ptr):ptr(ptr){}
        iterator(const iterator & i):ptr(i.ptr){}
        ref_type operator*(){return ptr->data;}
        ptr_type operator->(){return &(ptr->data);}
        bool operator == (const iterator& i){return i.ptr==ptr;}
        bool operator != (const iterator& i){return i.ptr!=ptr;}

        const iterator& operator =(ptr_node_type p){ptr=p;return *this;}
        const iterator& operator =(iterator& i){ptr=i.ptr;return *this;}


        iterator operator ++()
        {
            increment();
            return *this;
        }

        iterator operator ++(int)
        {
            iterator tmp=*this;
            ++(*this);
            return tmp;
        }
        iterator operator --()
        {
            decrement();
            return *this;
        }

        iterator operator --(int)
        {
            iterator tmp=*this;
            --(*this);
            return tmp;
        }
    private:
        void increment()
        {
            if(ptr->right!=nullptr)
            {
                ptr=ptr->right;
                while(ptr->left!=nullptr)
                    ptr=ptr->left;
            }
            else
            {
                ptr_node_type y=ptr->parent;
                if(y==nullptr&&ptr->right==nullptr)
                    ptr=nullptr;
                else{
                    while(y!=nullptr&&ptr==y->right){
                        ptr=y;
                        y=y->parent;
                    }
                    if(ptr->right!=y)
                        ptr=y;
                }
            }
        }
        void decrement()
        {
            if(ptr->left!=nullptr)
            {
                ptr=ptr->left;
                while(ptr->right!=nullptr)
                    ptr=ptr->right;
            }
            else
            {
                ptr_node_type y=ptr->parent;
                if(y==nullptr&&ptr->left==nullptr)
                    ptr=nullptr;
                else{
                    while(y!=nullptr&&ptr==y->left){
                        ptr=y;
                        y=y->parent;
                    }
                    if(ptr->left!=y)
                        ptr=y;
                }
            }
        }
    };

    using reverse_iterator=reverse_iterator<iterator>;

    using const_iterator=const_iterator<iterator>;

protected:
    void _empty(ptr_node_type ptr)
    {
        if(ptr!=nullptr)
        {
            _empty(ptr->left);
            _empty(ptr->right);
            delete ptr;
        }
    }
    ptr_node_type _findMax(ptr_node_type ptr)const
    {
        if(ptr!=nullptr)
            while(ptr->right!=nullptr)
                ptr=ptr->right;
        return ptr;
    }
    ptr_node_type _findMin(ptr_node_type ptr)const
    {
        if(ptr!=nullptr)
            while(ptr->left!=nullptr)
                ptr=ptr->left;
        return ptr;
    }
    ptr_node_type _find(const_ref_type x,ptr_node_type ptr)
    {
        if(ptr==nullptr)
            return nullptr;
        if(cmp(x,ptr->data))
            return _find(x,ptr->left);
        else if(cmp(ptr->data,x))
            return _find(x,ptr->right);
        else
            return ptr;
    }

    ptr_node_type _insert(const_ref_type x,ptr_node_type ptr,ptr_node_type parent)
    {
        if(ptr==nullptr){
            ++size;
            ptr=new node_type(x);
            ptr->parent=parent;
        }
        else if(cmp(x,ptr->data)){
            ptr->left=_insert(x,ptr->left,ptr);
        }
        else if(cmp(ptr->data,x)){
            ptr->right=_insert(x,ptr->right,ptr);
        }
        return ptr;
    }

    ptr_node_type _insert(right_ref_type x,ptr_node_type ptr,ptr_node_type parent)
    {
        if(ptr==nullptr){
            ++size;
            ptr=new node_type(std::move(x));
            ptr->parent=parent;
        }
        else if(cmp(x,ptr->data))
            ptr->left=_insert(std::move(x),ptr->left,ptr);
        else if(cmp(ptr->data,x))
            ptr->right=_insert(std::move(x),ptr->right,ptr);
        return ptr;
    }

    bool _erase(const_ref_type x,ptr_node_type ptr)
    {

        if(ptr==nullptr)
            return false;
        else if(cmp(x,ptr->data)){
            return _erase(x,ptr->left);
        }
        else if(cmp(ptr->data,x)){
            return _erase(x,ptr->right);
        }
        else if(ptr->left&&ptr->right)
        {
            ptr_node_type tmpCell = _findMin(ptr->right);
            ptr->data=tmpCell->data;
            return _erase(ptr->data,ptr->right);
        }
        else
        {
            ptr_node_type tmpCell=ptr;
            if(!ptr->parent)
            {
                if(ptr->left!=nullptr){
                    root=ptr->left;
                    root->parent=nullptr;
                }
                else if(ptr->right!=nullptr)
                {
                    root=ptr->right;
                    root->parent=nullptr;
                }
                else{
                    root=nullptr;
                }
            }
            else if(ptr->parent->left==ptr)
            {
                if(ptr->left!=nullptr){
                    ptr->parent->left=ptr->left;
                    ptr->left->parent=ptr->parent;
                }
                else if(ptr->right!=nullptr)
                {
                    ptr->parent->left=ptr->right;
                    ptr->right->parent=ptr->parent;
                }
                else
                    ptr->parent->left=nullptr;
            }
            else if(ptr->parent->right==ptr)
            {
                if(ptr->left!=nullptr){
                    ptr->parent->right=ptr->left;
                    ptr->left->parent=ptr->parent;
                }
                else if(ptr->right!=nullptr)
                {
                    ptr->parent->right=ptr->right;
                    ptr->right->parent=ptr->parent;
                }
                else{
                    ptr->parent->right=nullptr;
                }
            }
            --size;
            delete tmpCell;
        }

        return true;
    }

public:
    RecursiveTree():root(nullptr),size(0){}
    RecursiveTree(const_ref_self_type tree):root(nullptr),size(0)
    {
        insert(tree.begin(),tree.end());
    }
    RecursiveTree(right_ref_self_type tree)
    {
        root=tree.root;
        size=tree.size;
        tree.root=nullptr;
        tree.size=0;
    }

    template<typename iter_type>
    RecursiveTree(iter_type first,iter_type last):root(nullptr),size(0)
    {
        for(;first!=last;++first)insert(*first);
    }


    const_ref_self_type operator =(const_ref_self_type tree)
    {
        empty();
        insert(tree.begin(),tree.end());
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type tree)
    {
        empty();
        root=tree.root;
        size=tree.size;
        tree.root=nullptr;
        tree.size=0;
        return *this;
    }

    ~RecursiveTree(){empty();}
public:
    iterator begin()const{return findMin();}
    iterator end()const{return iterator(nullptr);}
    reverse_iterator rbegin()const{return findMax();}
    reverse_iterator rend()const{return iterator(nullptr);}
    const_iterator cbegin()const{return findMin();}
    const_iterator cend()const{return iterator(nullptr);}
    size_type length()const {return size;}
    void empty(){_empty(root);root=nullptr;size=0;}
    bool isEmpty()const{return root!=nullptr;}
    bool count(const_ref_type x)const{return find(x)!=end();}
    iterator findMax()const{return _findMax(root);}

    iterator findMin()const{return _findMin(root);}

    iterator find(const_ref_type x)
    {
        ptr_node_type ptr=_find(x,root);
        if(ptr==nullptr)
            return iterator(nullptr);
        else
        {
            if(cmp_extend.equal_to(x,ptr->data))
                return iterator(ptr);
            else
                return iterator(nullptr);
        }
    }

    bool insert(const_ref_type x)
    {
        int i=size;
        root=_insert(x,root,nullptr);
        return size-i;
    }
    bool insert(right_ref_type x)
    {
        int i=size;
        root=_insert(std::move(x),root,nullptr);
        return size-i;
    }
    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {
        for(;first!=last;++first)insert(*first);
    }

    //Set or Map port
    bool insert_unique(const_ref_type x){return insert(x);}
    bool insert_unique(right_ref_type x){return insert(std::move(x));}

    bool erase(const_ref_type x){return _erase(x,root);}
    bool erase(iterator iter){return erase(iter.ptr->data);}
    template<typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(*first);
    }
private:
    ptr_node_type root;
    size_type size;
    CMP cmp;
    STL::Compare_extend<CMP> cmp_extend;
};

}

#endif // BINARYTREE_H
