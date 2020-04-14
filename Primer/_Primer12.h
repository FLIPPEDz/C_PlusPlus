#pragma once
#include "Header.h"

//12-1
//4,4

//12-2
//class StrBlob
//{
//public:
//	typedef vector<string>::size_type size_type;
//
//	StrBlob();
//	StrBlob(initializer_list<string>);
//	size_type size() const { return data->size(); }
//	bool empty() const { return data->empty(); }
//
//	void push_back(const string &t) { data->push_back(t); }
//	void pop_back();
//
//	string& front() const;
//	string& back() const;
//private:
//	shared_ptr<vector<string>> data;
//
//	void check(size_type i, const string & msg) const;
//
//};
//
//StrBlob::StrBlob() : data(make_shared<vector<string>>())
//{ }
//
//StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il))
//{ }
//
//void StrBlob::check(size_type i, const string & msg) const
//{
//	if (i >= data->size())
//	{
//		throw out_of_range(msg);
//	}
//}
//
//string& StrBlob::front() const
//{
//	check(0, "empty!");
//	return data->front();
//}
//
//string&StrBlob::back() const
//{
//	check(0, "empty!");
//	return data->back();
//}
//
//void StrBlob::pop_back()
//{
//	check(0, "empty!");
//	data->pop_back();
//}


//12-3
//不能加上虽然作为数据成员的data是一个指针，本身的指向是没有变的，是可以加const。
//但是函数写成const版本，StrBlob常量对象就能添加删除元素了

//12-4
//size_t为无符号类型,输入任何参数它会转换成大于0的数字

//12-5
//explicit的作用就是抑制构造函数的隐式转换
//优点：不会自动的进行类型转换，必须清楚的知道类类型
//缺点：必须用构造函数显示创建一个对象，不够方便简单

//12-6
//vector<int>* get_vec()
//{
//	return new vector<int>;
//}
//
//void get_val(istream& is,vector<int>* vec)
//{
//	int tmp = 0;
//	while (is>>tmp)
//	{
//		vec->push_back(tmp);
//	}
//}
//
//void prin_vec(vector<int>& vec)
//{
//	for (auto i:vec)
//	{
//		cout << i << endl;
//	}
//}
//
////test_code
//vector<int>* vec = get_vec();
//get_val(cin, vec);
//prin_vec(*vec);
//delete vec;

//12-7
//shared_ptr<vector<int>> get_vec()
//{
//
//	return make_shared<vector<int>>();
//}
//
//void get_val(istream& is, shared_ptr<vector<int>> vec)
//{
//	int tmp = 0;
//	while (cin>>tmp)
//	{
//		vec->push_back(tmp);
//	}
//}
//
//void prin_val(const shared_ptr<vector<int>> vec)
//{
//	for (const auto& i : *vec)
//	{
//		cout << i << endl;
//	}
//}


//12-8
//“int *”: 将值强制为布尔值“true”或“false”，其指向的动态内存空间将无法得到释放
//bool b()
//{
//	int* p = new int;
//
//	return p;
//}

//12-9
//q指向的内存发生泄漏
//q2，r2为智能指针,r2引用计数为零释放资源


//12-10
//正确，拷贝生成临时对象引用计数加一
void proce(shared_ptr<int> p)
{

}

//12-11
//利用P的get()函数得到的内置指针来初始化一个临时的智能指针，一旦调用结束，
//该临时指针被销毁，内置指针所指对象内存会被释放，使得p变为空悬指针

//12-12
//(a)：合法，处理sp指针所指向内容，赋值的方式传递参数，处理完毕后内存不会被释放
//(b)：不合法，参数必须是智能指针int类型
//(c)：同上
//(d)：合法，处理完毕后内存会被释放

//12-13
//删除p之后，会导致p指向的内存被释放，
//此时sp就会变成空悬指针，在sp指针被销毁时，该块内存会被二次delete，
//执行后产生错误：double free

//12-14
//struct destination
//{};
//struct connection
//{};
//connection connect(destination* pDest)
//{
//	std::shared_ptr<connection> pConn(new connection());
//	return *pConn;
//}
//void disconnect(connection pConn)
//{
//}
//void end_connection(connection* pConn)
//{
//	disconnect(*pConn);
//}
//void f(destination& d)
//{
//	connection c = connect(&d);
//
//	shared_ptr<connection>p(&c, [](connection* p) {disconnect(*p);});
//}

//12-15
//void f(destination& d)
//{
//	connection c = connect(&d);
//
//	shared_ptr<connection>p(&c, [](connection* p) {disconnect(*p);});
//}

//12-16
//unique_ptr<int> p1(new int(1234));
//unique_ptr<int> p2(p1); //尝试引用已删除的函数
//unique_ptr<int> p3;
//p3 = p1;  //尝试引用已删除的函数

//12-17
//IntP p0(ix); //无法将参数 1 从“int”转换为“std::nullptr_t
//IntP p1(pi); //不合法,p1离开作用域会释放对象，但对象不是用new分配的
//IntP p2(pi2); //不合法,p2释放对象，会使原始指针悬空
//IntP p3(&ix);      //不合法,ix不是new分配的
//IntP p4(new int(2048)); //合法
//IntP p5(p2.get());  //不合法,双重释放

//12-18
//release()函数的作用就是放弃对指针指向对象的控制权，但shared_ptr是多对一的关系，
//其他的智能指针仍然可以删除这个对象

