#pragma once
#include "Header.h"
//7.31
class Y;  //声明
class X
{

	Y* y = nullptr;
};

class Y
{
	X x;
};

//7.32
class SCreen;

class Window_mgr
{
public:
	void clear(SCreen&);

};

class SCreen
{
	friend void Window_mgr::clear(SCreen&);
private:
	string str = "hello";
};


void Window_mgr::clear(SCreen& s)
{
	s.str = string(100, ' ');
}

//7-34
//1.名字查找顺序：由内而外、自上而下
//2.类的定义处理步骤：首先编译成员的声明，直到类全部可见是再编译函数体
//即成员函数在类的声明全部处理完之后才会被定义，所以可以调用函数中定义的任何名字
//3.在类中，类型名要特殊处理，最好是定义在类的一开始，并且不能与外层作用域中同名
//answer:pos未定义

//7-35
//Type有两种类型，应将最后一个函数的Type也声明为Exercise::作用域，因为返回值是double类型


//7-36
//交换rem,base顺序

//7-37
//Sales_data(istream& is) { read(is, *this); }; 输入的值
//Sales_data(string &s):bookNo(s){ }; string bookNo=s;unsigned units_sold = 0;double revenue = 0.0;

//7-38
//Sales_data(istream& is=cin) { read(is, *this); };

//7-39
//不合法,编译器不知道调用哪个

//7-43
//NoDefault不存在默认构造函数
//class NoDefault
//{
//	NoDefault(int &);
//};
//
//
//class C
//{
//public:
//	C() { };
//
//private:
//	NoDefault no;
//};

//7-44
//不合法“NoDefault::NoDefault”: 没有合适的默认构造函数可用

//7-45
//如果不存在NoDefault合法

//7-46
//（a）：错误，类本身不提供构造函数时，编译器会自动合成一个默认构造函数
//（b）：错误，为成员提供默认值的构造函数也成为默认构造函数
//（c）：错误
//（d）：错误，当类没有定义构造函数时，才会默认编译器生成默认构造函数。

//7-47
//优点不将构造函数设置为explicit可能会在有些时候使用较为方便
//缺点可能造成对string的使用与初衷不一致


//7-49
//a.编译器会根据s隐式地调用Sales_data的构造函数，生成一个临时的Sales_data对象，然后传递给combine
//b.编译器报错error: invalid initialization of non - const reference of type 'Sales_data&' 
//from an rvalue of type 'Sales_data'，string可以转为一个临时的Sales_data对象，但不能转化为Sales_data类型的引用。
//c.error : assignment of member 'Sales_data::units_sold' in read - only object，声明最后的const会禁止函数对值做出改变，这个错误与参数无关。


//7-51
//防止隐式的转换
//int getSize(const std::vector<int>&);
//It's very confused.
//getSize(34);
//it is very natural.
//void setYourName(std::string); // declaration.
//setYourName("pezy"); 


//7-52
//struct Sale_data
//{
//	string bookNo;
//	unsigned units_sold;
//	double revenue;
//};

//7-54
//shouldn't, cause a constexpr function must contain exactly one return statement

//7-55
//std::string is not a literal type, and it can be verified by following codes
//struct Data
//{
//	int ival;
//	string s;
//};
//cout << is_literal_type<Data>::value << endl;  //0

//7-56
//What is a static class member ?
//A class member that is associated with the class, rather than with individual objects of the class type.
//What are the advantages of static members ?
//each object can no need to store a common data.And if the data is changed, each object can use the new value.
//How do they differ from ordinary members ?
//a static data member can have incomplete type.
//we can use a static member as a default argument.
