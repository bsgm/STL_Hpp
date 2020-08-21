#ifndef DET_HPP
#define DET_HPP

#include <iostream>
#include "vector.hpp"

namespace STL{

template<unsigned int N,typename value_type=int>
class Det
{
protected:
    using size_type=unsigned int;

    using self_type=Det<N,value_type>;

    using data_type=Vector<Vector<value_type,size_type>,size_type>;

    static constexpr size_type rank=N;

protected:
    void initializer_det()
    {
        map.resize(N);
        for(size_type i=0;i<N;++i) map[i].resize(N);
    }
    static void initializer_det(data_type & data,size_type n)
    {
        data.resize(n);
        for(size_type i=0;i<n;++i) data[i].resize(n);
    }

    void set_det(std::initializer_list<value_type>& list)
    {
        auto iter=list.begin();
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
            {
                map[i][j]=*iter;
                ++iter;
            }
    }

    static data_type cofactor(data_type & arr,size_type x,size_type y)
    {
        data_type result;
        initializer_det(result,N-1);
        size_type ri=0;
        size_type rj=0;
        for(size_type i=0;i<N;i++)
        {
            if(i!=x)
            {
                for(size_type j=0;j<N;j++)
                {
                    if(j!=y)
                    {
                        result[ri][rj]=arr[i][j];
                        ++rj;
                    }
                }
                rj=0;
                ++ri;
            }
        }

        return result;
    }

    template <typename T>
    static T determinant(Vector<Vector<T,size_type>,size_type> arr)
    {
        size_type n=arr.length();
        if(n==2)
        {
            return arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0];
        }
        else if(n==1)
        {
            return arr[0][0];
        }
        else
        {
            T sum=0;
            for(size_type i=0;i<n;i++)
            {
                if(i%2)
                    sum+=(-1)*arr[i][0]*determinant(cofactor(arr,i,0));
                else
                    sum+=arr[i][0]*determinant(cofactor(arr,i,0));
            }
            return sum;
        }

    }

public: // constructor

    Det(){initializer_det();}

    Det(std::initializer_list<value_type>&& list)
    {
         initializer_det();
         set_det(list);
    }
    Det(const std::initializer_list<value_type>& list)
    {
         initializer_det();
         set_det(list);
    }

    template<typename InputIterator>
    Det(InputIterator first,InputIterator last)
    {
        initializer_det();
        size_type i=0;
        size_type j=0;
        while(first!=last&&i<N){
            map[i][j]=*first;
            ++first;
            ++j;
            if(j>=N) {j=0; ++i;}
        }
    }

    Det(const self_type& other) {map=other.map;}
    Det(self_type&& other) {map=std::move(other.map);}
    Det(data_type data){map=data;}

public: //operator
    const self_type& operator =(const self_type& other){map=other.map;return *this;}
    const self_type& operator =(self_type&& other){map=std::move(other.map);return *this;}

    self_type operator + ( self_type& other)
    {
        data_type result=map;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                result[i][j]+=other.map[i][j];
        return self_type(result);
    }
    self_type operator - ( self_type& other)
    {
        data_type result=map;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                result[i][j]-=other.map[i][j];
        return self_type(result);
    }

    const self_type& operator += ( self_type& other)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                map[i][j]+=other.map[i][j];
        return *this;
    }
    const self_type& operator -= ( self_type& other)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                map[i][j]-=other.map[i][j];
        return *this;
    }

    self_type operator  * (value_type x)
    {
        data_type result=map;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                result[i][j]*=x;
        return self_type(result);
    }
    self_type operator  / (value_type x)
    {
        data_type result=map;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                result[i][j]/=x;
        return self_type(result);
    }

    const self_type& operator *= (value_type x)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                map[i][j]*=x;
        return *this;
    }
    const self_type& operator /= (value_type x)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
                map[i][j]/=x;
        return *this;
    }

public:

    value_type& at(size_type i,size_type j)
    {
        return map[i][j];
    }



    Det<N-1,value_type> cofactor(size_type x,size_type y)
    {
        data_type result;
        initializer_det(result,N-1);
        size_type ri=0;
        size_type rj=0;
        for(size_type i=0;i<N;i++)
        {
            if(i!=x)
            {
                for(size_type j=0;j<N;j++)
                {
                    if(j!=y)
                    {
                        result[ri][rj]=map[i][j];
                        ++rj;
                    }
                }
                rj=0;
                ++ri;
            }
        }
        return Det<N-1,value_type>(result);
    }

    value_type value()
    {
        return determinant(map);
    }

public: // friend function
    friend std::ostream &  operator <<
    (std::ostream& out,const self_type & self)
    {
        STL::for_each(self.map.begin(),self.map.end(),[](Vector<value_type,size_type>& v){
            STL::out_foreach(v.begin(),v.end());
        });
        return out;
    }

private:
    data_type map;
};
}
#endif // DET_HPP
