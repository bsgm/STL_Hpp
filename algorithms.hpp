#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/**
 * <algorithms.hpp>
 *
 * for_each
 * out_foreach
 * copy
 * copy_n
 * copy_if
 * shell_sort
 * insert_sort
 * swap
 * purity_quick_sort
 * quick_sort
 * find
 * count
 * binary_search
 * Max
 * Min
 * Max_element
 * Min_element
 * replace
 * reverse
 * swap_ranges
 * transform
 * distance
 */
#include <iostream>
#include "function.hpp"
#include "iterator.hpp"
namespace STL
{

    const static int Cutoff =15;

    template<typename iterator,typename UnaryOperator>
    void for_each(iterator first, iterator last,const UnaryOperator& f)
    {
        for(iterator i=first;i!=last;++i)f(*i);
    }

    template<typename iterator>
    void out_foreach(iterator begin,iterator end,std::string title="",std::string str=" ",int n=-1)
    {
        std::cout<<title;
        int j=1;
        for(iterator i=begin;i!=end;++i,++j){
            std::cout<<*i<<str;
            if(j==n)
            {
                std::cout<<std::endl;
                j=0;
            }
        }
        std::cout<<std::endl;
    }

    template<typename InputIterator,typename OutputIterator>
    void copy(InputIterator first,InputIterator last,OutputIterator result)
    {
        if(first>=result)
            for(InputIterator i=first;i!=last;++i,++result)
                *result=*i;
        else{
            if(last==first)
                return ;
            for(InputIterator i=result+(last-first)-1;i!=result;--i,--last)
                *i=*(last-1);
            *result=*(first);
        }
    }

    template<typename InputIterator,typename OutputIterator>
    void copy_n(InputIterator first,InputIterator last,OutputIterator result)
    {
        for(;first!=last;++first,++result) *result=*first;
    }

    template<typename InputIterator,typename OutputIterator,typename Function>
    void copy_if(InputIterator first,InputIterator last,OutputIterator result,const Function& f)
    {
        for(;first!=last;++first)if(f(*first)) *(result++)=*first;
    }

    template<typename iterator>
    void shell_sort(iterator first,iterator last)
    {
        int i,j,increment;
        int N=last-first;
        auto tmp=*first;

        for(increment=N/2;increment>0;increment /=2)
            for(i=increment;i<N;i++)
            {
                tmp = *(first+i);
                for(j=i;j>=increment;j-=increment)
                    if(tmp < *(first+(j-increment)))
                        *(first+j)=*(first+(j-increment));
                    else
                        break;
                *(first+j)=tmp;
            }
    }

    template<typename iterator,typename BinaryOperator>
    void shell_sort(iterator first,iterator last,const BinaryOperator& f)
    {
        int i,j,increment;
        int N=last-first;
        auto tmp=*first;

        for(increment=N/2;increment>0;increment /=2)
            for(i=increment;i<N;i++)
            {
                tmp = *(first+i);
                for(j=i;j>=increment;j-=increment)
                    if(f(tmp,*(first+(j-increment))))
                        *(first+j)=*(first+(j-increment));
                    else
                        break;
                *(first+j)=tmp;
            }
    }


    template<typename iterator>
    void insert_sort(iterator first,iterator last)
    {
        iterator i,j;
        auto tmp=*first;
        for(i=first+1;i!=last;++i)
        {
            tmp=*i;
            for(j=i;j>first&&*(j-1)>tmp;--j)
                *j=*(j-1);
            *j=tmp;
        }
    }

    template<typename iterator,typename BinaryOperator>
    void insert_sort(iterator first, iterator last,const BinaryOperator& f)
    {
        iterator i,j;
        auto t=*first;
        for(i=first+1;i!=last;++i)
        {
            t=*i;
            for(j=i;j>first&&f(t,*(j-1));--j)
                *j=*(j-1);
            *j=t;
        }
    }

    template<typename T>
    inline void swap(T& x,T& y)
    {
        T t = std::move(x);
        x = std::move(y);
        y = std::move(t);
    }

    template<typename iterator>
    inline iterator median(iterator& first,iterator& last)
    {
        iterator center=first+(last-first)/2;

        if(*center<*first){
            if(*first<*(last-1))
                STL::swap(*first,*(last-1));
            else if(*(last-1)<*center)
                STL::swap(*center,*(last-1));
            else
                return (last-1);
        }
        else{
            if(*(last-1)<*first)
                STL::swap(*first,*(last-1));
            else if(*center<*(last-1))
                STL::swap(*center,*(last-1));
            else
                return (last-1);
        }
        return (last-1);
    }

    template<typename iterator,typename BinaryOperator>
    inline iterator median(iterator& first,iterator& last,const BinaryOperator& f)
    {
        iterator center=first+(last-first)/2;

        if(f(*center,*first)){
            if(f(*first,*(last-1)))
                STL::swap(*first,*(last-1));
            else if(f(*(last-1),*center))
                STL::swap(*center,*(last-1));
            else
                return (last-1);
        }
        else{
            if(f(*(last-1),*first))
                STL::swap(*first,*(last-1));
            else if(f(*center,*(last-1)))
                STL::swap(*center,*(last-1));
            else
                return (last-1);
        }
        return (last-1);
    }

    template<typename iterator>
    inline iterator partition(iterator& first,iterator& last)
    {
        iterator div=median(first,last);
        iterator i=first-1;
        iterator j=last-1;
        for(;;)
        {
            while(*(++i)<*div);
            while(*(--j)>*div);
            if(i<j)
                STL::swap(*i,*j);
            else
                break;
        }
        STL::swap(*i,*(last-1));

        return i;
    }

    template<typename iterator,typename BinaryOperator>
    inline iterator partition(iterator& first,iterator& last,const BinaryOperator& f)
    {
        iterator div=median(first,last,f);
        iterator i=first-1;
        iterator j=last-1;
        for(;;)
        {
            while(f(*(++i),*div));
            while(f(*div,*(--j)));
            if(i<j)
                STL::swap(*i,*j);
            else
                break;
        }
        STL::swap(*i,*(last-1));

        return i;
    }

    template<typename iterator>
    void purity_quick_sort(iterator first,iterator last)
    {
        if(last-first<=1)
            return ;
        iterator i=partition(first,last);
        purity_quick_sort(first,i);
        purity_quick_sort(i+1,last);
    }

    template<typename iterator,typename BinaryOperator>
    void purity_quick_sort(iterator first,iterator last,const BinaryOperator & f)
    {
        if(last-first<=1)
            return ;
        iterator i=partition(first,last,f);
        purity_quick_sort(first,i,f);
        purity_quick_sort(i+1,last,f);
    }

    template<typename iterator>
    void quick_sort(iterator first,iterator last)
    {
        if(last-first>=Cutoff)
        {
            iterator i=partition(first,last);
            quick_sort(first,i);
            quick_sort(i+1,last);
        }
        else if(last-first>=1)
            insert_sort(first,last);
    }

    template<typename iterator,typename BinaryOperator>
    void quick_sort(iterator first,iterator last,const BinaryOperator& f)
    {
        if(last-first>=Cutoff)
        {
            iterator i=partition(first,last,f);
            quick_sort(first,i,f);
            quick_sort(i+1,last,f);
        }
        else if(last-first>=1)
            insert_sort(first,last,f);
    }

    template<typename iterator,typename T,typename CMP=STL::equal_to<T>>
    iterator find(iterator first,iterator last,const T& x,const CMP& cmp=CMP())
    {
        for(;first!=last;++first)
            if(cmp(*first,x))
                return first;
        return last;
    }

    template<typename iterator,typename T,typename CMP=STL::equal_to<T>>
    int count(iterator first,iterator last,const T& x,const CMP& cmp=CMP())
    {
        int size=0;
        for(;first!=last;++first)
            if(cmp(x,*first))
                ++size;
        return size;
    }


    template<typename iterator,typename T>
    iterator binary_search(iterator first,iterator last,const T& x)
    {
        if(*(last-1) >= *first)
            return _increase_binary_search(first,last,x);
        else
            return _decrease_binary_search(first,last,x);
    }
    template<typename iterator,typename T>
    inline iterator _increase_binary_search(iterator first,iterator last,const T& x)
    {
        iterator right=first;
        iterator left=last-1;
        iterator mid;
        while(right<=left)
        {
            mid=right+(left-right)/2;
            if(*mid > x)
                left=mid-1;
            else if(*mid < x)
                right=mid+1;
            else
                return mid;
        }
        return last;
    }
    template<typename iterator,typename T>
    inline iterator _decrease_binary_search(iterator first,iterator last,const T& x)
    {
        iterator right=first;
        iterator left=last-1;
        iterator mid;
        while(right<=left)
        {
            mid=right+(left-right)/2;
            if(*mid < x)
                left=mid-1;
            else if(*mid > x)
                right=mid+1;
            else
                return mid;
        }
        return last;
    }

    template<typename T,typename CMP=STL::less<T>>
    const T & Max(const T x,const T y,const CMP& cmp=CMP()){return cmp(x,y)?y:x;}
    template<typename T,typename CMP=STL::less<T>>
    const T & Min(const T x,const T y,const CMP& cmp=CMP()){return cmp(x,y)?x:y;}

    template<typename iterator>
    iterator Max_element(iterator first,iterator last)
    {
        iterator position=first;
        for(++first;first!=last;++first)
            if(*position<*first)
                position=first;
        return position;
    }
    template<typename iterator,typename BinaryOperator>
    iterator Max_element(iterator first,iterator last,const BinaryOperator& f)
    {
        iterator position=first;
        for(++first;first!=last;++first)
            if(f(*first,*position))
                position=first;
        return position;
    }
    template<typename iterator>
    iterator Min_element(iterator first,iterator last)
    {
        iterator position=first;
        for(++first;first!=last;++first)
            if(*position>*first)
                position=first;
        return position;
    }
    template<typename iterator,typename BinaryOperator>
    iterator Min_element(iterator first,iterator last,const BinaryOperator& f)
    {
        iterator position=first;
        for(++first;first!=last;++first)
            if(f(*position,*first))
                position=first;
        return position;
    }

    template<typename iterator,typename T>
    void replace(iterator first,iterator last,const T& x,const T& y)
    {
        for(;first!=last;++first)if(*first==x) *first=y;
    }
    template<typename iterator,typename T,typename UnaryOperator>
    void replace(iterator first,iterator last,const UnaryOperator& f,const T& y)
    {
        for(;first!=last;++first)if(f(*first)) *first=y;
    }
    template<typename iterator>
    void reverse(iterator first,iterator last)
    {
        for(--last;first!=last && first!=last+1;++first,--last)STL::swap(*first,*last);
    }

    template<typename InputIterator,typename OutputIterator>
    void swap_ranges(InputIterator first,InputIterator last,OutputIterator result)
    {
        for(;first!=last;++first,++result)STL::swap(*first,*result);
    }
    template<typename InputIterator,typename OutputIterator,typename UnaryOperator>
    void transform(InputIterator first,InputIterator last,OutputIterator result,const UnaryOperator& op)
    {
        for(;first!=last;++first,++result) *result=op(*first);
    }
    template<typename InputIterator,typename OutputIterator,typename BinaryOperator>
    void transform(InputIterator first1,InputIterator last,InputIterator first2,OutputIterator result,const BinaryOperator& op)
    {
        for(;first1!=last;++first1,++first2,++result) *result=op(*first1,*first2);
    }

    template<typename InputIterator>
    inline typename STL::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first,InputIterator last)
    {
        return _distance(first,last,typename iterator_traits<InputIterator>::iterator_category());
    }
    template<typename InputIterator>
    inline typename STL::iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first,InputIterator last,STL::random_access_iterator_tag)
    {
        return last-first;
    }
    template<typename InputIterator>
    inline typename STL::iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first,InputIterator last,STL::input_iterator_tag)
    {
        typename STL::iterator_traits<InputIterator>::difference_type n=0;
        for(;first!=last;++first,++n);
        return n;
    }

    template <typename InputIterator,typename Distance>
    void advance(InputIterator& i,Distance n)
    {
        advance(i,n,typename iterator_traits<InputIterator>::iterator_category());
    }
    template <typename InputIterator,typename Distance>
    void advance(InputIterator& i,Distance n,STL::random_access_iterator_tag)
    {
        i+=n;
    }
    template <typename InputIterator,typename Distance>
    void advance(InputIterator& i,Distance n,STL::bidirectional_iterator_tag)
    {
        if(n>=0)
            for(;n>0;--n,++i);
        else
            for(;n<0;++n,--i);
    }
    template <typename InputIterator,typename Distance>
    void advance(InputIterator& i,Distance n,STL::forward_iterator_tag)
    {
        for(;n>0;--n,++i);
    }


}
#endif // ALGORITHMS_H
