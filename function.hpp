#ifndef FUNCTION_H
#define FUNCTION_H
/**
 * <function.hpp>
 *
 * Adaptable
 *          unary_function
 *          binary_function
 * Arithmetic
 *          plus
 *          minus
 *          multiplies
 *          divdes
 *          modulus
 *          negate
 *          count
 * Relational
 *          equal_to
 *          not_equal_to
 *          greater
 *          less
 *          greater_equal
 *          less_equal
 * RelationalExtend
 *          less_extend
 *          Compare_extend
 *                      make_Compare_extend
 * Logical
 *          logical_and
 *          logical_or
 *          logical_not
 * Function
 *          Functor
 *                      make_functor
 * binder1st
 *          bind1st
 * binder2st
 *          bind2st
 *
 */


#include <iostream>

namespace STL{

/************* Adaptable **************/

template <typename Arg,typename Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};

template <typename Arg1,typename Arg2,typename Result>
struct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};



/**************Arithmetic***************/

template <typename T>
struct plus:public binary_function<T,T,T>{
    T operator()(const T& x,const T& y)const{return x+y;}
};
template <typename T>
struct minus:public binary_function<T,T,T>{
    T operator()(const T& x,const T& y)const{return x-y;}
};
template <typename T>
struct multiplies:public binary_function<T,T,T>{
    T operator()(const T& x,const T& y)const{return x*y;}
};
template <typename T>
struct divdes:public binary_function<T,T,T>{
    T operator()(const T& x,const T& y)const{return x/y;}
};
template <typename T>
struct modulus:public binary_function<T,T,T>{
    T operator()(const T& x,const T& y)const{return x%y;}
};
template <typename T>
struct negate:public unary_function<T,T>{
    T operator()(const T& x)const{return -x;}
};
template <typename T>
struct identity:public unary_function<T,T>{
    const T& operator()(const T& x)const{return x;}
};

/**************Relational***************/

template <typename T>
struct equal_to:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x==y;}
};
template <typename T>
struct not_equal_to:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x!=y;}
};
template <typename T>
struct greater:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x>y;}
};
template <typename T>
struct less:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x<y;}
};
template <typename T>
struct greater_equal:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x>=y;}
};
template <typename T>
struct less_equal:public binary_function<T,T,bool>{
    bool operator()(const T& x,const T& y)const{return x<=y;}
};
/**************RelationalExtend***************/
template <typename Basic>
struct less_extend:public Basic{
public:
    less_extend(){}
    template <typename ...Args>
    less_extend(const Args&... args):Basic(args...){}
    template <typename ...Args>
    less_extend(Args&&... args):Basic(args...){}

    bool operator ==(const less_extend<Basic>& x){return !(*this<x || *this>x);}
    bool operator !=(const less_extend<Basic>& x){return !(*this == x);}
    bool operator <=(const less_extend<Basic>& x){return !(*this > x);}
    bool operator >=(const less_extend<Basic>& x){return ! (*this < x);}
    bool operator > (const less_extend<Basic>& x){return x < *this;}
};

template <typename Compare>
class Compare_extend{
public:
    Compare_extend(){}
    Compare_extend(const Compare& cmp):cmp(cmp){}
    Compare_extend(Compare&& cmp):cmp(std::move(cmp)){}

    template <typename T>
    bool less(const T& x,const T& y){return cmp(x,y);}
    template <typename T>
    bool greater(const T& x,const T& y){return cmp(y,x);}
    template <typename T>
    bool equal_to(const T& x,const T& y){return !(cmp(x,y) || cmp(y,x));}
    template <typename T>
    bool not_equal_to(const T& x,const T& y){return (cmp(x,y) || cmp(y,x));}
    template <typename T>
    bool greater_equal(const T& x,const T& y){return !cmp(x,y);}
    template <typename T>
    bool less_equal(const T& x,const T& y){return !cmp(y,x);}

private:
    Compare cmp;
};

template <typename T>
Compare_extend<T> make_Compare_extend(T cmp)
{
    return Compare_extend<T>(cmp);
}

/**************Logical***************/

template <typename T>
struct logical_and:public binary_function<T,T,bool>{
    bool operator ()(const T& x,const T&y)const{return x&&y;}
};
template <typename T>
struct logical_or:public binary_function<T,T,bool>{
    bool operator ()(const T& x,const T&y)const{return x||y;}
};
template <typename T>
struct logical_not:public unary_function<T,bool>{
    bool operator ()(const T& x)const{return !x;}
};


/**************Function***************/
template <typename Result, typename... Args>
class  Functor
{
public:
    using result_type=Result;
public:
    Functor(){}
    Functor(Result  (*f)(Args...) ):function(f) {}

    Result operator()(Args&&... args)
    {
        return (*function)(std::forward<Args>(args) ...);
    }
public:
    Result  (*function)(Args...);
};

template <typename Result, typename... Args>
Functor<Result, Args...> make_functor(Result (*f)(Args...))
{
    return Functor<Result, Args...>(f);
}

template <typename Operation>
class binder1st:
        public unary_function<typename Operation::first_argument_type,
        typename Operation::result_type>{
protected:
    Operation op;
    typename Operation::first_argument_type value;

public: //constructor
    binder1st(const Operation& x,
              const typename Operation::first_argument_type& y):
        op(x),value(y){}
public:
    typename Operation::result_type
    operator ()(const typename Operation::second_argument_type& x)const
    {
        return op(value,x);
    }
};

template <typename Operation>
class binder2st:
        public unary_function<typename Operation::second_argument_type,
        typename Operation::result_type>{
protected:
    Operation op;
    typename Operation::second_argument_type value;

public: //constructor
    binder2st(const Operation& x,
              const typename Operation::second_argument_type& y):
        op(x),value(y){}
public:
    typename Operation::result_type
    operator ()(const typename Operation::first_argument_type& x)const
    {
        return op(x,value);
    }
};

template <typename Operation,typename T>
inline binder1st<Operation> bind1st(const Operation& op,const T& x)
{
    typedef typename Operation::first_argument_type arg1_type;
    return binder1st<Operation>(op,arg1_type(x));
}

template <typename Operation,typename T>
inline binder2st<Operation> bind2st(const Operation& op,const T& x)
{
    typedef typename Operation::second_argument_type arg2_type;
    return binder2st<Operation>(op,arg2_type(x));
}



}



#endif // FUNCTION_H
