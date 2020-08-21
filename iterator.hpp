#ifndef ITERATOR_H
#define ITERATOR_H


#include <iostream>


namespace STL{

struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag:public input_iterator_tag{};
struct bidirectional_iterator_tag:public forward_iterator_tag{};
struct random_access_iterator_tag:public bidirectional_iterator_tag{};

template<typename Category,
         typename T,
         typename Distance=ptrdiff_t,
         typename Pointer=T*,
         typename Reference=T&>
struct base_iterator{
    typedef Category        iterator_category;
    typedef T               element_type;
    typedef Distance        difference_type;
    typedef Pointer         pointer;
    typedef Reference       reference;
};

template <typename iterator,
          typename Category=typename iterator::iterator_category>
struct reverse_iterator;


// random_access_iterator_tag reverse_iterator
template <typename iterator>
struct reverse_iterator<iterator,random_access_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    reverse_iterator(){}
    reverse_iterator(const iterator& i):iter(i){}
    reverse_iterator(const reverse_iterator& i):iter(i.iter){}
    bool operator == (const reverse_iterator& i){return iter==i.iter;}
    bool operator != (const reverse_iterator& i){return iter!=i.iter;}
    const reverse_iterator& operator =(const iterator& i){iter=i;return *this;}
    const reverse_iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}

    reverse_iterator operator ++()
    {
        --iter;
        return *this;
    }
    reverse_iterator operator ++(int)
    {
        iterator tmp=*this;
        ++(*this);
        return tmp;
    }
    reverse_iterator operator --()
    {
        ++iter;
        return *this;
    }
    reverse_iterator operator --(int)
    {
        iterator tmp=*this;
        --(*this);
        return tmp;
    }

    reverse_iterator operator-(difference_type i)const
    {
        reverse_iterator t;
        t.iter=iter+i;
        return t;
    }
    reverse_iterator operator+(difference_type i)const
    {
        reverse_iterator t;
        t.iter=iter-i;
        return t;
    }
    difference_type operator -(const reverse_iterator & i)const{return i.iter-iter;}
    reference operator*(){return *iter;}
    pointer   operator->(){return &(*iter);}
};


// bidirectional_iterator_tag reverse_iterator
template <typename iterator>
struct reverse_iterator<iterator,bidirectional_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    reverse_iterator(){}
    reverse_iterator(const iterator& i):iter(i){}
    reverse_iterator(const reverse_iterator& i):iter(i.iter){}
    bool operator == (const reverse_iterator& i){return iter==i.iter;}
    bool operator != (const reverse_iterator& i){return iter!=i.iter;}
    const reverse_iterator& operator =(const iterator& i){iter=i;return *this;}
    const reverse_iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}

    reverse_iterator operator ++()
    {
        --iter;
        return *this;
    }
    reverse_iterator operator ++(int)
    {
        iterator tmp=*this;
        ++(*this);
        return tmp;
    }
    reverse_iterator operator --()
    {
        ++iter;
        return *this;
    }
    reverse_iterator operator --(int)
    {
        iterator tmp=*this;
        --(*this);
        return tmp;
    }
    reference operator*(){return *iter;}
    pointer   operator->(){return &(*iter);}
};

// forward_iterator_tag       reverse_iterator
template <typename iterator>
struct reverse_iterator<iterator,forward_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    reverse_iterator(){}
    reverse_iterator(const iterator& i):iter(i){}
    reverse_iterator(const reverse_iterator& i):iter(i.iter){}
    bool operator == (const reverse_iterator& i){return iter==i.iter;}
    bool operator != (const reverse_iterator& i){return iter!=i.iter;}
    const reverse_iterator& operator =(const iterator& i){iter=i;return *this;}
    const reverse_iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}

    reverse_iterator operator --()
    {
        ++iter;
        return *this;
    }
    reverse_iterator operator --(int)
    {
        iterator tmp=*this;
        --(*this);
        return tmp;
    }
    reference operator*(){return *iter;}
    pointer   operator->(){return &(*iter);}
};

template <typename iterator,
          typename Category=typename iterator::iterator_category>
struct const_iterator;
// random_access_iterator_tag const_iterator
template <typename iterator>
struct const_iterator<iterator,random_access_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    const_iterator(){}
    const_iterator(const iterator& i):iter(i){}
    const_iterator(const const_iterator& i):iter(i.iter){}

    bool operator == (const const_iterator& i){return iter==i.iter;}
    bool operator != (const const_iterator& i){return iter!=i.iter;}
    const const_iterator& operator =(const iterator& i){iter=i;return *this;}
    const const_iterator& operator =(const const_iterator& i){iter=i.iter;return *this;}

    const_iterator operator ++()
    {
        ++iter;
        return *this;
    }
    const_iterator operator ++(int)
    {
        const_iterator tmp=*this;
        ++(*this);
        return tmp;
    }
    const_iterator operator --()
    {
        --iter;
        return *this;
    }
    const_iterator operator --(int)
    {
        const_iterator tmp=*this;
        --(*this);
        return tmp;
    }
    const_iterator operator-(difference_type i)const
    {
        const_iterator t;
        t.iter=iter-i;
        return t;
    }
    const_iterator operator+(difference_type i)const
    {
        const_iterator t;
        t.iter=iter+i;
        return t;
    }
    difference_type operator-(const const_iterator & i)const{return iter-i.iter;}
    const element_type& operator*(){return *iter;}
    const element_type* operator->(){return &(*iter);}
};
// bidirectional_iterator_tag const_iterator
template <typename iterator>
struct const_iterator<iterator,bidirectional_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    const_iterator(){}
    const_iterator(const iterator& i):iter(i){}
    const_iterator(const const_iterator& i):iter(i.iter){}

    bool operator == (const const_iterator& i){return iter==i.iter;}
    bool operator != (const const_iterator& i){return iter!=i.iter;}
    const const_iterator& operator =(const iterator& i){iter=i;return *this;}
    const const_iterator& operator =(const const_iterator& i){iter=i.iter;return *this;}

    const_iterator operator ++()
    {
        ++iter;
        return *this;
    }
    const_iterator operator ++(int)
    {
        const_iterator tmp=*this;
        ++(*this);
        return tmp;
    }
    const_iterator operator --()
    {
        --iter;
        return *this;
    }
    const_iterator operator --(int)
    {
        const_iterator tmp=*this;
        --(*this);
        return tmp;
    }
    const element_type& operator*(){return *iter;}
    const element_type* operator->(){return &(*iter);}
};
// forward_iterator_tag const_iterator
template <typename iterator>
struct const_iterator<iterator,forward_iterator_tag>
{
    iterator iter;
    typedef typename iterator::iterator_category   iterator_category;
    typedef typename iterator::element_type        element_type;
    typedef typename iterator::difference_type     difference_type;
    typedef typename iterator::pointer             pointer;
    typedef typename iterator::reference           reference;

    const_iterator(){}
    const_iterator(const iterator& i):iter(i){}
    const_iterator(const const_iterator& i):iter(i.iter){}

    bool operator == (const const_iterator& i){return iter==i.iter;}
    bool operator != (const const_iterator& i){return iter!=i.iter;}
    const const_iterator& operator =(const iterator& i){iter=i;return *this;}
    const const_iterator& operator =(const const_iterator& i){iter=i.iter;return *this;}

    const_iterator operator ++()
    {
        ++iter;
        return *this;
    }
    const_iterator operator ++(int)
    {
        const_iterator tmp=*this;
        ++(*this);
        return tmp;
    }
    const element_type& operator*(){return *iter;}
    const element_type* operator->(){return &(*iter);}
};



template <typename I>
struct iterator_traits{
    typedef typename I::iterator_category   iterator_category;
    typedef typename I::element_type        element_type;
    typedef typename I::difference_type     difference_type;
    typedef typename I::pointer             pointer;
    typedef typename I::reference           reference;
};
template <typename T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef ptrdiff_t                   difference_type;
    typedef T                           element_type;
    typedef T*                          pointer;
    typedef T&                          reference;
};
template <typename T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag  iterator_category;
    typedef ptrdiff_t                   difference_type;
    typedef T                           element_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
};


template <typename ostream_type>class ostream_iterator;
template <typename ostream_type>class not_div_ostream_iterator;
template <typename istream_type>class istream_iterator;

template <typename ostream_type>
ostream_iterator<ostream_type> make_ostream_iterator(ostream_type& out,std::string str)
{
    return ostream_iterator<ostream_type>(out,str);
}

template <typename ostream_type>
not_div_ostream_iterator<ostream_type> make_ostream_iterator(ostream_type& out)
{
    return not_div_ostream_iterator<ostream_type>(out);
}

template <typename istream_type>
istream_iterator<istream_type> make_istream_iterator(istream_type& in)
{
    return istream_iterator<istream_type>(in);
}


template <typename ostream_type>
class ostream_iterator{
public:
    ostream_iterator(ostream_type& of,const std::string& str)
    {
        out=&of;
        this->str_div=str;
    }
    template <typename T>
    void operator =(const T& x)const{(*out)<<x<<str_div;}
    template <typename T>
    void operator ()(const T& x)const{(*out)<<x<<str_div;}
    ostream_iterator& operator *(){return *this;}
    ostream_iterator& operator ++(){return *this;}
    ostream_iterator& operator ++(int){return *this;}
    ostream_iterator& operator --(){return *this;}
    ostream_iterator& operator --(int){return *this;}
    ostream_iterator& operator +(int){return *this;}
    ostream_iterator& operator -(int){return *this;}

private:
    ostream_type * out;
    std::string str_div;

};

template <typename ostream_type>
class not_div_ostream_iterator{
public:
    not_div_ostream_iterator(ostream_type& of)
    {
        out=&of;
    }
    template <typename T>
    void operator =(const T& x)const{(*out)<<x;}
    template <typename T>
    void operator ()(const T& x)const{(*out)<<x;}
    not_div_ostream_iterator& operator *(){return *this;}
    not_div_ostream_iterator& operator ++(){return *this;}
    not_div_ostream_iterator& operator ++(int){return *this;}
    not_div_ostream_iterator& operator --(){return *this;}
    not_div_ostream_iterator& operator --(int){return *this;}
    not_div_ostream_iterator& operator +(int){return *this;}
    not_div_ostream_iterator& operator -(int){return *this;}

private:
    ostream_type * out;
};

template <typename istream_type>
class istream_iterator
{
public:
    istream_iterator(istream_type& in){this->in=&in;}
    template<typename T>
    void operator =(T& x){(*in)>>x;}

    istream_iterator& operator *(){return *this;}
    istream_iterator& operator ++(){return *this;}
    istream_iterator& operator ++(int){return *this;}
    istream_iterator& operator --(){return *this;}
    istream_iterator& operator --(int){return *this;}
    istream_iterator& operator +(int){return *this;}
    istream_iterator& operator -(int){return *this;}

private:
    istream_type * in;
};

}

#endif // ITERATOR_H
