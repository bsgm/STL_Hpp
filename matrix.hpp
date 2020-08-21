#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include "vector.hpp"

namespace STL{
template <unsigned int __N,unsigned int __M,typename value_type> class Matrix;


template <unsigned int N,unsigned int M,typename value_type>
Matrix<M,N,value_type> Matrix_T(Matrix<N,M,value_type>& matrix)
{
    Matrix<M,N,value_type> result;

    for(unsigned int i=0;i<N;++i)
        for(unsigned int j=0;j<M;++j)
            result.at(j,i)=matrix.at(i,j);
    return result;
}

template <unsigned int __N,unsigned int __M,typename value_type=int>
class Matrix
{
protected:
    using size_type=unsigned int;
    using data_type=Vector<Vector<value_type,size_type>,size_type>;

    using self_type=Matrix<__N,__M,value_type>;

    static constexpr size_type N=__N;
    static constexpr size_type M=__M;

protected:

    void initializer_matrix()
    {
        map.resize(N);
        for(size_type i=0;i<N;++i)map[i].resize(M);
    }

    void set_matrix(std::initializer_list<value_type>& list)
    {
        auto iter=list.begin();
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
            {
                map[i][j]=*iter;
                ++iter;
            }
    }

public: // constructor
    Matrix() {initializer_matrix();}

    Matrix(std::initializer_list<value_type>&& list)
    {
        initializer_matrix();
        set_matrix(list);
    }

    Matrix(const self_type& other){map=other.map;}

public: //operator

    template <unsigned int X>
    Matrix<N,X,value_type>
    operator * (Matrix<M,X>& matrix)
    {
        Matrix<N,X,value_type> result;

        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<X;j++)
            {
                value_type sum=0;
                for(size_type x=0;x<M;++x)
                    sum+= at(i,x)*matrix.at(x,j);
                result.at(i,j)=sum;
            }

        return result;
    }

    self_type operator *(value_type x)
    {
        self_type result;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                result.at(i,j)=at(i,j)*x;
        return result;
    }
    self_type operator /(value_type x)
    {
        self_type result;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                result.at(i,j)=at(i,j)/x;
        return result;
    }
    self_type operator +(self_type& other)
    {
        self_type result;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                result.at(i,j)=at(i,j)+other.at(i,j);
        return result;
    }
    self_type operator -(self_type& other)
    {
        self_type result;
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                result.at(i,j)=at(i,j)-other.at(i,j);
        return result;
    }

    const self_type& operator *=(value_type x)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                at(i,j)=at(i,j)*x;
        return *this;
    }
    const self_type& operator /=(value_type x)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                at(i,j)=at(i,j)/x;
        return *this;
    }
    const self_type& operator +=(self_type& other)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                at(i,j)=at(i,j)+other.at(i,j);
        return *this;
    }
    const self_type& operator -=(self_type& other)
    {
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<M;++j)
                at(i,j)=at(i,j)-other.at(i,j);
        return *this;
    }


public:
    value_type& at(size_type i,size_type j)
    {
        return map[i][j];
    }

public: //friend function
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

template <unsigned int __N,typename value_type>
class Matrix<__N,__N,value_type>
{
protected:
    using size_type=unsigned int;
    using data_type=Vector<Vector<value_type,size_type>,size_type>;

    using self_type=Matrix<__N,__N,value_type>;

    static constexpr size_type N=__N;

protected:

    void initializer_matrix()
    {
        map.resize(N);
        for(size_type i=0;i<N;++i)map[i].resize(N);
    }
    void set_matrix(std::initializer_list<value_type>& list)
    {
        auto iter=list.begin();
        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<N;++j)
            {
                map[i][j]=*iter;
                ++iter;
            }
    }
public:
    Matrix() {initializer_matrix();}

    Matrix(std::initializer_list<value_type>&& list)
    {
        initializer_matrix();
        set_matrix(list);
    }

    Matrix(const self_type& other){map=other.map;}

public: //operator

    template <unsigned int X>
    Matrix<N,X,value_type>
    operator * (Matrix<N,X>& matrix)
    {
        Matrix<N,X,value_type> result;

        for(size_type i=0;i<N;++i)
            for(size_type j=0;j<X;j++)
            {
                value_type sum=0;
                for(size_type x=0;x<N;++x)
                    sum+= at(i,x)*matrix.at(x,j);
                result.at(i,j)=sum;
            }

        return result;
    }

public:
    value_type& at(size_type i,size_type j)
    {
        return map[i][j];
    }
public: //friend function
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

#endif // MATRIX_HPP
