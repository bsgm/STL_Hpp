#ifndef AVLTREE_H
#define AVLTREE_H


#include "linkedlist.hpp"
#include "function.hpp"
#include "iterator.hpp"
#include "pair.hpp"
namespace STL{

template <typename T,typename CMP=STL::less<T>>
class AvlTree
{
protected:
    template <typename Type>
    struct Node{
        STL::LinkedList<Type> data;
        bool is;
        int height;
        Node<Type> * parent;
        Node<Type> * left;
        Node<Type> * right;

        Node():data(),is(false),height(0),parent(nullptr),left(nullptr),right(nullptr){}

        Node(const Type& value):
            data(),is(false),height(0),parent(nullptr),left(nullptr),right(nullptr){
            data.push_back(value);}
        Node(Type&& value):
            data(),is(false),height(0),parent(nullptr),left(nullptr),right(nullptr){
            data.push_back(std::move(value));}
        Node(const Node<Type>& node):
            data(node.data),is(node.is),height(node.height),parent(node.parent),
            left(node.left),right(node.right){}
        Node(Node<Type>&& node):
            data(std::move(node.data)),is(node.is),height(node.height),parent(node.parent),
            left(node.left),right(node.right){}
        ~Node(){}
        void operator += (const Type& value){
            if(is){
                is=false;
                *(data.begin())=value;
            }
            else
                data.push_back(value);
        }
        void operator += (Type&& value){
            if(is){
                is=false;
                *(data.begin())=std::move(value);
            }
            else
                data.push_back(std::move(value));
            }

        void clear(){data.erase(data.begin()+1,data.end());is=true;}
        bool erase(int position)
        {
            if(is) return false;
            if(position>=0&&position<data.length())
            {
                if(data.length()==1)
                    is=true;
                else
                    data.erase(data.begin()+position);

                return true;
            }
            return false;
        }
    };

protected:
    using value_type=T;
    using ptr_type=T*;
    using ref_type=T&;
    using const_ref_type=const T &;
    using const_ptr_type=const T *;
    using right_ref_type=T&&;

    using size_type=unsigned long;

    using node_type=Node<T>;
    using ptr_node_type=Node<T>*;
    using ref_node_type=Node<T>&;
    using const_ref_node_type=const Node<T>&;
    using const_ptr_node_type=const Node<T>*;
    using right_ref_node_type=Node<T>&&;

    using self_type=AvlTree<T,CMP>;
    using ref_self_type=AvlTree<T,CMP>&;
    using const_ref_self_type=const AvlTree<T,CMP>&;
    using right_ref_self_type=AvlTree<T,CMP>&&;
public:
    struct iterator:public base_iterator<bidirectional_iterator_tag,value_type,size_type>{
        size_type index;
        ptr_node_type ptr;

        iterator():index(0),ptr(nullptr){}
        iterator(ptr_node_type p):index(0),ptr(p){}
        iterator(ptr_node_type p,size_type i):index(i),ptr(p){}
        iterator(const iterator& iter):index(iter.index),ptr(iter.ptr){}

        bool operator == (const iterator& i){return i.ptr==ptr&&i.index==index;}
        bool operator != (const iterator& i){return i.ptr!=ptr||i.index!=index;}
        const iterator& operator =(const ptr_node_type p){ptr=p;index=0;return *this;}
        const iterator& operator =(const iterator& i){ptr=i.ptr;index=i.index;return *this;}
        iterator operator ++()
        {
            if(index < ptr->data.length()-1)
            {
                ++index;
            }
            else
            {
                index=0;
                do{increment();}while(ptr&&ptr->is);
            }
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
            if(index > 0)
            {
                --index;
            }
            else
            {
                do{decrement();}while(ptr&&ptr->is);
                if(ptr)index=ptr->data.length()-1;
            }
            return *this;
        }
        iterator operator --(int)
        {
            iterator tmp=*this;
            --(*this);
            return tmp;
        }

        ref_type operator*(){return *(ptr->data.begin()+index);}
        ptr_type operator->(){return &(*(ptr->data.begin()+index));}
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
    using reverse_iterator       =typename STL::reverse_iterator<iterator>;
    using const_iterator         =typename STL::const_iterator<iterator>;
    using const_reverse_iterator =typename STL::const_iterator<reverse_iterator>;

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
        if(cmp(x,*(ptr->data.begin())))
            return _find(x,ptr->left);
        else if(cmp(*(ptr->data.begin()),x))
            return _find(x,ptr->right);
        else
            return ptr;
    }

    static int Height(ptr_node_type ptr)
    {
        return ptr?ptr->height:-1;
    }
    static int Max(int x,int y){return x<y?y:x;}
    static ptr_node_type SingleRotateWithLeft(ptr_node_type K2)
    {

        ptr_node_type K1;
        K1=K2->left;
        K2->left=K1->right;
        if(K2->left) K2->left->parent=K2;
        K1->right=K2;
        K1->parent=K2->parent;
        K2->parent=K1;
        K2->height=Max(Height(K2->left),Height(K2->right))+1;
        K1->height=Max(Height(K1->left),K2->height)+1;
        return K1;
    }
    static ptr_node_type SingleRotateWithRight(ptr_node_type K1)
    {
        ptr_node_type K2;
        K2=K1->right;
        K1->right=K2->left;
        if(K1->right)K1->right->parent=K1;
        K2->left=K1;
        K2->parent=K1->parent;
        K1->parent=K2;
        K1->height=Max(Height(K1->left),Height(K1->right))+1;
        K2->height=Max(Height(K2->right),K1->height)+1;
        return K2;
    }
    static ptr_node_type DoubleRotateWithLeft(ptr_node_type K3)
    {
        K3->left=SingleRotateWithRight(K3->left);
        if(K3->left) K3->left->parent=K3;
        return SingleRotateWithLeft(K3);
    }
    static ptr_node_type DoubleRotateWithRight(ptr_node_type K3)
    {
        K3->right=SingleRotateWithLeft(K3->right);
        if(K3->right) K3->right->parent=K3;
        return SingleRotateWithRight(K3);
    }

    ptr_node_type _insert_equal(const_ref_type x,ptr_node_type ptr)
    {
        if(ptr==nullptr)
        {   ++size;
            ptr=new node_type(x);
        }
        else if(cmp(x,*(ptr->data.begin())))
        {
            ptr->left=_insert_equal(x,ptr->left);
            ptr->left->parent=ptr;
            if(Height(ptr->left)-Height(ptr->right)==2){
                if(cmp(x,*(ptr->left->data.begin())))
                    ptr=SingleRotateWithLeft(ptr);
                else
                    ptr=DoubleRotateWithLeft(ptr);
            }

        }
        else if(cmp(*(ptr->data.begin()),x))
        {
            ptr->right=_insert_equal(x,ptr->right);
            ptr->right->parent=ptr;
            if(Height(ptr->right)-Height(ptr->left)==2){
                if(cmp(*(ptr->right->data.begin()),x))
                    ptr=SingleRotateWithRight(ptr);
                else
                    ptr=DoubleRotateWithRight(ptr);
            }
        }
        else{
            ++size;
            ptr->operator +=(x);
        }

        ptr->height=Max(Height(ptr->left),Height(ptr->right))+1;
        return ptr;
    }
    ptr_node_type _insert_unique(const_ref_type x,ptr_node_type ptr)
    {
        if(ptr==nullptr)
        {   ++size;
            ptr=new node_type(x);
        }
        else if(cmp(x,*(ptr->data.begin())))
        {
            ptr->left=_insert_unique(x,ptr->left);
            ptr->left->parent=ptr;
            if(Height(ptr->left)-Height(ptr->right)==2){
                if(cmp(x,*(ptr->left->data.begin())))
                    ptr=SingleRotateWithLeft(ptr);
                else
                    ptr=DoubleRotateWithLeft(ptr);
            }

        }
        else if(cmp(*(ptr->data.begin()),x))
        {
            ptr->right=_insert_unique(x,ptr->right);
            ptr->right->parent=ptr;
            if(Height(ptr->right)-Height(ptr->left)==2){
                if(cmp(*(ptr->right->data.begin()),x))
                    ptr=SingleRotateWithRight(ptr);
                else
                    ptr=DoubleRotateWithRight(ptr);
            }
        }
        ptr->height=Max(Height(ptr->left),Height(ptr->right))+1;
        return ptr;
    }


public:
    AvlTree() :size(0),root(nullptr){}
    AvlTree(const CMP & c) :size(0),root(nullptr),cmp(c){}
    AvlTree(const_ref_self_type tree):size(0),root(nullptr),cmp(tree.cmp)
    {
        insert(tree.begin(),tree.end());
    }
    AvlTree(right_ref_self_type tree)
    {
        root=tree.root;
        size=tree.size;
        cmp=tree.cmp;
        tree.root=nullptr;
        tree.size=0;
    }

    template<typename iter_type>
    AvlTree(iter_type first,iter_type last) :size(0),root(nullptr)
    {
        for(;first!=last;++first)insert_equal(*first);
    }

    const_ref_self_type operator =(const_ref_self_type tree)
    {
        empty();
        cmp=tree.cmp;
        insert(tree.begin(),tree.end());
        return *this;
    }
    const_ref_self_type operator =(right_ref_self_type tree)
    {
        empty();
        root=tree.root;
        size=tree.size;
        cmp=tree.cmp;
        tree.root=nullptr;
        tree.size=0;
        return *this;
    }

    ~AvlTree(){empty();}

    iterator begin()const{return findMin();}
    iterator  end()const {return iterator(nullptr);}

    reverse_iterator rbegin()const{return findMax();}
    reverse_iterator rend()const{return iterator(nullptr);}

    const_iterator cbegin()const{return findMin();}
    const_iterator cend()const{return iterator(nullptr);}

    const_reverse_iterator crbegin()const{return rbegin();}
    const_reverse_iterator crend()const{return rend();}

    bool isEmpty()const {return size;}
    void empty(){_empty(root);root=nullptr;size=0;}
    size_type length()const {return size;}
    size_type count(const_ref_type x)
    {
        ptr_node_type ptr=_find(x,root);
        if(ptr==nullptr)
            return 0;
        else
            return (ptr->is)?0:ptr->data.length();
    }

    iterator findMax()const{
        iterator iter(_findMax(root));
        if(iter.ptr&&iter.ptr->is)
            --iter;
        if(iter.ptr)iter.index=iter.ptr->data.length()-1;
        return iter;
    }

    iterator findMin()const{
        iterator iter(_findMin(root));
        if(iter.ptr&&iter.ptr->is)
            ++iter;
        return iter;
    }

    iterator find(const_ref_type x)
    {
        iterator iter(_find(x,root));
        if(iter.ptr&&iter.ptr->is)
            return end();
        return iter;
    }
    Pair<iterator,iterator> equal_range(const_ref_type x)
    {
        ptr_node_type ptr=_find(x,root);
        if(!ptr) return Pair<iterator,iterator>(end(),end());
        iterator first(ptr,0);
        iterator last(ptr,ptr->data.length()-1);
        ++last;
        return Pair<iterator,iterator>(first,last);
    }

    template<typename iter_type>
    void insert(iter_type first,iter_type last)
    {
        for(;first!=last;++first)insert_equal(*first);
    }

    void insert_equal(const_ref_type x){root=_insert_equal(x,root);}
    bool insert_unique(const_ref_type x)
    {
        int i=size;
        root=_insert_unique(x,root);
        return size-i;
    }

    bool erase(const_ref_type x)
    {
        iterator iter=find(x);
        if(iter!=end()){
            size-=iter.ptr->data.length();
            iter.ptr->clear();
            return true;
        }
        else
            return false;
    }
    bool erase(iterator position)
    {
        if(position!=end())
            return position.ptr->erase(position.index);
        return false;
    }
    template<typename iter_type>
    void erase(iter_type first,iter_type last)
    {
        for(;first!=last;++first)erase(*first);
    }
private:
    size_type size;
    ptr_node_type root;
    CMP cmp;
    STL::Compare_extend<CMP> cmp_extend;
};


}

#endif // AVLTREE_H
