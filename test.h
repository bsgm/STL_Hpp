#ifndef TEST_H
#define TEST_H

/**

using STL::Vector;
template <typename T>
Vector<Vector<T>> cofactor(Vector<Vector<T>> arr,int x,int y)
{
    int N=arr.length();
    Vector<T> tmp;
    tmp.resize(N-1);
    Vector<Vector<T>> result;
    result.resize(N-1);
    for(auto i=result.begin();i!=result.end();++i) *i=tmp;

    int ri=0;
    int rj=0;
    for(int i=0;i<N;i++)
    {
        if(i!=x)
        {
            for(int j=0;j<N;j++)
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
T determinant(Vector<Vector<T>> arr)
{
    int N=arr.length();
    if(N==2)
    {
        return arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0];
    }
    else if(N==1)
    {
        return arr[0][0];
    }
    else
    {
        T sum=0;
        for(int i=0;i<N;i++)
        {
            if(i%2)
                sum+=(-1)*arr[i][0]*determinant(cofactor(arr,i,0));
            else
                sum+=arr[i][0]*determinant(cofactor(arr,i,0));
        }
        return sum;
    }

}

*/
/**
    Vector<Vector<int>> map(
                Vector<int>(1,1,1,1),
                Vector<int>(0,2,0,4),
                Vector<int>(5,2,1,4),
                Vector<int>(1,4,3,0)
                );


    cout<<"_____determinant_____"<<endl;
    STL::for_each(map.begin(),map.end(),[](Vector<int>& v){
        STL::out_foreach(v.begin(),v.end());
    });
    cout<<"_____________________"<<endl;





    cout<<"value: "<<determinant(map)<<endl;

    for(int i=0;i<map.length();i++)
    {
        cout<<"map (0,"<<i<<") cofactor"<<endl;
        Vector<Vector<int>> A=cofactor(map,0,i);
        STL::for_each(A.begin(),A.end(),[](Vector<int>& v){
            STL::out_foreach(v.begin(),v.end());
        });
        cout<<"__________________"<<endl<<endl;;

    }

*/
/**

    STL::initializer_array<char,'H','e','l','l','o',',','W','o','r','l','d'> arr;
    STL::for_each(arr.begin(),arr.end(),STL::make_ostream_iterator(cout));
    cout<<endl;

    cout<<"const int : "<<STL::is_const<const int>::value<<endl;
    cout<<"int : "<<STL::is_const<int>::value<<endl;
    cout<<"const float : "<<STL::is_const<const float>::value<<endl;
    cout<<"float : "<<STL::is_const<float>::value<<endl;

    cout<<"const STL::Vector<int>: "<<STL::is_const<const STL::Vector<int>>::value<<endl;
    cout<<"STL::Vector<int> : "<<STL::is_const<STL::Vector<int>>::value<<endl;

    cout<<"int,int : "<<STL::is_same<int,int>::value<<endl;
    cout<<"int,float: "<<STL::is_same<int,float>::value<<endl;

    cout<<"constent :"<<STL::integral_constant<int,12>::value<<endl;

    cout<<"int,add_const(int) :"<<STL::is_same<int,STL::add_const<int>::type>::value<<endl;
    cout<<"const int,add_const(int) :"<<STL::is_same<const int,STL::add_const<int>::type>::value<<endl;
    cout<<"const int,add_const(const int) :"<<STL::is_same<const int,STL::add_const<const int>::type>::value<<endl;

    cout<<"int * :"<<STL::is_pointer<int*>::value<<endl;
    cout<<"int :"<<STL::is_pointer<int>::value<<endl;

    cout<<"const int * : "<<STL::is_pointer<const int *>::value<<endl;
    cout<<"add_const(int*):"<<STL::is_pointer<STL::add_const<int*>::type>::value<<endl;
    cout<<"const int*,add_const(int*)"<<STL::is_same<const int*,STL::add_const<int*>::type>::value<<endl;

    cout<<"const int*,add_const(int*)"<<is_same<const int*,add_const<int*>::type>::value<<endl;

*/

/**
template<typename T,typename Distance=int>class initializer{
public:

    template<T...args>class list;

    template<T v,T...args>
    class list<v,args...>{
    protected:
        template <int N,T..._args> struct __element;
        template <int N,T _v,T..._args> struct __element<N,_v,_args...>{
            static constexpr T e=__element<N-1,_args...>::e;
        };
        template <T _v,T..._args> struct __element<0,_v,_args...>{
            static constexpr T e=_v;
        };


    public:
        template <int N>
        T element()
        {
            return __element<N,v,args...>::e;
        }

    public:
        static constexpr T value=v;
        static list<args...> child_list;
    };

    template<T v>
    class list<v>{

    protected:
        template <int N,T..._args> struct __element;
        template <T _v> struct __element<0,_v>{
            static constexpr T e=_v;
        };
    public:
        template <int N>
        T element()
        {
            return __element<N,v>::e;
        }
    private:
        static constexpr T value=v;
    };

    template<T...args>class Array{
    protected:
        using size_type=Distance;
        using value_type=T;
        using ptr_type=T*;
        using ref_type=T&;
        using const_ptr_type=const T*;
        using const_ref_type=const T&;
        using right_ref_type=T&&;
    public:
        using iterator=T*;
    public:
        Array(){}
        iterator begin(){return array;}
        iterator end(){return array+size;}
        size_type length()const{return size;}
        bool isEmpty()const{return size;}
        const_ref_type front()const{return *begin();}
        const_ref_type back()const{return *(end()-1);}
        void fill(const_ref_type v)
        {
            for(size_type i=0;i<size;++i)
                array[i]=v;
        }
        ref_type operator[](size_type i){return *(array+i);}
    private:
        static constexpr size_type size=sizeof...(args);
        value_type array[size]={args...};
    };
};



*/


/**
    // test iterator reverse_iterator const_iterator
    cout<<"test iterator reverse_iterator const_iterator"<<endl;
    STL::Vector<int> v(1,2,3,4,5,6,7,8,9,0);
    cout<<"Vector<int>"<<" length: "<<v.length()<<endl;
    STL::out_foreach(v.begin(),v.end(),"v: ");
    STL::out_foreach(v.rbegin(),v.rend(),"v: ");
    STL::out_foreach(v.cbegin(),v.cend(),"v: ");

    STL::LinkedList<int> list(v.begin(),v.end());
    cout<<"LinkedList<int>"<<" length: "<<list.length()<<endl;
    STL::out_foreach(list.begin(),list.end(),"list: ");
    STL::out_foreach(list.rbegin(),list.rend(),"list: ");
    STL::out_foreach(list.cbegin(),list.cend(),"list: ");
    STL::initializer<int>::Array<65,43,45,6,7,82,67,7,61,2> arr;

    STL::AvlTree<int> avl(arr.begin(),arr.end());
    cout<<"AvlTree<int>"<<" length: "<<avl.length()<<endl;
    STL::out_foreach(avl.begin(),avl.end(),"avl: ");
    STL::out_foreach(avl.rbegin(),avl.rend(),"avl: ");
    STL::out_foreach(avl.cbegin(),avl.cend(),"avl: ");

    STL::BinaryTree<int> btree(arr.begin(),arr.end());
    cout<<"BinaryTree<int>"<<" length: "<<btree.length()<<endl;
    STL::out_foreach(btree.begin(),btree.end(),"btree: ");
    STL::out_foreach(btree.rbegin(),btree.rend(),"btree: ");
    STL::out_foreach(btree.cbegin(),btree.cend(),"btree: ");

    STL::RecursiveTree<int> rtree(arr.begin(),arr.end());
    cout<<"RecursiveTree<int>"<<" length: "<<rtree.length()<<endl;
    STL::out_foreach(rtree.begin(),rtree.end(),"rtree: ");
    STL::out_foreach(rtree.rbegin(),rtree.rend(),"rtree: ");
    STL::out_foreach(rtree.cbegin(),rtree.cend(),"rtree: ");

    STL::Set<int> iset(arr.begin(),arr.end());
    cout<<"Set<int>"<<" length: "<<iset.length()<<endl;
    STL::out_foreach(iset.begin(),iset.end(),"iset: ");
    STL::out_foreach(iset.rbegin(),iset.rend(),"iset: ");

    STL::MultiSet<int> miset(arr.begin(),arr.end());
    cout<<"MultiSet<int>"<<" length: "<<miset.length()<<endl;
    STL::out_foreach(miset.begin(),miset.end(),"miset: ");
    STL::out_foreach(miset.rbegin(),miset.rend(),"miset: ");

    typedef typename STL::Pair<string,int> pair_type;
    STL::Vector<pair_type> pair_arr(pair_type("Apple",12),
                             pair_type("OK",17),
                             pair_type("holy",57),
                             pair_type("faker",76),
                             pair_type("hello",88),
                             pair_type("The",96),
                             pair_type("world",75),
                             pair_type("holy",23)
                             );
    STL::Map<string,int> map(pair_arr.begin(),pair_arr.end());
    cout<<"Map<string,int>"<<" length: "<<map.length()<<endl;
    STL::out_foreach(map.begin(),map.end(),"map: ");
    STL::out_foreach(map.rbegin(),map.rend(),"map: ");

    STL::MultiMap<string,int> mmap(pair_arr.begin(),pair_arr.end());
    cout<<"MultiMap<string,int>"<<" length: "<<mmap.length()<<endl;
    STL::out_foreach(mmap.begin(),mmap.end(),"mmap: ");
    STL::out_foreach(mmap.rbegin(),mmap.rend(),"mmap: ");

    STL::HashSet<int> hset(arr.begin(),arr.end());
    cout<<"HashSet<int>"<<" length: "<<iset.length()<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"hset: ");

    STL::HashMultiSet<int> hmset(arr.begin(),arr.end());
    cout<<"HashMultiSet<int>"<<" length: "<<hmset.length()<<endl;
    STL::out_foreach(hmset.begin(),hmset.end(),"hmset: ");

    STL::HashMap<string,int> hmap(pair_arr.begin(),pair_arr.end());
    cout<<"HashMap<string,int>"<<" length: "<<hmap.length()<<endl;
    STL::out_foreach(hmap.begin(),hmap.end(),"hmap: ");

    STL::HashMultiMap<string,int> hmmap(pair_arr.begin(),pair_arr.end());
    cout<<"HashMultiMap<string,int>"<<" length: "<<hmmap.length()<<endl;
    STL::out_foreach(hmmap.begin(),hmmap.end(),"hmmap: ");


*/
/**         MultiMap iterator
struct iterator;
struct reverse_iterator;

struct iterator:public base_iterator<bidirectional_iterator_tag,pair_type,
        typename STL::iterator_traits<typename Basic::iterator>::difference_type>
{
    typename Basic::iterator iter;

    iterator(){}
    iterator(const typename Basic::iterator& i):iter(i){}
    iterator(const iterator & i):iter(i.iter){}
    iterator(const reverse_iterator& i):iter(i.iter){}
    const_ref_pair_type operator*(){return *iter;}
    const_ptr_pair_type operator->(){return &(*iter);}

    bool operator == (const iterator& i){return iter==i.iter;}
    bool operator != (const iterator& i){return iter!=i.iter;}

    const iterator& operator =(const iterator& i){iter=i.iter;return *this;}
    const iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}
    iterator operator ++(){++iter;return *this;}
    iterator operator ++(int){iterator tmp=*this;++iter;return tmp;}

    iterator operator --(){--iter;return *this;}
    iterator operator --(int){iterator tmp=*this;--iter;return tmp;}
};
struct reverse_iterator:public base_iterator<bidirectional_iterator_tag,pair_type,
        typename STL::iterator_traits<typename Basic::iterator>::difference_type>
{
    typename Basic::reverse_iterator iter;

    reverse_iterator(){}
    reverse_iterator(const typename Basic::reverse_iterator& i):iter(i){}
    reverse_iterator(const reverse_iterator & i):iter(i.iter){}
    reverse_iterator(const iterator& i):iter(i.iter){}
    const_ref_pair_type operator*(){return *iter;}
    const_ptr_pair_type operator->(){return &(*iter);}

    bool operator == (const reverse_iterator& i){return iter==i.iter;}
    bool operator != (const reverse_iterator& i){return iter!=i.iter;}

    const reverse_iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}
    const reverse_iterator& operator =(const iterator& i){iter=i.iter;return *this;}
    reverse_iterator operator ++(){++iter;return *this;}
    reverse_iterator operator ++(int){reverse_iterator tmp=*this;++iter;return tmp;}

    reverse_iterator operator --(){--iter;return *this;}
    reverse_iterator operator --(int){reverse_iterator tmp=*this;--iter;return tmp;}

};
*/

/**         MultiSet iterator
struct iterator;
struct reverse_iterator;

struct iterator:public base_iterator<bidirectional_iterator_tag,key_type,
        typename STL::iterator_traits<typename Basic::iterator>::difference_type>{
    typename Basic::iterator iter;

    iterator(){}
    iterator(const typename Basic::iterator& i):iter(i){}
    iterator(const iterator & i):iter(i.iter){}
    iterator(const reverse_iterator& i):iter(i.iter){}
    const_ref_type operator*(){return *iter;}
    const_ptr_type operator->(){return &(*iter);}
    bool operator == (const iterator& i){return iter==i.iter;}
    bool operator != (const iterator& i){return iter!=i.iter;}

    const iterator& operator =(const iterator& i){iter=i.iter;return *this;}
    const iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}
    iterator operator ++(){++iter;return *this;}
    iterator operator ++(int){iterator tmp=*this;++iter;return tmp;}

    iterator operator --(){--iter;return *this;}
    iterator operator --(int){iterator tmp=*this;--iter;return tmp;}
};
struct reverse_iterator:public base_iterator<bidirectional_iterator_tag,key_type,
        typename STL::iterator_traits<typename Basic::iterator>::difference_type>{
    typename Basic::reverse_iterator iter;

    reverse_iterator(){}
    reverse_iterator(const typename Basic::reverse_iterator& i):iter(i){}
    reverse_iterator(const reverse_iterator & i):iter(i.iter){}
    reverse_iterator(const iterator& i):iter(i.iter){}
    const_ref_type operator*(){return *iter;}
    const_ptr_type operator->(){return &(*iter);}
    bool operator == (const reverse_iterator& i){return iter==i.iter;}
    bool operator != (const reverse_iterator& i){return iter!=i.iter;}

    const reverse_iterator& operator =(const reverse_iterator& i){iter=i.iter;return *this;}
    const reverse_iterator& operator =(const iterator& i){iter=i.iter;return *this;}
    reverse_iterator operator ++(){++iter;return *this;}
    reverse_iterator operator ++(int){reverse_iterator tmp=*this;++iter;return tmp;}

    reverse_iterator operator --(){--iter;return *this;}
    reverse_iterator operator --(int){reverse_iterator tmp=*this;--iter;return tmp;}
};
*/

/**

    STL::initializer<int>::Array<12,3,46,7,8,9,87,65,43> arr;
    cout<<"length: "<<arr.length()<<endl;
    STL::out_foreach(arr.begin(),arr.end(),"arr: ");
    cout<<"arr: ";
    for(int i=0;i<arr.length();i++)
        cout<<arr[i]<<" ";
    cout<<endl;
    cout<<"arr: ";
    for(auto i=arr.begin();i!=arr.end();i++)
        cout<<*i<<" ";
    cout<<endl;
    for(auto i=arr.begin(),j=arr.end()-1;i<j;i++,j--)
    {
        auto tmp=*i;
        *i=*j;
        *j=tmp;
    }
    cout<<endl;
    STL::out_foreach(arr.begin(),arr.end(),"arr: ");

*/

/**
  底层为SHash 的HashMap的输出结果
v: <NO,12> <OK,17> <holy,23> <shit,76> <hello,88> <The,96> <world,75> <holy,23>
map: <holy,23> <The,96> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
<The,96> <world,75>
null star
succeed erase "The"
map: <holy,23> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
map: <holy,23> <star,99> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
holy count: 1
map length: 7
map: <star,99> <hello,88>
holy count: 0
map length: 2
map:
holy count: 0
map length: 0
map: <february,28> <star,100> <july,27> <january,31> <qwertg,99>
world-> 0
february star july january qwertg world v : 65 4 32 3 3 5 45 234 56 5 43 2 45 6 67 76
set: 2 3 4 5 6 3 65 5 76 234 56 45 32 67 43 45
succeed erase 5
set: 2 3 4 6 3 65 76 234 56 45 32 67 43 45
succeed insert 78
set: 2 3 4 6 3 65 76 234 56 78 45 32 67 43 45
45 count: 2
STL::HashMultiSet<int> cset(hset);
cset: 2 3 4 6 3 65 67 56 234 76 78 45 32 43 45
STL::HashMultiSet<int> mset(std::move(hset));
mset: 2 3 4 6 3 65 76 234 56 78 45 32 67 43 45
45 count:2
set:
mset size:15
cset size:15
hset isEmpty 0

底层为HashTable 的HashMap的输出结果
v: <NO,12> <OK,17> <holy,23> <shit,76> <hello,88> <The,96> <world,75> <holy,23>
map: <holy,23> <The,96> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
<The,96> <world,75>
null star
succeed erase "The"
map: <holy,23> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
map: <holy,23> <star,99> <shit,76> <hello,88> <NO,12> <OK,17> <world,75>
holy count: 1
map length: 7
map: <star,99>
holy count: 0
map length: 1
map:
holy count: 0
map length: 0
map: <february,28> <january,31> <star,100> <july,27> <qwertg,99>
world-> 0
february january star july qwertg world v : 65 4 32 3 3 5 45 234 56 5 43 2 45 6 67 76
set: 2 56 3 3 4 5 5 6 65 67 234 76 32 43 45 45
succeed erase 5
set: 2 56 3 3 4 6 65 67 234 76 32 43 45 45
succeed insert 78
set: 2 56 3 3 4 6 65 67 234 76 78 32 43 45 45
45 count: 2
STL::HashMultiSet<int> cset(hset);
cset: 2 3 3 56 4 6 65 67 234 76 78 32 43 45 45
STL::HashMultiSet<int> mset(std::move(hset));
mset: 2 56 3 3 4 6 65 67 234 76 78 32 43 45 45
45 count:2
set:
mset size:15
cset size:15
hset isEmpty: 0

*/


/**

    //  HashMultiSet test
    STL::Vector<int> v(65,4,32,3,3,5,45,234,56,5,43,2,45,6,67,76);

    STL::HashMultiSet<int> hset(v.begin(),v.end());
    STL::out_foreach(v.begin(),v.end(),"v : ");
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    hset.erase(5);cout<<"succeed erase 5"<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    hset.insert(78);cout<<"succeed insert 78"<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
     cout<<"45 count: "<<hset.count(45)<<endl;
    cout<<"STL::HashMultiSet<int> cset(hset);"<<endl;
    STL::HashMultiSet<int> cset(hset);
    STL::out_foreach(cset.begin(),cset.end(),"cset: ");
    cout<<"STL::HashMultiSet<int> mset(std::move(hset));"<<endl;
    STL::HashMultiSet<int> mset(std::move(hset));
    STL::out_foreach(mset.begin(),mset.end(),"mset: ");
    cout<<"45 count:"<<mset.count(45)<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    cout<<"mset size:"<<mset.length()<<endl;
    cout<<"cset size:"<<cset.length()<<endl;
    cout<<"hset isEmpty: "<<hset.isEmpty()<<endl;

*/


/**

    // HashMap test
    typedef typename STL::Pair<string,int> pair_type;
    STL::Vector<pair_type> v(pair_type("NO",12),
                             pair_type("OK",17),
                             pair_type("holy",23),
                             pair_type("shit",76),
                             pair_type("hello",88),
                             pair_type("The",96),
                             pair_type("world",75),
                             pair_type("holy",23)
                             );

    STL::HashMap<string,int> map;
    map.insert(v.begin(),v.end());
    STL::out_foreach(v.begin(),v.end(),"v: ");
    STL::out_foreach(map.begin(),map.end(),"map: ");
    cout<< * map.find("The")<<" "<<*map.find("world")<<endl;
    if(map.find("star")==map.end())
        cout<<"null star"<<endl;
    if(map.erase("The"))
        cout<<"succeed erase \"The\" "<<endl;
    STL::out_foreach(map.begin(),map.end(),"map: ");
    //map.insert("star",100);

    //map.insert(pair_type("star",44));
    map["star"]=99;
    STL::out_foreach(map.begin(),map.end(),"map: ");



    cout<<"holy count: "<<map.count("holy")<<endl;
    cout<<"map length: "<<map.length()<<endl;
    map.erase(v.begin(),v.end());
    STL::out_foreach(map.begin(),map.end(),"map: ");
    cout<<"holy count: "<<map.count("holy")<<endl;
    cout<<"map length: "<<map.length()<<endl;
    map.empty();
    STL::out_foreach(map.begin(),map.end(),"map: ");
    cout<<"holy count: "<<map.count("holy")<<endl;
    cout<<"map length: "<<map.length()<<endl;
    map["star"]=100;
    map["january"]=31;
    map["february"]=28;
    map["july"]=27;
    map["world"]=99;
    STL::out_foreach(map.begin(),map.end(),"map: ");
    cout<<"world-> "<<map["world"]<<endl;

    for(auto i=map.begin();i!=map.end();i++)
        cout<<i->first_value<<" ";



  */

/**

    //  HashSet test
    STL::Vector<int> v(65,4,32,3,45,234,56,5,43,2,45,6,67,76);

    STL::HashSet<int> hset(v.begin(),v.end());
    STL::out_foreach(v.begin(),v.end(),"v : ");
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    if(hset.erase(5))cout<<"succeed erase 5"<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    if(hset.insert(78))cout<<"succeed insert 78"<<endl;
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
     cout<<"45 count: "<<hset.count(45)<<endl;
    cout<<"STL::HashSet<int> cset(hset);"<<endl;
    STL::HashSet<int> cset(hset);
    STL::out_foreach(cset.begin(),cset.end(),"cset: ");
    cout<<"STL::HashSet<int> mset(std::move(hset));"<<endl;
    STL::HashSet<int> mset(std::move(hset));
    STL::out_foreach(mset.begin(),mset.end(),"mset: ");
    STL::out_foreach(hset.begin(),hset.end(),"set: ");
    cout<<"mset size:"<<mset.length()<<endl;
    cout<<"cset size:"<<cset.length()<<endl;
    cout<<"hset isEmpty: "<<hset.isEmpty()<<endl;


*/

/**
    //使用函数指针作为比较
    //需要在构造函数中传递函数指针
    STL::Vector<int> v1(9,6,4,5,3,4,3,4,5,6,7);
    STL::Map<int,int,bool(*)(const int&,const int&)> set(Less);
    while(v1.isEmpty())set.insert(v1.pop_back(),0);
    STL::out_foreach(set.begin(),set.end(),"map: ");

    //使用Functor将函数指针包装为仿函数
    STL::Vector<int> v2(9,6,4,5,3,4,3,4,5,6,7);
    STL::MultiSet<int,STL::Functor<bool,const int&,const int&>>
        set2(STL::make_functor(Less));
    set2.insert(v2.begin(),v2.end());
    STL::out_foreach(set2.begin(),set2.end(),"MultiSet: ");

    //使用Functor将函数指针包装为仿函数
    STL::Map<int,int,STL::Functor<bool,const int&,const int&>>
        map(STL::make_functor(Less));
    while(v2.isEmpty())map.insert(v2.pop_back(),0);
    STL::out_foreach(map.begin(),map.end(),"map: ");
    STL::Vector<int> vt(1,2,3,4,5,6,7,8,9);

    vt.resize(5,2);
    STL::out_foreach(vt.begin(),vt.end());
*/


/**

    //使用函数指针作为比较
    //需要在构造函数中传递函数指针
    STL::Vector<int> v3(9,6,4,5,3,4,3,4,5,6,7);
    STL::Map<int,int,bool(*)(const int&,const int&)> set(Less);
    while(v3.isEmpty())set.insert(v3.pop_back(),0);
    STL::out_foreach(set.begin(),set.end(),"map: ");

    //使用仿函数作为比较
    //无须传递参数
    STL::Vector<int> v2(9,6,4,5,3,4,3,4,5,6,7);
    STL::Map<int,int,STL::less<int>> set2;
    while(v2.isEmpty())set2.insert(v2.pop_back(),1);
    STL::out_foreach(set2.begin(),set2.end(),"map2: ");
    typedef typename STL::Pair<int,string> pair_type;

    STL::Vector<pair_type> v(
                pair_type(5,"qqq"),
                pair_type(7,"www"),
                pair_type(6,"eee"),
                pair_type(9,"rrr"),
                pair_type(8,"ttt")
                );

    STL::out_foreach(v.begin(),v.end(),"v: "," ");

    STL::Map<int,string,bool(*)(const int&,const int&)> iset(Less);
    iset.insert(v.begin(),v.end());

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    if(iset.erase(5))cout<<"succeed erase key=5"<<endl;
    if(iset.insert(pair_type(1,"ccc")))cout<<"succeed insert <1,ccc>"<<endl;

    STL::for_each(iset.begin(),iset.end(),STL::make_ostream_iterator(cout," "));
    cout<<endl;

    STL::Map<int,string,bool(*)(const int&,const int&)> cset(std::move(iset));
    cout<<"cset(std::move(iset))"<<endl;
    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    cout<<"iset isempty: "<<iset.isEmpty()<<endl;

    iset=cset;
    cout<<"iset = cset"<<endl;
    cout<<"iset[7]= \"kkk\" "<<endl;
    iset[7]="kkk";
    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    iset=std::move(cset);
    cout<<"iset=std::move(cset)"<<endl;

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    iset.erase(v.begin(),v.end());
    cout<<"iset.erase(v.begin(),v.end());"<<endl;

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");
*/


/**

    int * arr=new int[10]{1,2,3,4,5,4,5,6,3,0};
    STL::out_foreach(arr,arr+10,"arr: ");
    cout<<"5 count :"<<STL::count(arr,arr+10,5)<<endl;
    *STL::find(arr,arr+10,5)=10;
    cout<<"*STL::find(arr,arr+10,5)=10;"<<endl;
    STL::out_foreach(arr,arr+10,"arr: ");

    cout<<STL::Min(2,3)<<endl;
    int i=10,j=3;
    cout<<STL::Max(i,j)<<endl;

    cout<<"arr max ="<<*STL::Max_element(arr,arr+10)<<endl;

    STL::Vector<int> v{8,7,6,5,3,4,5,6,7,0};
    cout<<"v max ="<<*STL::Max_element(v.begin(),v.end())<<endl;
    cout<<"arr min ="<<*STL::Min_element(arr,arr+10)<<endl;

    STL::Vector<int> v2(0,0,0,0,0,0,0,0,0,0);
    cout<<"v min ="<<*STL::Min_element(v.begin(),v.end())<<endl;
     STL::out_foreach(v.begin(),v.end());

    //STL::replace(v.begin(),v.end(),STL::bind2st(STL::less<int>(),5),10);
    STL::copy_if(v.begin(),v.end(),v2.begin(),STL::bind2st(STL::less<int>(),6));
    STL::out_foreach(v2.begin(),v2.end());

    cout<<"reverse v:"<<endl;

    STL::reverse(v.begin(),v.end());

    STL::out_foreach(v.begin(),v.end());cout<<endl;
    STL::out_foreach(v2.begin(),v2.end(),"v2 ");
    STL::out_foreach(v.begin(),v.end(),"v ");
    cout<<"swap v v2"<<endl;
    STL::swap(v,v2);
    STL::out_foreach(v2.begin(),v2.end(),"v2 ");
    STL::out_foreach(v.begin(),v.end(),"v ");

    cout<<"swap_ranges v ,v2"<<endl;
    STL::swap_ranges(v2.begin(),v2.end(),v.begin());
    STL::out_foreach(v2.begin(),v2.end(),"v2 ");
    STL::out_foreach(v.begin(),v.end(),"v ");
    cout<<"transform v=v-2"<<endl;
    STL::transform(v.begin(),v.end(),v.begin(),STL::bind2st(STL::minus<int>(),2));
    STL::out_foreach(v.begin(),v.end(),"v ");

    cout<<"transform v2=v*v "<<endl;

    STL::transform(v.begin(),v.end(),v.begin(),v2.begin(),STL::multiplies<int>());
    STL::out_foreach(v.begin(),v.end(),"v ");
    STL::out_foreach(v2.begin(),v2.end(),"v2 ");

*/
/*
 *      STL::Vector<int> v(7,5,6,5,3,4,6,7,8);
       STL::MultiSet<int> iset(v.begin(),v.end());
       STL::out_foreach(iset.begin(),iset.end(),"iset : ");
       if(iset.erase(5))cout<<"succeed erase key= 5"<<endl;
       iset.insert(1);cout<<"succeed insert 1"<<endl;

       STL::for_each(iset.begin(),iset.end(),STL::make_ostream_iterator(cout," "));
       cout<<endl;

       STL::MultiSet<int> cset(std::move(iset));
       STL::out_foreach(cset.begin(),cset.end(),"cset : ");
       cout<<"iset isempty: "<<iset.isEmpty()<<endl;

       iset=cset;
       cout<<"iset = cset"<<endl;
       STL::out_foreach(iset.begin(),iset.end(),"iset : ");
       STL::out_foreach(iset.rbegin(),iset.rend(),"reverse: ");
       STL::MultiSet<int>::iterator i;
       i=iset.rbegin();
       cout<<"iterator i=iset.rbegin() *i="<<*i<<endl;
       if(++i==iset.end())cout<<"++i==iset.end()"<<endl;

       STL::MultiSet<int>::reverse_iterator j;
       j=iset.begin();
       cout<<"reverse_iterator j=iset.begin() *j="<<*j<<endl;
       if(++j==iset.rend())cout<<"++j==iset.rend()"<<endl;

       STL::out_foreach(cset.begin(),cset.end(),"cset : ");

       iset=std::move(cset);
       cout<<"iset=std::move(cset)"<<endl;
       STL::out_foreach(iset.begin(),iset.end(),"iset : ");
       STL::out_foreach(cset.begin(),cset.end(),"cset : ");

       cout<<"*(iterator.operator->()) :";
       for(auto i=iset.begin();i!=iset.end();i++)
           cout<<*(i.operator->())<<" ";
       cout<<endl;
       iset.erase(v.begin(),v.end());
       cout<<"iset.erase(v.begin(),v.end());"<<endl;
       STL::out_foreach(iset.begin(),iset.end(),"iset : ");

/*
 *  //            //MultiMap test
           typedef typename STL::Pair<int,string> pair_type;

           STL::Vector<pair_type> v(
                       pair_type(5,"qqq"),
                       pair_type(7,"www"),
                       pair_type(7,"zzz"),
                       pair_type(6,"eee"),
                       pair_type(9,"rrr"),
                       pair_type(9,"xxx"),
                       pair_type(8,"ttt")
                       );

           STL::out_foreach(v.begin(),v.end(),"v: "," ");

           STL::MultiMap<int,string> iset(v.begin(),v.end());

           STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

           if(iset.erase(6))cout<<"succeed erase key=6"<<endl;
           iset.insert(pair_type(1,"ccc"));
           cout<<"insert <1,ccc>"<<endl;
           cout<<"key 9 count:"<<iset.count(9)<<endl;
           STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

           STL::MultiMap<int,string> cset(std::move(iset));
           cout<<"cset(std::move(iset))"<<endl;
           STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

           cout<<"iset isempty: "<<iset.isEmpty()<<endl;

           iset=cset;
           cout<<"iset = cset"<<endl;
           cout<<"iset[7]= \"kkk\" "<<endl;
           iset[7]="kkk";
           STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

           STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

           iset=std::move(cset);
           cout<<"iset=std::move(cset)"<<endl;
           cout<<"*(--(++(++iset.begin()))): "<<*(--(++(++iset.begin())))<<endl;


            STL::out_foreach(iset.rbegin(),iset.rend(),"reverse iset: ");
           STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");



            STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");
           auto erase_iter=iset.find(9);
            cout<<"erase_iter=iset.find(9);index="<<erase_iter.iter.index<<endl;
            erase_iter++;
             cout<<" erase_iter++;index="<<erase_iter.iter.index<<endl;
           iset.erase(erase_iter);
            STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");
             cout<<" iterator.operator->()";
            for(auto i=iset.begin();i!=iset.end();i++)
                cout<<"<"<<i->first_value<<","<<i->second_value<<"> ";
            cout<<endl;


           iset.erase(v.begin(),v.end());

           cout<<"iset.erase(v.begin(),v.end())"<<endl;
           STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");
*/







/*  //AvlTree TEST
/*    STL::AvlTree<int> avl;
    STL::Vector<int> v(23,45,87,63,56,825,825,825,692,2,32,34,5,6,52,64,3,4,6,7,6);


    STL::Vector<int> iv(v);
    STL::quick_sort(iv.begin(),iv.end());
    STL::out_foreach(iv.begin(),iv.end(),"sort V: ");

    avl.insert(v.begin(),v.end());

    cout<<"length: "<<avl.length()<<endl;
    STL::out_foreach(avl.begin(),avl.end(),"avltree: ");
    STL::out_foreach(avl.rbegin(),avl.rend(),"reverse_iterator:");

    cout<<"erase 2: "<<avl.erase(2)<<endl;
    if(avl.find(2)==avl.end()) cout<<"not find 2"<<endl;
    cout<<"length: "<<avl.length()<<endl;

    cout<<"Max="<<* avl.findMax()<<endl;
    cout<<"erase Max"<<endl;
    avl.erase(*avl.findMax());

    cout<<"Max="<<* avl.findMax()<<endl;
    auto iter=avl.find(6);
    cout<<"iter.index:"<<iter.index<<endl;
    ++iter;
    cout<<"iter.index:"<<iter.index<<endl;
    cout<<"erase 6 : "<< avl.erase(iter)<<endl;

    cout<<"erase 6 : "<< avl.erase(iter)<<endl;
    cout<<"erase 6 : "<< avl.erase(iter)<<endl;
    cout<<"erase 6 : "<< avl.erase(iter)<<endl;
    STL::out_foreach(avl.begin(),avl.end(),"avltree: ");
    cout<<"length: "<<avl.length()<<endl;
    cout<<"isEmpty: "<<avl.isEmpty()<<endl;
    cout<<"avltree--:";
    for(auto i=avl.findMax();i!=avl.end();i--)
        cout<<*i<<" ";
    cout<<endl;

    cout<<"avl.erase(avl.begin(),avl.end());"<<endl;
    avl.erase(avl.begin(),avl.end());
    cout<<"isEmpty: "<<avl.isEmpty()<<endl;
    avl.insert(v.begin(),v.end());
    //avl.empty();
    STL::out_foreach(avl.begin(),avl.end(),"avltree: ");

    for(auto i=avl.begin();i!=avl.end();i++)
        if(*i==6)
        {
            for(STL::AvlTree<int>::reverse_iterator j=i;j!=avl.rend();j++)
                cout<<*j<<" ";
            break;
        }
        else
        {
            cout<<*i<<" ";
        }
    cout<<endl;
*/
*/
//Set<Key,CMP,Recursive<Key>> test
/*       STL::Vector<int> v(7,6,5,3,4,6,7,8);
STL::Set<int,STL::less<int>,STL::RecursiveTree<int>> iset(v.begin(),v.end());

if(iset.erase(5))cout<<"succeed erase"<<endl;
if(iset.insert(1))cout<<"succeed insert"<<endl;

STL::for_each(iset.begin(),iset.end(),STL::make_ostream_iterator(cout," "));
cout<<endl;

STL::Set<int,STL::less<int>,STL::RecursiveTree<int>> cset(std::move(iset));
STL::out_foreach(cset.begin(),cset.end(),"cset : ");
cout<<"iset isempty: "<<iset.isEmpty()<<endl;

iset=cset;
cout<<"iset = cset"<<endl;
STL::out_foreach(iset.begin(),iset.end(),"iset : ");
STL::out_foreach(cset.begin(),cset.end(),"cset : ");

iset=std::move(cset);
cout<<"iset=std::move(cset)"<<endl;
STL::out_foreach(iset.begin(),iset.end(),"iset : ");
STL::out_foreach(cset.begin(),cset.end(),"cset : ");

iset.erase(v.begin(),v.end());
cout<<"iset.erase(v.begin(),v.end());"<<endl;
STL::out_foreach(iset.begin(),iset.end(),"iset : ");
*/

/*          Map test
    typedef typename STL::Pair<int,string> pair_type;

    STL::Vector<pair_type> v(
                pair_type(5,"qqq"),
                pair_type(7,"www"),
                pair_type(6,"eee"),
                pair_type(9,"rrr"),
                pair_type(8,"ttt")
                );

    STL::out_foreach(v.begin(),v.end(),"v: "," ");

    STL::Map<int,string> iset(v.begin(),v.end());

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    if(iset.erase(5))cout<<"succeed erase key=5"<<endl;
    if(iset.insert(pair_type(1,"ccc")))cout<<"succeed insert <1,ccc>"<<endl;

    STL::for_each(iset.begin(),iset.end(),STL::make_ostream_iterator(cout," "));
    cout<<endl;

    STL::Map<int,string> cset(std::move(iset));
    cout<<"cset(std::move(iset))"<<endl;
    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    cout<<"iset isempty: "<<iset.isEmpty()<<endl;

    iset=cset;
    cout<<"iset = cset"<<endl;
    cout<<"iset[7]= \"kkk\" "<<endl;
    iset[7]="kkk";
    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    iset=std::move(cset);
    cout<<"iset=std::move(cset)"<<endl;

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");

    STL::out_foreach(cset.begin(),cset.end(),"cset : "," ");

    iset.erase(v.begin(),v.end());
    cout<<"iset.erase(v.begin(),v.end());"<<endl;

    STL::out_foreach(iset.begin(),iset.end(),"iset : "," ");
*/

/*          Set test
    STL::Vector<int> v(7,6,5,3,4,6,7,8);
    STL::Set<int> iset(v.begin(),v.end());

    if(iset.erase(5))cout<<"succeed erase"<<endl;
    if(iset.insert(1))cout<<"succeed insert"<<endl;

    STL::for_each(iset.begin(),iset.end(),STL::make_ostream_iterator(cout," "));
    cout<<endl;

    STL::Set<int> cset(std::move(iset));
    STL::out_foreach(cset.begin(),cset.end(),"cset : ");
    cout<<"iset isempty: "<<iset.isEmpty()<<endl;

    iset=cset;
    cout<<"iset = cset"<<endl;
    STL::out_foreach(iset.begin(),iset.end(),"iset : ");
    STL::out_foreach(cset.begin(),cset.end(),"cset : ");

    iset=std::move(cset);
    cout<<"iset=std::move(cset)"<<endl;
    STL::out_foreach(iset.begin(),iset.end(),"iset : ");
    STL::out_foreach(cset.begin(),cset.end(),"cset : ");

    iset.erase(v.begin(),v.end());
    cout<<"iset.erase(v.begin(),v.end());"<<endl;
    STL::out_foreach(iset.begin(),iset.end(),"iset : ");
*/

/*              Map test

    STL::Vector<STL::Pair<int,string>> pv(
                STL::Pair<int,string>(12,"fewrgw"),
                STL::Pair<int,string>(7,"yresy"),
                STL::Pair<int,string>(6,"hsshsre"),
                STL::Pair<int,string>(8,"hehea")
                );

    STL::Map<int,string> map(pv.begin(),pv.end());
    cout<<map.length()<<endl;

    if(map.erase(7))
       cout<<"delete 7"<<endl;
    if(map.insert(7,"hhhhhh"))
        cout<<"succeed"<<endl;
    else
        cout<<"fail"<<endl;
    for(auto i=map.begin();i!=map.end();i++){
        cout<<i->first_value<<","<<i->second_value<<endl;
    }

    STL::Vector<int> v(5,4,6,8,2,1,3,9,7);

    STL::BinaryTree_sort(v.begin(),v.end());

    STL::out_foreach(v.begin(),v.end(),"sort v: ");
*/
/*
//Set test
class CMP{
public:
    bool operator ()( STL::Tuple<string,int>& x,
                      STL::Tuple<string,int>& y)
    {
        return x.element<1>() < y.element<1>();
    }
};



int main()
{
    STL::Vector<int> v(9,8,6,5,1,5,5,4,8,9,6,3,6);

    STL::Set<int> iset(v.begin(),v.end());

    STL::out_foreach(iset.begin(),iset.end(),"set : ");

    auto iter=iset.find(3);
    if(iter!=iset.end())
        cout<<*iter<<endl;
    else
        cout<<"NULL"<<endl;

    STL::out_foreach(iset.begin(),iset.end(),"set : ");

    STL::Set<STL::Tuple<string,int>,CMP> mset;

    mset.insert(STL::Tuple<string,int>("qwe",1));
    mset.insert(STL::Tuple<string,int>("af",7));
    mset.insert(STL::Tuple<string,int>("af",2));
    mset.insert(STL::Tuple<string,int>("vsd",3));
    mset.insert(STL::Tuple<string,int>("afa",8));
    mset.insert(STL::Tuple<string,int>("qer",4));
    mset.insert(STL::Tuple<string,int>("afwaf",9));

    for(auto i=mset.begin();i!=mset.end();i++)
        cout<<(*i).element<0>()<<","<<(*i).element<1>()<<endl;


    return 0;
}

*/

/*

bool fcmp(int x,int y){return x<y;}

int main()
{
    STL::Compare_extend<less<int>> cmp;

    cout<<cmp.less(1,2)<<endl;
    cout<<cmp.equal_to(1,2)<<endl;
    cout<<cmp.greater(1,2)<<endl;
    cout<<cmp.less_equal(1,2)<<endl;
    cout<<cmp.not_equal_to(1,2)<<endl;

    auto c=STL::make_Compare_extend(STL::less<int>());

    cout<<c.less(1,2)<<endl;
    cout<<c.equal_to(1,2)<<endl;
    cout<<c.greater(1,2)<<endl;
    cout<<c.less_equal(1,2)<<endl;
    cout<<c.not_equal_to(1,2)<<endl;

    return 0;
}

*/
/* swap test
    STL::Vector<int> v1(1,2,3,4,5,6,7,8,9,0);
    STL::Vector<int> v2(0,9,8,7,6,5,4,3,2,1);

    auto i=v1.begin();
    auto j=v2.begin();
    STL::out_foreach(i,i+v1.length(),"iterator v1: ");
    STL::out_foreach(j,j+v2.length(),"iterator v2: ");
    STL::out_foreach(v1.begin(),v1.end(),"v1 :");
    STL::out_foreach(v2.begin(),v2.end(),"v2 :");

    cout<<"swap(v1,v2)"<<endl;
    STL::swap(v1,v2);
    STL::out_foreach(i,i+v1.length(),"iterator v1: ");
    STL::out_foreach(j,j+v2.length(),"iterator v2: ");

    STL::out_foreach(v1.begin(),v1.end(),"v1 :");
    STL::out_foreach(v2.begin(),v2.end(),"v2 :");
    */


/*

    //Pair test

    typedef typename STL::Pair<string,STL::Vector<int>> NameList;
    STL::Vector<int> v(1,2,3,4,5,6,7,8,9,0);
    NameList list1("list1 :",std::move(v));

    cout<<list1.first_value;
    STL::out_foreach(list1.second_value.begin(),list1.second_value.end());

    NameList list2(std::move(list1));
    cout<<list1.first_value;
    STL::out_foreach(list1.second_value.begin(),list1.second_value.end());
    cout<<list2.first_value;
    STL::out_foreach(list2.second_value.begin(),list2.second_value.end());


*/
/*
    // Pair test

    STL::Pair<int,string> p(11,"wwww");
    cout<<p.first_value<<endl;
    cout<<p.second_value<<endl;

    STL::Pair<int,string> p2(p);
    STL::Pair<int,string> p3;
    cout<<p2.first_value<<endl;
    cout<<p2.second_value<<endl;

    p3.first_value=999;
    p3.second_value="zzzz";

    cout<<p3.first_value<<endl;
    cout<<p3.second_value<<endl;

*/
/*

    //Stack Queue 不同内核测试

    STL::Queue<int,STL::LinkedList<int>> q1;
    STL::Queue<int,STL::List<int>> q2;
    for(int i=0;i<10;i++)q1.push(i);
    for(int i=0;i<10;i++)q2.push(i);

    while(q1.isEmpty())cout<<q1.pop()<<" ";cout<<endl;
    while(q2.isEmpty())cout<<q2.pop()<<" ";cout<<endl;
    cout<<q1.length()<<","<<q2.length()<<endl;



    STL::Stack<int,STL::Vector<int>> s1;
    STL::Stack<int,STL::LinkedList<int>> s2;
    STL::Stack<int,STL::List<int>> s3;
    for(int i=0;i<10;i++)s1.push(i);
    for(int i=0;i<10;i++)s2.push(i);
    for(int i=0;i<10;i++)s3.push(i);

    cout<<s1.top()<<","<<s2.top()<<","<<s3.top()<<endl;
    s1.pop();
    s2.pop();
    s3.pop();
    s1.push(-1);
    s2.push(-1);
    s3.push(-1);
    cout<<s1.length()<<","<<s2.length()<<","<<s3.length()<<endl;
    while(s1.isEmpty())cout<<s1.pop()<<" ";cout<<endl;
    while(s2.isEmpty())cout<<s2.pop()<<" ";cout<<endl;
    while(s3.isEmpty())cout<<s3.pop()<<" ";cout<<endl;
*/

/*
    STL::Vector<int> v(1,2,7,54,1,2,4,5,6,5,3,2,16,5,2,8,5,6,21,
                       5,2,1,8,94,6,5,1,2,0,21,5,8,4,6,5,1,3,1,2,
                       5,4,97,8,4,6,5,1,21,1,47,8,5,2,1,1,4,8,5,6,
                       27,8,5,1,2,1,4,8,4,5,1,2,14,4,7,8,65,1,2,1,7,4);

    STL::Vector<int> v2(v.begin(),v.end());
    STL::Vector<int> v3(v.length());
    STL::copy_n(v.begin(),v.end(),v3.begin());
    v3.resize(v.length());

    STL::out_foreach(v.begin(),v.end(),"v :"," ",10);

    STL::out_foreach(v2.begin(),v2.end(),"v2: "," ",10);

    STL::out_foreach(v3.begin(),v3.end(),"v3: "," ",10);
*/
//List test
/*
    STL::List<int> list;
    for(int i=0;i<10;i++)
        list.push_back(i);
    STL::out_foreach(list.begin(),list.end(),"list : ");
    cout<<list.pop_back()<<" "<<list.pop_front()<<endl;
    list.insert(list.begin(),9);
    list.insert(list.end(),0);
    STL::out_foreach(list.begin(),list.end(),"list : ");
    list.erase(list.begin());
    list.erase(list.end()-1);
    STL::out_foreach(list.begin(),list.end(),"list : ");

*/
//Lambda Tuple sort
/*
typedef typename STL::Tuple<int,string,int> Stu;

STL::Vector<Stu> v(Stu(1001,"zhao",58),Stu(1002,"qian",69),
                   Stu(1003,"sun",76),Stu(1004,"li",49),
                   Stu(1005,"zhou",82),Stu(1006,"wu",71));

STL::purity_quick_sort(v.begin(),v.end(),
                       []( Stu& x,Stu& y){
                            return x.element<2>() > y.element<2>() ;
                       });

STL::for_each(v.begin(),v.end(),
              [](Stu &x){
                    cout<<x.element<0>()<<" "<<x.element<1>()
                       <<" "<<x.element<2>()<<endl;
              });*/

/* bool isfunc(int v1,int v2){return v1<v2;}
 * STL::Vector<int> v(6,53,2,1,4,9,8,6,5,4,89,6,5,1,6,5,1);
 STL::purity_quick_sort(v.begin(),v.end(),STL::less<int>());
 STL::out_foreach(v.begin(),v.end(),"sort vector :");
 auto i=STL::binary_search(v.begin(),v.end(),5);
 if(i==v.end())
     cout<<"null"<<endl;
 else
     cout<<*i<<endl;*/
/* STL::Deque<int> deque;

 for(int i=0;i<4;i++)
     deque.insert(i);
 cout<<*deque.begin()<<endl;*/

/* STL::LinkedList<STL::Vector<int>> deque;

 for(auto i=deque.begin();i!=deque.end();i++);*/


 /*int * arr=new int[10]{1,2,3,4,5,6,7,8,9,0};
 STL::Vector<int> v0(arr,10);
 STL::Vector<int> v1(arr,arr+10);
 STL::Vector<int> v2(v1.begin(),v1.end());
 STL::Vector<int> v3(v0);
 STL::Vector<int> v4(std::move(v3));
 STL::Vector<int> v5(1,2,3,4,5,6,7,8,9,0);
 STL::Vector<int> v6(10,20);
 STL::Vector<STL::Vector<int>> v7(std::move(v4),std::move(v5));

 STL::out_foreach(v1.begin(),v1.end());
 STL::out_foreach(v2.begin(),v2.end());
 STL::out_foreach(v3.begin(),v3.end());
 STL::out_foreach(v4.begin(),v4.end());
 STL::out_foreach(v5.begin(),v5.end());
 STL::out_foreach(v6.begin(),v6.end());
 STL::out_foreach(v7[0].begin(),v7[0].end());
 STL::out_foreach(v7[1].begin(),v7[1].end());*/
/*
 STL::LinkedList<int> list1(arr,arr+10);
 STL::LinkedList<int> list2(v2.begin(),v2.end());
 STL::LinkedList<int> list3(list1.begin(),list1.end());

 STL::out_foreach(list1.begin(),list1.end());
 STL::out_foreach(list2.begin(),list2.end());
 STL::out_foreach(list3.begin(),list3.end());*/

/*
 * ofstream out;
    out.open("C:\\Users\\Lenovo\\Desktop\\test.txt",ios_base::out|ios_base::app);

    STL::Vector<string> v("awev","afvdbf","dWFEA","WEFRT","ertgr","egrgn","rtyt");
    STL::copy_d(v.begin(),v.end(),STL::make_ostream_iterator(out," "));
    out.close();
    cout<<"vector<string> :";
    STL::copy_d(v.begin(),v.end(),STL::make_ostream_iterator(cout," "));
    cout<<endl;
    ifstream in;
    in.open("C:\\Users\\Lenovo\\Desktop\\test.txt",ios_base::in);
    STL::Vector<int> read(0,0,0,0,0,0,0,0,0,0);
    cout<<"vector<int> read file:"<<endl;
    STL::copy_d(read.begin(),read.end(),STL::make_istream_iterator(in));
    in.close();
    cout<<"vector<int> :";
    STL::copy_d(read.begin(),read.end(),STL::make_ostream_iterator(cout," "));
template<typename T>
class Stack
{
protected:
    using value_type=T;
    using ref_type=T&;
    using ptr_type=T*;
    using const_ref_type=const T&;
    using const_ptr_type=const T*;
    using right_ref_type=T&&;

    using array_type=Vector<value_type>;


public:
    Stack(){}
    Stack(int size)
    {
        array.resize(size);
    }
    Stack(const Stack& s)
    {
        array.operator =(s.array);
    }
    Stack(Stack&& s)
    {
        array.operator =(std::move(s.array));
    }

public:

    void push(right_ref_type e){array.push_back(std::move(e));}
    void push(const_ref_type e){array.push_back(e);}
    value_type pop(){return array.pop_back();}
    const_ref_type top(){return array.back();}

    void empty(){array.empty();}
    bool isEmpty(){return array.isEmpty();}

    int length(){return array.length();}

private:
    array_type array;
};
*/
/*
template<unsigned long long N>
struct binary;
template<unsigned long long N>
struct binary
{
    constexpr static int value=binary<N/10>::value*2+N%10;
};

template<>
struct binary<0>
{
     constexpr static int value=0;
};

template<typename T>
inline void self_swap(T& t1,T& t2)
{
    T t=t1;
    t1=t2;
    t2=t;
}
#include "keytuple.h"*/
// Tuple test
/*
STL::Tuple<int,STL::Vector<int>,double,string>tuple(
            110,STL::Vector<int>(1,2,3),1.23,"hello");
int i;
STL::Vector<int> v;
double d;
string str;
cout<<"use Tuple read function "<<endl;
tuple.read(i,v,d,str);
cout<<"element int:"<<i<<endl;
cout<<"element vector<int>:";
STL::out_foreach(v.begin(),v.end());
cout<<"element double: "<<d<<endl;
cout<<"element string:"<<str<<endl;
cout<<endl;
cout<<"use Tuple write function"<<endl;
tuple.write(1,STL::Vector<int>(2,1,2),0.1,"world");
cout<<"use Tuple read function "<<endl;
tuple.read(i,v,d,str);
cout<<"element int:"<<i<<endl;
cout<<"element vector<int>:";
STL::out_foreach(v.begin(),v.end());
cout<<"element double: "<<d<<endl;
cout<<"element string:"<<str<<endl;
cout<<endl;
cout<<"use Tuple read_one function"<<endl;


int ri;
STL::Vector<int> rv;
double rd;
string rc;
tuple.read_one(0,ri);
tuple.read_one(1,rv);
tuple.read_one(2,rd);
tuple.read_one(3,rc);

cout<<"element int:"<<ri<<endl;
cout<<"element vector<int>:";
STL::out_foreach(rv.begin(),rv.end());
cout<<"element double: "<<rd<<endl;
cout<<"element string:"<<rc<<endl;
cout<<endl;
cout<<"use Tuple write_one function"<<endl;
ri=1024;
rv[0]=80;
rd=3.14;
rc="tuple";
tuple.write_one(0,ri);
tuple.write_one(1,rv);
tuple.write_one(2,rd);
tuple.write_one(3,rc);

tuple.read(i,v,d,str);
cout<<"element int:"<<i<<endl;
cout<<"element vector<int>:";
STL::out_foreach(v.begin(),v.end());
cout<<"element double: "<<d<<endl;
cout<<"element string:"<<str<<endl;
cout<<endl;

cout<<"use Tuple element function"<<endl;

cout<<"element int:"<<STL::tuple_element<0>(tuple)<<endl;
cout<<"element vector<int>:";
STL::Vector<int> rev=STL::tuple_element<1>(tuple);
STL::out_foreach(rev.begin(),rev.end());
cout<<"element double: "<<STL::tuple_element<2>(tuple)<<endl;
cout<<"element string:"<<STL::tuple_element<3>(tuple)<<endl;
cout<<endl;


STL::Tuple<int,char,double> t1(9,'z',0.99),t2(2,'x',1.001);
t1.set_primary_key(0);
t2.set_primary_key(0);
bool is=t1<t2;
cout<<is<<endl;
*/
/*                        // id,name,score
typedef typename STL::KeyTuple<3,int,string,STL::Vector<int>,int> Student;
Student stu1(1001,"zx",STL::Vector<int>(55,43,43,43),0);
Student stu2(1002,"ls",STL::Vector<int>(57,87,97,92,3),0);
Student stu3(1003,"wer",STL::Vector<int>(45,79),0);
Student stu4(1004,"mazi",STL::Vector<int>(53,53,45,43),0);
Student stu5(1005,"wwu",STL::Vector<int>(32,21,3),0);
self_swap(stu1,stu2);

STL::Vector<Student> V(std::move(stu1),std::move(stu2),
          std::move(stu3),std::move(stu4),std::move(stu5));

for(auto i=V.begin();i!=V.end();i++){
    cout<<STL::tuple_element<0>(*i)<<" , "
           <<STL::tuple_element<1>(*i)<<" , ";
    auto v=STL::tuple_element<2>(*i);
    STL::out_foreach(v.begin(),v.end());

    int num=0;
    for(auto j=v.begin();j!=v.end();j++)
        num+=(*j);
    i->write_one(3,num);
    cout<<" sum: ";
    cout<<STL::tuple_element<3>(*i)<<endl;;

}
for(auto i=V.begin();i!=V.end();i++)
    for(auto j=i;j!=V.end();j++)
        if((*i)>(*j))
            self_swap(*i,*j);
//STL::purity_quick_sort(V.begin(),V.end());
for(auto i=V.begin();i!=V.end();i++){
    cout<<STL::tuple_element<0>(*i)<<" , "
           <<STL::tuple_element<1>(*i)<<" , ";
    auto v=STL::tuple_element<2>(*i);
    STL::out_foreach(v.begin(),v.end());
    cout<<" sum: ";
    cout<<STL::tuple_element<3>(*i)<<endl;;

}*/
/*
cout<<"key=score  sort : "<<endl;


for(auto i=V.begin();i!=V.end();i++){
    cout<<STL::tuple_element<0>(*i)<<" , "
           <<STL::tuple_element<1>(*i)<<" , "
           <<STL::tuple_element<2>(*i)<<endl;
    //(*i).set_primary_key(0);
}

cout<<"key=id  sort : "<<endl;
//STL::purity_quick_sort(V.begin(),V.end());
for(auto i=V.begin();i!=V.end();i++){
    cout<<STL::tuple_element<0>(*i)<<" , "
           <<STL::tuple_element<1>(*i)<<" , "
           <<STL::tuple_element<2>(*i)<<endl;;
}*/

/*   STL::Tuple<int,string,STL::Vector<int>> t(13,"fsgfd",STL::Vector<int>(1,2,3,4));

cout<<t.element<0>()<<endl;
cout<<t.element<1>()<<endl;
auto v=t.element<2>();
STL::out_foreach(v.begin(),v.end());
cout<<endl;

t.set_element<0>(1212);
t.set_element<1>("dasff");
t.set_element<2>(STL::Vector<int>(44,46,56,451,2,3,4));

cout<<t.element<0>()<<endl;
cout<<t.element<1>()<<endl;
v=t.element<2>();
STL::out_foreach(v.begin(),v.end());
*/
/*
#include <iostream>
#include "vector.h"
#include "linkedlist.h"
#include "algorithms.h"

#include "list.h"

#include "binarytree.h"

using namespace std;
//using namespace STL;

template<typename R,typename ... Args>
struct Fun{
   typedef R (*F)(Args...);
   const static F func;
};
bool isMax(int i,int j)
{
    return i>j;
}


template<typename...Args>class Tuple;

template<>class Tuple<>{};

template<typename T,typename...Args>
class Tuple<T,Args...>:public Tuple<Args...>
{
public:
    Tuple(T v,Args...args):
        Tuple<Args...>(args...),
        value(v){cout<<value<<endl;}

public:
    T value;
};
//得到一个与实参相同类型的无参构造变量;
//由于t在函数内有生命周期故不能使用引用，效率较低
template <typename T>
T temp_var(const T&)
{
    T t;
    return t;
}
//返回 T*类型的无参构造 变量
//虽然传递指针一样需要开销，但相比直接传递变量效率要好
//需要释放指针
template <typename T>
T * temp_ptr(const T&)
{
    T * t=new T;
    return t;
}

int main()
{
    //vector test

    //--------Vector的使用------------//
    //--------------构造函数-----------------------//
    /*
    //使用可变参数模板进行构造
    //空间大小为参数个数，且finish是满的
    STL::Vector<int> v1(1,2,3,4,5);

    //空间大小为10，finish=0
    STL::Vector<int> v2(10);

    //使用数组进行初始化
    //空间大小为 4
    int a[]={1,2,3,5};
    STL::Vector<int> v3(a,4);

    //移动拷贝构造函数

    STL::Vector<int> v4(move(v3));



    //拷贝构造函数
    STL::Vector<int> v5=v4;
    //无参构造函数inish=0
    STL::Vector<int> v6;
    */
    //------------------------iterator-------------------//
    /*
    //使用iterator遍历 read write
    cout<<"v1 :";
    for(STL::Vector<int>::iterator i=v1.begin();i!=v1.end();i++)
        cout<<*i<<",";
    cout<<endl;
    //使用const_iterator遍历 only read
    cout<<"v2 :";
    for(STL::Vector<int>::const_iterator i=v2.begin();i!=v2.end();i++)
        cout<<*i<<",";
    cout<<endl;
    cout<<"v3 :";
    for(STL::Vector<int>::iterator i=v3.begin();i!=v3.end();i++)
        cout<<*(i.index)<<",";
    cout<<endl;

    //使用at(int index)访问元素 only read
    cout<<"v4 :";
    for(int i=0;i<v4.length();i++)
        cout<<v4.at(i)<<",";
    cout<<endl;

    //使用重载运算符[i] 访问元素 read write
    cout<<"v5 :";
    for(int i=0;i<v5.length();i++)
        cout<<v5[i]<<",";
    cout<<endl;

    cout<<"v6 :";
    for(STL::Vector<int>::iterator i=v6.begin();i!=v6.end();i++)
        cout<<*i<<",";
    cout<<endl;
    cout<<endl;
    */
    //--------------------insert-remove------------------//
    /*
    //max_size返回空间大小
    //push_back在末尾插入元素
    //v2{}--->v2{0,1,2,3,4,5,6,7,8,9}
    for(int i=0;i<v2.max_size();i++)
        v2.push_back(i);

    //使用pop_back清空v2 pop_back返回被清空元素
    //v2{0,1,2,3,4,5,6,7,8,9}-->v2{}
    while (v2.isEmpty())
        v2.pop_back();
    //使用insert(int position,value_tpye x)插入元素
    //v1{1,2,3,4,5}-->v1{1,2,6,3,4,5}
    v1.insert(v1.length()/2,6);
    //使用insert(iterator position,value_type x)插入元素
    //v1{1,2,3,4,5}-->v1{1,7,2,6,3,4,5}
    v1.insert(v1.begin()+1,7);

    //使用erase(int position)删除元素
    //v1{1,7,2,6,3,4,5}-->v1{1,7,6,3,4,5}
    v1.erase(2);
    //使用erase(iterator position)删除元素
    //v1{1,7,6,3,4,5}-->v1{1,7,3,4,5}
    v1.erase(v1.begin()+2);

    //使用erase(iterator first,iterator last)删除区间内的元素
    //v4{1,2,3,5}-->v4{3,5}
    v4.erase(v4.begin(),v4.begin()+v4.length()/2);

    //使用erase(int first,int last)删除区间内的元素
    //v5{1,2,3,5}-->v5{1,2}
    v5.erase(v5.length()/2,v5.length());

    //使用empty清空元素
    //令finish=start,并未实际释放内存
    v1.empty();

    //使用clear释放内存
    v1.clear();

    //使用resize(int n)改变空间大小
    //end_of_storage-start=n;
    v1.resize(10);
    //v1{}-->v1{0,1,2,3,4,5,6,7,8,9}
    for(int i=0;i<10;i++)
        v1.push_back(i);
    //使用resize(iterator first,iterator last)改变空间大小
    //finish-start=last-first
    //v1{0,1,2,3,4,5,6,7,8,9}-->v1{0,1,2,3,4}
    v1.resize(5);
    */
    //-------------------嵌套vector----------------------//
    /*
    //嵌套Vector使用
    int count=1;
    STL::Vector<STL::Vector<int>> X(v1,v2,v3,v4,v5,v6);
    for(STL::Vector<STL::Vector<int>>::iterator i=X.begin();i!=X.end();i++){
        cout<<"v"<<count++<<": ";
        for(STL::Vector<int>::iterator j=i->begin();j!=i->end();j++)
            cout<<*j<<",";
        cout<<endl;
    }
    */
    /*
    STL::Vector<int> x1(1,2,3,4,5),x2(5,6),x3(7,8,9),x4(0,10);
    STL::Vector<STL::Vector<int>> X(move(x1),move(x2),move(x3),move(x4));
    for(STL::Vector<STL::Vector<int>>::iterator i=X.begin();i!=X.end();i++)
    {
        cout<<"x : ";
        for(STL::Vector<int>::iterator j=i->begin();j!=i->end();j++)
            cout<<*j<<",";
        cout<<endl;
    }
    cout<<"x1 : ";
    for(STL::Vector<int>::iterator j=x1.begin();j!=x1.end();j++)
        cout<<*j<<",";
    cout<<endl;
    */
    //-------------------Vector move array------------------//
    //-------------Vector Array init -------------------//
/*    int * a=new int[5]{1,2,3,4,5};
    STL::Vector<int> * v=new STL::Vector<int>[4] {
             STL::Vector<int>(1,2,3),
             STL::Vector<int>(4,5,6),
             STL::Vector<int>(7,8,9),
             STL::Vector<int>()
            };
    cout<<"v[]:"<<endl;
    for(int i=0;i<4;i++){
        cout<<"v["<<i<<"] :";
        for(int j=0;j<v[i].length();j++)
            cout<<v[i][j]<<",";
        cout<<endl;
    }
    cout<<endl;
    STL::Vector<int> va(move(a),5);
    cout<<"move(a)  a = "<<a<<endl;
    for(int i=0;i<va.length();i++)
        cout<<va[i]<<",";
    cout<<endl;
    STL::Vector<STL::Vector<int>> V1(move(v),4);
    cout<<"V1:"<<endl;
    for(int i=0;i<V1.length();i++){
        for(int j=0;j<V1[i].length();j++)
            cout<<V1[i][j]<<",";
        cout<<endl;
    }
    cout<<"move(v) v = "<<v<<endl;
*/
    //--------------Vector changed value init move------//
    /*
    cout<<endl;
    STL::Vector<int> * v=new STL::Vector<int>[4] {
             STL::Vector<int>(1,2,3),
             STL::Vector<int>(4,5,6),
             STL::Vector<int>(7,8,9),
             STL::Vector<int>()
            };
    STL::Vector<STL::Vector<int>> V2(move(v[0]),move(v[1]),move(v[2]),move(v[3]));

    cout<<"move v[] ->V2:"<<endl;
    for(int i=0;i<V2.length();i++){
        for(int j=0;j<V2[i].length();j++)
            cout<<V2[i][j]<<",";
        cout<<endl;
    }
    cout<<"v[]:"<<endl;
    for(int i=0;i<4;i++){
        cout<<"v["<<i<<"] :";
        for(int j=0;j<v[i].length();j++)
            cout<<v[i][j]<<",";
        cout<<endl;
    }
    cout<<endl;
    */

    //LinkedList test

    /*
    STL::LinkedList<int> list;


    for(int i=0;i<10;i++){
        list.insert(list.begin(),i);
    }

    cout<<"list1:";
    for(STL::LinkedList<int>::iterator i=list.begin();i!=list.end();i++)
        cout<<*i<<",";
    cout<<endl;

    //移动拷贝构造函数
    STL::LinkedList<int> list2(move(list));
    cout<<"list2:";
    for(STL::LinkedList<int>::iterator i=list2.begin();i!=list2.end();i++)
        cout<<*i<<",";
    cout<<endl;


    STL::LinkedList<int> list3(move(list2)),list4;

    for(int i=0;i<10;i++)
        list3.insert(list3.begin()+i,i);
    for(int i=1;i<10;i++)
        list4.push_front(0);

    int j=10;
    STL::LinkedList<int>::iterator i=list4.begin()+2;
    while(j--)
        i=list4.insert(i,j);

    cout<<"list3:";
    for(STL::LinkedList<int>::iterator i=list3.begin();i!=list3.end();i++)
        cout<<*i<<",";
    cout<<endl;
    cout<<"list4:";
    for(STL::LinkedList<int>::iterator i=list4.begin();i!=list4.end();i++)
        cout<<*i<<",";
    cout<<endl;

    STL::LinkedList<int> list5;
    for(int i=0;i<10;i++)
        list5.push_back(i);
    //LinkedList 拷贝构造函数
    STL::LinkedList<int> list6(list5);
    cout<<"list5:";
    for(STL::LinkedList<int>::iterator i=list5.begin();i!=list5.end();i++)
       *i=0;
    cout<<endl;
    cout<<"list6:";
    for(STL::LinkedList<int>::iterator i=list6.begin();i!=list6.end();i++)
        cout<<*i<<",";
    cout<<endl;


    //LinkedList 嵌套
    STL::LinkedList<STL::LinkedList<int>> L;
    cout<<endl;
    cout<<endl;
    L.push_back(move(list));
    L.push_back(move(list2));
    L.push_back(move(list3));
    L.push_back(list4);
    L.push_back(move(list5));
    L.push_back(list6);
    int count=1;
    int count2=0;
    for(STL::LinkedList<STL::LinkedList<int>>::iterator i=L.begin();i!=L.end();i++){
        cout<<"L"<<count++<<" : ";
        for(STL::LinkedList<int>::iterator j=i->begin();j!=i->end();j++)
        {
            *j=count2++;
            cout<<*j<<",";
        }
        cout<<endl;
    }
    //
    list5=list6;
    cout<<"list:";
    for(STL::LinkedList<int>::iterator i=list.begin();i!=list.end();i++)
       cout<<*i<<",";
    cout<<endl;
    cout<<"list2:";
    for(STL::LinkedList<int>::iterator i=list2.begin();i!=list2.end();i++)
       cout<<*i<<",";
    cout<<endl;
    cout<<"list3:";
    for(STL::LinkedList<int>::iterator i=list3.begin();i!=list3.end();i++)
       cout<<*i<<",";
    cout<<endl;
    cout<<"list4:";
    for(STL::LinkedList<int>::iterator i=list4.begin();i!=list4.end();i++)
       cout<<*i<<",";
    cout<<endl;
    cout<<"list5:";
    for(STL::LinkedList<int>::iterator i=list5.begin();i!=list5.end();i++)
       cout<<*i<<",";
    cout<<endl;
    cout<<"list6:";
    for(STL::LinkedList<int>::iterator i=list6.begin();i!=list6.end();i++)
       cout<<*i<<",";
    cout<<endl;

    */
    //使用数组移动拷贝构造函数必须为指针型 Type * i
    //而不能是Type i[] 否则将调用 constructor(const Type* array ,n)

    /*int * a=new int[10]{1,1,2,1,1,1,5,1,1,1};
    //STL::Vector<int> v(move(a),6);
    //cout<<a<<endl;
    STL::LinkedList<int> l1(a,10);

    for(STL::LinkedList<int>::iterator i=l1.begin();i!=l1.end();i++)
        cout<<*i<<",";
    cout<<endl;

    STL::LinkedList<int> l2(move(a),10);
    l2.unique();
    cout<<"L2 : ";
    for(STL::LinkedList<int>::iterator i=l2.begin();i!=l2.end();i++)
        cout<<*i<<",";
    cout<<endl;*/






    /*BinayTree<int> tree(isMax);
    tree.insert(5);
    tree.insert(4);
    tree.insert(6);
    tree.insert(2);
    tree.insert(3);
    tree.insert(7);
    tree.insert(8);
    tree.insert(0);
    tree.insert(9);
*/
    //cout<<*tree.find(2)<<endl;

//sort test
/*
STL::Vector<string> v(1000);
char ch[6];
for(int i=0;i<1000;++i){
    ch[0]=(char)(std::rand()%26+'a');
    ch[1]=(char)(std::rand()%26+'a');
    ch[2]=(char)(std::rand()%26+'a');
    ch[3]=(char)(std::rand()%26+'a');
    ch[4]=(char)(std::rand()%26+'a');
    ch[5]='\0';
    v.push_back(ch);
}
//STL::out_foreach(v.begin(),v.end(),"sort:\n"," ",10);

std::cout<<"v length :"<<v.length()<<std::endl;

struct timeval tpstart,tpend;

long long timeuse;

gettimeofday(&tpstart,NULL);

//STL::purity_quick_sort(v.begin(),v.end());
STL::quick_sort(v.begin(),v.end());
//STL::insert_sort(v.begin(),v.end());

gettimeofday(&tpend,NULL);

timeuse=(1000000*(tpend.tv_sec-tpstart.tv_sec) + tpend.tv_usec-tpstart.tv_usec);

std::cout<<timeuse<<"us"<<endl;
STL::out_foreach(v.begin(),v.end(),"sort :\n"," ",10);
*/
 /*   return 0;
}
*/
/*cout<<"stack test:"<<endl;

STL::Stack<int> stack(10);
//cout<<"stack isfull "<<stack.isfull()<<endl;
//cout<<"stack isempty "<<stack.isEmpty()<<endl;
//cout<<"stack length "<<stack.length()<<endl;
//cout<<"stack top value "<<stack.top()<<endl;
for(int i=0;!stack.isfull();i++){
    stack.push(i);
    //cout<<"stack is full "<<stack.isfull()<<endl;
    //cout<<"stack is empty "<<stack.isEmpty()<<endl;
    //cout<<"stack length "<<stack.length()<<endl;
    //cout<<"stack top value "<<stack.top()<<endl;
}

cout<<"--------copy_stack-----------"<<endl;
STL::Stack<int> s1(stack);
for(int i=0;s1.isEmpty();i++)
    cout<<s1.pop()<<endl;

cout<<"---------------------------"<<endl;


cout<<"-------move-copy_stack-----------"<<endl;
STL::Stack<int> s(move(stack));
for(int i=0;s.isEmpty();i++)
    cout<<s.pop()<<endl;

cout<<"---------------------------"<<endl;

cout<<"_____stack______"<<endl;
for(int i=0;stack.isEmpty();i++){
    cout<<stack.pop()<<endl;
cout<<"stack is full "<<stack.isfull()<<endl;
cout<<"stack is empty "<<stack.isEmpty()<<endl;
cout<<"stack length "<<stack.length()<<endl;
cout<<"stack top value "<<stack.top()<<endl;
}
cout<<"___________"<<endl;
*/
//LinkedList嵌套vector sort
/*
STL::Vector<int> * v=new STL::Vector<int>[5] {
         STL::Vector<int>(2,1,3),
         STL::Vector<int>(2,3,4,5,6),
         STL::Vector<int>(7,5,4,3,9,7),
         STL::Vector<int>(),
         STL::Vector<int>(1,5),
        };

STL::LinkedList<STL::Vector<int>> list(v,5);
for(auto i=list.begin();i!=list.end();i++)
    STL::out_foreach((*i).begin(),(*i).end());

cout<<"sort:"<<endl;
for(auto i=list.begin();i!=list.end();i++)
    STL::purity_quick_sort(i->begin(),i->end());

int count=0;
for(auto i=list.begin();i!=list.end();i++){
    cout<<"v"<<++count<<": ";
    for(auto j=i->begin();j!=i->end();j++)
        cout<<*j<<",";
    cout<<endl;
}
*/
#endif // TEST_H
