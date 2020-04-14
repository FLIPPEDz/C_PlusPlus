#pragma once
#include "Header.h"
//15-1
//虚成员就是虚函数
//基类中的虚成员希望其派生类定义自己的版本

//15-2
//基类通过protected访问说明符禁止其他用户访问，让派生类有权限访问该成员
//private禁止其他用户和派生类访问

//15-3
//参照书本定义

//15-4
//a)一个类不能派生本身
//b)正确
//c)派生类声明中包含类名但是不包含它的派生列表


//15-5
//class Bulk_quote final :public Quote
//{
//public:
//	Bulk_quote() = default;
//	Bulk_quote(const string& book, double p, size_t qty, double disc) :Quote(book, p),
//		min_qty(qty), discount(disc) { }
//
//	double net_price(size_t n) const override;
//
//private:
//	size_t min_qty = 0;
//	double discount = 0.0;
//};

//15-6
//正确
//Quote item("item",20.0);
//Bulk_quote bulk("bulk", 15.0, 50, 0.1);
//
//print_total(cout, item, 50);
//print_total(cout, bulk, 60);

//15-7
//double Bulk_quote::net_price(size_t n) const 
//{
	//if (min_qty = < n <= max_qty)
	//	return n*(1 - discount)*price;
	//else if (n < min_qty)
	//	return n*price;
	//else
	//return max_qty*(1 - discount)*price + (n - max_qty)*price
//}

//15-8
//静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型。
//动态类型则是在变量或者表达式表示的内存中的对象类型。

//15-9
//派生类绑定在基类的引用或指针上

//15-10
//ifstream从istream中派生而来,因此，ifstream对象“是”istream

//15-11
//virtual void debug()const { cout <<  "Quote" << "-isbn:"<< bookNo<< "-price:"<< price << endl; }
//void debug()const override {
//cout << "Bulk_quote" << endl;
//Quote::debug();
//cout << "-min_qty:" << min_qty << "-discount:" << discount << endl; }

//15-12
//有override是表示对其基类函数的覆盖，final是表示此函数不能再被其他的函数所覆盖

//15-13
//有问题，派生类的print(os)会造成递归死循环，应加上作用域限定符改成base::print(os)

//15-14
//(a)：调用基类版本的print()函数
//(b)：调用派生类版本的print()函数
//(c)：调用基类的name()函数
//(d)：调用派生类中基类部分的name()函数
//(e)：调用基类版本
//(f)：调用派生类版本

//15-15 and 15-16
//class Disc_quote :public Quote
//{
//public:
//	Disc_quote() = default;
//	Disc_quote(const string& book, double p, size_t qty, size_t max_qty, double disc) :Quote(book, p),
//		quantity(qty), discount(disc), max_qty(max_qty) { }
//
//	double net_price(size_t) const = 0;
//
//protected:
//	size_t quantity = 0;
//	double discount = 0.0;
//	size_t max_qty = 0;
//};
//class Bulk_quote :public Disc_quote
//{
//public:
//	Bulk_quote() = default;
//	Bulk_quote(const string& book, double p, size_t qty, size_t max_qty, double disc) :
//		Disc_quote(book, p, qty, max_qty, disc) { }
//
//	double net_price(size_t) const override;
//
//};
//double Bulk_quote::net_price(size_t n) const
//{
//	if (quantity <= n <= max_qty)
//		return n*(1 - discount)*price;
//	else if (n < quantity)
//		return n*price;
//	else
//		return max_qty*(1 - discount)*price + (n - max_qty)*price;
//}

//15-17
//“Disc_quote”: 不能实例化抽象类

//15-18
//Base* p = &d1; 合法
//p = &d2;		 不合法
//p = &d3;		 不合法
//p = &d4;       合法
//p = &d5;		 不合法
//p = &d6;		 不合法
//只有当D公有继承B时，用户代码才能使用派生到基的转换


//15-19
//struct Derived_from_Private : public Priv_Derv {
//	// void memfcn(Base &b) { b = *this; } // error: 'Base' not accessible because 'Priv_Derv' uses 'private' to inherit from 'Base'
//};

//15-21,15-22
//class Quote
//{
//public:
//	Quote() = default;
//	Quote(const string& book, double sales_price) :bookNo(book), price(sales_price) { }
//	string isbn() const { return bookNo; }
//	virtual double net_price(size_t n) const = 0;
//
//	virtual ~Quote() = default;
//private:
//	string bookNo;
//protected:
//	double price = 0.0;
//};
//
//class Normal_quote : public Quote
//{
//public:
//	Normal_quote() = default;
//	Normal_quote(const string& book, double p, size_t qty):Quote(book,p),
//		qty(qty){ }
//
//	double net_price(size_t n) const override
//	{
//		return qty*price;
//	}
//
//protected:
//	size_t qty = 0;
//};
//
//class Disc_quote :public Normal_quote
//{
//public:
//	Disc_quote() = default;
//	Disc_quote(const string& book, double p, size_t qty, double disc) :Normal_quote(book, p,qty),discount(disc)
//	{ }
//
//	double net_price(size_t n) const override
//	{
//		return qty*price*(1-discount);
//	}
//
//protected:
//	double discount = 0.0;
//};

//15-23
//去掉fcn的参数，
//1：确定其静态类型，必然是一个类类型
//2：在其静态类型的类中查找该成员，找不到，则向外层的基类移动，再没有，编译器报错
//3：找到了该成员，进行常规的类型检查，编译器再根据其是否是虚函数产生不同的代码
//若是虚函数且为引用或者指针类型的调用，则需要进行动态绑定，
//编译器产生的运行代码在运行时将决定到底运行该虚函数的哪个版本，依据其动态类型
//若不是虚函数或是没有指针引用调用，则产生常规调用
//class Base
//{
//public:
//	virtual int fcn() {
//		cout << "Base" << endl;
//		return 0;
//	}
//};
//class Drived1 :public Base
//{
//public:
//	using Base::fcn;
//	int  fcn(int) {
//		cout << "Drived1" << endl;
//		return 0;
//	}
//	virtual void f2()
//	{
//		cout << "Drived1" << endl;
//	}
//};
//class Drived2 :public Drived1
//{
//public:
//	int  fcn(int) {
//		cout << "Drived2" << endl;
//	}
//	int fcn() {
//		cout << "Drived2" << endl;
//		return 0;
//	}
//	void f2()
//	{
//		cout << "Drived2" << endl;
//	}
//
//};

//15-24
//基类需要虚析构函数，需要动态销毁对象

//15-25
//派生类可以合成默认构造函数，无法合成默认构造函数，因为基类已经定义了构造函数所以默认构造函数是删除的
//class Quote
//{
//public:
//	Quote() = default;
//	Quote(const string& book, double sales_price) :bookNo(book), price(sales_price) {
//		cout << "Quote(const string& book, double sales_price)" << endl;
//	}
//	Quote(const Quote&);
//	string isbn() const { return bookNo; }
//	virtual double net_price(size_t n) const
//	{
//		return n*price;
//	};
//	virtual ~Quote() = default;
//
//	virtual void debug()const { cout << "Quote" << "-isbn:" << bookNo << "-price:" << price << endl; }
//private:
//	string bookNo;
//protected:
//	double price = 0.0;
//};
//Quote::Quote(const Quote& rhs)
//{
//	cout << "Quote(const Quote& rhs)" << endl;
//	bookNo = rhs.bookNo;
//	price = rhs.price;
//}
//class Bulk_quote : public Quote
//{
//public:
//	Bulk_quote() = default;
//	Bulk_quote(const string& book, double p, size_t qty, double disc) :Quote(book, p),
//		min_qty(qty), discount(disc) {
//		cout << "Bulk_quote(const string& book, double p, size_t qty, double disc)" << endl;
//	}
//	Bulk_quote(const Bulk_quote&rhs);
//	double net_price(size_t n) const override;
//
//	void debug()const override {
//		cout << "Bulk_quote" << endl;
//		Quote::debug();
//		cout << "-min_qty:" << min_qty << "-discount:" << discount << endl;
//	}
//private:
//	size_t min_qty = 0;
//	double discount = 0.0;
//};
//Bulk_quote::Bulk_quote(const Bulk_quote&rhs) :Quote(rhs)
//{
//	cout << "Bulk_quote(const Bulk_quote&rhs)" << endl;
//	min_qty = rhs.min_qty;
//	discount = rhs.discount;
//}
//double Bulk_quote::net_price(size_t n) const
//{
//	if (n >= min_qty)
//		return n*(1 - discount)*price;
//	else
//		return n*price;
//}

//15-27
//class Bulk_quote :public Disc_quote
//{
//public:
//	using Disc_quote::Disc_quote;
//	Bulk_quote() = default;
//	Bulk_quote(const string& book, double p, size_t qty, size_t max_qty, double disc) :
//		Disc_quote(book, p, qty, max_qty, disc) { }
//
//	double net_price(size_t) const override;
//
//};

//15-28
//namespace EX26 {
//	using std::string;
//	using std::cout; using std::endl;
//
//	class Quote {
//	public:
//		Quote() {
//		}
//
//		Quote(const string &b, double p) : bookNo(b), price(p) {
//		}
//
//		Quote(const Quote &rhs) : bookNo(rhs.bookNo), price(rhs.price) {
//		}
//
//		Quote& operator=(const Quote &rhs) {
//			price = rhs.price;
//			bookNo = rhs.bookNo;
//			return *this;
//		}
//
//		Quote(Quote &&rhs) noexcept : bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) {
//		}
//
//		Quote& operator=(Quote &&rhs) noexcept {
//			bookNo = std::move(rhs.bookNo);
//			price = std::move(rhs.price);
//			return *this;
//		}
//
//		virtual ~Quote() {
//		}
//
//		string isbn() const { return bookNo; }
//		virtual double net_price(size_t n) const { return n * price; }
//	private:
//		string bookNo;
//	protected:
//		double price = 0.0;
//	};
//
//	class Bulk_quote : public Quote {
//	public:
//		Bulk_quote() {
//		}
//
//		Bulk_quote(const string &b, double p, size_t q, double d) : Quote(b, p), min_qty(q), discount(d) {
//		}
//
//		Bulk_quote(const Bulk_quote& rhs) : Quote(rhs), min_qty(rhs.min_qty), discount(rhs.discount) {
//		}
//
//		Bulk_quote& operator=(const Bulk_quote& rhs) {
//			Quote::operator=(rhs);
//			min_qty = rhs.min_qty;
//			discount = rhs.discount;
//			return *this;
//		}
//
//		Bulk_quote(Bulk_quote &&rhs) noexcept : Quote(rhs), min_qty(std::move(rhs.min_qty)),
//			discount(std::move(rhs.discount)) {
//		}
//
//		Bulk_quote& operator=(Bulk_quote &&rhs) noexcept {
//			Quote::operator=(rhs);
//			min_qty = std::move(rhs.min_qty);
//			discount = std::move(rhs.discount);
//			return *this;
//		}
//
//		virtual ~Bulk_quote() {
//		}
//		virtual double net_price(size_t cnt) const override {
//			if (cnt >= min_qty) return cnt * (1 - discount) * price;
//			else return cnt * price;
//		}
//	protected:
//		size_t min_qty = 0;
//		double discount = 0.0;
//	};
//}
//
//int main(int argc, char* argv[])
//{
//	using namespace EX26;
//	vector<Quote> vecQuote;
//
//
//	Bulk_quote bulk_quote1("Bulk_quote1", 50, 4, 0.1);
//	Bulk_quote bulk_quote2("Bulk_quote2", 50, 3, 0.2);
//
//	cout << bulk_quote1.net_price(5) + bulk_quote2.net_price(5) << endl;
//
//	vecQuote.push_back(bulk_quote1);
//	vecQuote.push_back(bulk_quote2);
//
//	double total = accumulate(vecQuote.begin(), vecQuote.end(), 0.0, [](double ret, const Quote&obj) {
//		return ret += obj.net_price(5);
//	});
//	cout << total << endl;
//
//	return 0;
//}

//15-29
//using namespace EX26;
//vector<shared_ptr<Quote>> vecQuote;
//
//
//shared_ptr<Bulk_quote> bulk_quote1 = make_shared<Bulk_quote>("Bulk_quote1", 50, 4, 0.1);
//shared_ptr<Bulk_quote> bulk_quote2 = make_shared<Bulk_quote>("Bulk_quote2", 50, 3, 0.2);
//
//cout << bulk_quote1->net_price(5) + bulk_quote2->net_price(5) << endl;
//
//vecQuote.push_back(bulk_quote1);
//vecQuote.push_back(bulk_quote2);
//
//double total = accumulate(vecQuote.begin(), vecQuote.end(), 0.0, [](double ret, shared_ptr<Quote>obj) {
//	return ret += obj->net_price(5);
//});
//cout << total << endl;
