#ifndef BASIC_META_H
#define BASIC_META_H

/**
 * <basicmeta.hpp>
 *
 * //获取Args中第N个类型
 * template<int N, typename... Args>struct GetType;
 * //计算Args的类型数量
 * template<typename...Args>struct Length;
 * //根据bool值选择一个类型
 * template <bool i,typename Arg1,typename Arg2>struct conditional;
 * //定义一个T型常量
 * template <typename T,T v>struct integral_constant;
 * //判断一个类型是否为const型
 * template <typename T> struct is_const;
 * //判断两个类型是否相同
 * template <typename T,typename V> struct is_same;
 * //判断类型是否为指针
 * template <typename T> struct is_pointer;
 *
 */
namespace STL{

template<int N, typename... Args>struct GetType;

template<int N, typename T, typename... Args>
struct GetType<N,T,Args...>
{
    using type = typename GetType<N - 1, Args...>::type;
};
template<typename T, typename... Args>
struct GetType<0, T, Args...>
{
    using type = T;
};
template<int N, typename T>
struct GetType<N, T>
{
    using type = T;
};
template<typename T>
struct GetType<0, T>
{
    using type = T;
};

template<typename...Args>struct Length;

template<typename T,typename...Args>
struct Length<T,Args...>{
    enum{size=1+Length<Args...>::size};
};
template<typename T>
struct Length<T>{
    enum{size=1};
};
template<>struct Length<>{enum{size=0};};

template <bool i,typename Arg1,typename Arg2>
struct conditional;
template <typename Arg1,typename Arg2>
struct conditional<true,Arg1,Arg2>{using type=Arg1;};
template <typename Arg1,typename Arg2>
struct conditional<false,Arg1,Arg2>{using type=Arg2;};

template <typename T,T v>
struct integral_constant{static constexpr T value=v;};

template <typename T>
struct is_const:public integral_constant<bool,false>{};
template <typename T>
struct is_const<T const>:public integral_constant<bool,true>{};

template <typename T,typename V>
struct is_same:public integral_constant<bool,false>{};

template <typename T>
struct is_same<T,T>:public integral_constant<bool,true>{};

template <typename T>
struct add_const{
    using type=typename conditional<is_const<T>::value,T,T const>::type;
};

template <typename T>
struct is_pointer:public integral_constant<bool,false>{};
template <typename T>
struct is_pointer<T*>:public integral_constant<bool,true>{};

}

#endif // BASIC_META_H
