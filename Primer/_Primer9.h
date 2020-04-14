#pragma once
#include "Header.h"

//9-1
//set deque vector

//9-2
//list<deque<int>> tmp;

//9-3
//指向同一个容器中的元素
//end不在begin之前

//9-5
//bool _find(const vector<int>& vec, int val)
//{
//	for (const auto& i:vec)
//	{
//		if (i==val)
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

//9-5
//const int & _find(const vector<int>& vec, int& val)
//{
//	for (const auto& i : vec)
//	{
//		if (i == val)
//		{
//			return i;
//		}
//	}
//
//
//	return val;
//}

//vector<int>::iterator find(vector<int>::iterator beg, vector<int>::iterator end, int value)
//{
//	for (auto iter = beg; iter != end; ++iter)
//		if (*iter == value) return iter;
//	return end;
//}

//9-6
//不支持<，修改成itr1!=itr2

//9-7
//vector<int>::size_type

//9-8
//list<string>::iterator || list<string>::const_iterator // read
//list<string>::iterator // write

//9-9
//需要写访问用begin,不需要用begin

//9-10
//auto it2 = v2.begin();error C3538: 在声明符列表中，“auto”必须始终推导为同一类型
//it1 is vector<int>::iterator
//it2, it3 and it4 are vector<int>::const_iterator


//9-11
//vector<int> vec ;vector<int> vec {};vector<int> vec={} ;vector<int> vec(10) ;vector<int> vec(10,5) ;
//vector<int> vec(other_vec); <int> vec(other_vec.begin(), other_vec.end());

//9-12
//直接拷贝整个容器，两个容器类型及元素类型匹配；
//由迭代器对指定的元素范围，不要求容器类型相同，且新容器和原容器中的元素类型可以不同

//9-13
//list<int> st{10,20,30,40,50};vector<double> vec(st.begin(), st.end());
//vector<int> vec{ 10,20,30 };vector<double> vec2(vec.begin(), vec.end());

//9-14
//list<char*> st; st.assign(10, "hello"); vector<string> vec(10); vec.assign(st.begin(), st.end());

//9-15
//std::vector<int> vec1{ 1, 2, 3, 4, 5 };
//std::vector<int> vec2{ 1, 2, 3, 4, 5 };
//std::vector<int> vec3{ 1, 2, 3, 4 };
//std::boolalpha:Enables the boolalpha flag in the stream str
//std::cout << std::boolalpha << (vec1 == vec2) << std::endl;
//std::cout << (vec1 == vec3) << std::endl;

//9-16
//std::list<int> list{1, 2, 3, 4, 5};
//std::vector<int> vec1{ 1, 2, 3, 4, 5 };
//std::vector<int> vec2{ 1, 2, 3, 4 };
//
//std::cout << std::boolalpha
//<< (std::vector<int>(list.begin(), list.end()) == vec1)
//<< std::endl;
//std::cout << std::boolalpha
//<< (std::vector<int>(list.begin(), list.end()) == vec2)
//<< std::endl;

//9-17
//First, there must be the identical container and same type holded. 
//Second,the type held must support relational operation.


//9-18
//deque<string> input;
//for (string str; cin >> str; input.push_back(str));
//for (auto iter = input.cbegin(); iter != input.cend(); ++iter)
//cout << *iter << endl;

//9-19
//    list<string> input;
//for (string str; cin >> str; input.push_back(str));
//for (auto iter = input.cbegin(); iter != input.cend(); ++iter)
//cout << *iter << endl;

//9-20
//list<int> l{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//deque<int> odd, even;
//for (auto i : l) (i & 0x1 ? odd : even).push_back(i);

//9-21
//不需要改变

//9-22
//insert()操作有返回值，此题为无限循环，且插入元素后，mid做为一个引用会失效。

//9-23
//同一个元素

//9-24:vs2015
//std::vector<int> v;
//std::cout << v.at(
//	0); // abort
//std::cout << v[0];       // terminating with uncaught exception of type std::out_of_range
//std::cout << v.front();  // 迭代器无效
//std::cout << *v.begin(); // 迭代器无效
