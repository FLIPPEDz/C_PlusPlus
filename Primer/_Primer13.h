#pragma once
#include "Header.h"

//13-1
//一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值
//用=定义变量;将一个对象作为实参传递给一个非引用形参;从一个返回类型为非引用类型的函数返回一个对象;
//用花括号列表初始化一个数组中的元素或一个聚合类中的成员

//13-2
//参数不是引用类型，调用永远不会成功

//13-3
//when we copy a StrBlob, the shared_ptr member's use_count add one.
//when we copy a StrBlobPrts, the weak_ptr member's use_count isn't changed.
//(cause the count belongs to shared_ptr)


//13-4
//Point foo_bar(Point arg) // 1
//{
//	Point local = arg, *heap = new Point(global); // 2, 3
//	*heap = local;
//	Point pa[4] = { local, *heap }; // 4, 5
//	return *heap; // 6
//}

//13-5
//class HasPtr
//{
//
//public:
//	HasPtr(const string &s= string()):ps(new string(s)),i(0){ }
//
//	HasPtr(const HasPtr& s):ps(new string(*s.ps)),i(s.i){ }
//private:
//	string *ps;
//	int i;
//};

//13-6
//函数;将一个对象赋予同类型的另一个对象时;将右侧对象的每个非静态成员分配给左侧对象的相应成员;
//如果一个类未定义自己的拷贝赋值运算符

//13-7
//所有成员的赋值会发生，两个StrBlob中智能指针所指对象内存相同，计数器加一，
//两个StrBlobPtr中弱指针所指对象内存相同，计数器不变


//13-8
//class HasPtr
//{
//
//public:
//	HasPtr& operator=(const HasPtr& rhs)
//	{
//		if (this==&rhs)
//		{
//			return *this;
//		}
//
//		string* new_ps = new string(*rhs.ps);
//		delete ps;
//		ps = new_ps;
//		i = rhs.i;
//
//		return *this;
//	}
//private:
//	string *ps;
//	int i;
//};

//13-9
//是类的一个成员函数,名字由波浪号接类名构成;复制构造函数和复制赋值运算符一样，对于某些类，
//合成析构函数被定义为不允许销毁该类型的对象。否则，合成的析构函数具有空的函数体;一个类未定义自己的析构函数时

//13-10
//所有对象的数据成员被销毁，智能指针的计数减一，所有对象的数据成员被销毁，弱指针不影响计数器



//13-11
//class HasPtr
//{
//
//public:
//	HasPtr& operator=(const HasPtr& rhs)
//	{
//		if (this==&rhs)
//		{
//			return *this;
//		}
//
//		string* new_ps = new string(*rhs.ps);
//		delete ps;
//		ps = new_ps;
//		i = rhs.i;
//
//		return *this;
//	}
//
//	~HasPtr() { delete ps; }
//private:
//	string *ps;
//	int i;
//};


//13-12
//3 times. There are accum, item1 and item2.

//13-14
//a的mysn

//13-15
//Yes, the output will be changed. cause we don't use the synthesized copy-control members rather than own defined.
//The output will be three different numbers.

//13-16
//Yes, the output will be changed. cause the function f haven't any copy operators.
//Thus, the output are the same when pass the each object to f.

//13-18
//class Employee
//{
//	Employee()
//	{
//		myid = id++;
//	}
//
//	Employee(const string& name)
//	{
//		myname = name;
//		myid = id++;
//	}
//
//private:
//	string myname;
//	int myid;
//	static int id;
//};
//
//int Employee::id = 1;


//13-19
//不需要拷贝构造函数，怎么可能有人一样。将其声明为 =delete
//class Employee
//{
//	Employee()
//	{
//		myid = id++;
//	}
//
//	Employee(const string& name)
//	{
//		myname = name;
//		myid = id++;
//	}
//
//	Employee(const Employee&) = delete;
//	Employee& operator=(const Employee&) = delete;
//
//private:
//	string myname;
//	int myid;
//	static int id;
//};
//
//int Employee::id = 1;

//13-20 13-21 补

//13-22
//class HasPtr
//{
//	HasPtr(const string& s=string()) :str(new string(s)), value(0) 
//	{ }
//	HasPtr(const HasPtr& rhs):str(new string(*rhs.str)),value(rhs.value)
//	{
//	}
//	HasPtr& operator=(const HasPtr&rhs)
//	{
//		string* tmp = new string(*rhs.str);
//		delete str;
//		str = tmp;
//		value = rhs.value;
//		return *this;
//	}
//	~HasPtr()
//	{
//		delete str;
//	}
//private:
//	string* str;
//	int value;
//};

//13-24
//内存泄漏;浅拷贝

//13-25
//动态分配的内存由shared_ptr管理，析构函数之后会自动判断进行释放，所以不需要自定义版本的析构函数

//13-27
//class HasPtr
//{
//public:
//	HasPtr(const string& s = string()) :str(new string(s)), value(0), use(new size_t(1))
//	{ }
//	HasPtr(const HasPtr& rhs) :str(rhs.str), value(rhs.value), use(rhs.use)
//	{
//		++*use;
//	}
//	HasPtr& operator=(const HasPtr& rhs);
//	~HasPtr();
//
//private:
//	string* str;
//	int value;
//	size_t *use;
//};
//inline
//HasPtr& HasPtr::operator=(const HasPtr& rhs)
//{
//	++*rhs.use;
//	if (--*use == 0)
//	{
//		delete str;
//		delete use;
//	}
//	str = rhs.str;
//	value = rhs.value;
//	use = rhs.use;
//	return *this;
//}
//inline
//HasPtr::~HasPtr()
//{
//	if (--*use == 0)
//	{
//		delete str;
//		delete use;
//	}
//}


//13-28
//class TreeNode {
//	string  val;
//	TreeNode *left;
//	TreeNode *right;
//	int* use;
//public:
//	TreeNode(const string& x=string()) :
//		val(x), left(NULL), right(NULL),use(new int(1)) {
//	}
//
//	TreeNode(const TreeNode& rhs):val(rhs.val),left(rhs.left),right(rhs.right)
//	{
//		++*use;
//	}
//	TreeNode& operator=(const TreeNode& rhs)
//	{
//		++*rhs.use;
//		if (--*use==0)
//		{
//			if (left)
//			{
//				delete left;
//				left = nullptr;
//			}
//			if (right)
//			{
//				delete right;
//				right = nullptr;
//			}
//			delete use;
//			use = nullptr;
//		}
//		val = rhs.val;
//		left = rhs.left;
//		right = rhs.right;
//		use = rhs.use;
//		return *this;
//	}
//	~TreeNode()
//	{
//		if (--*use==0)
//		{
//			if (left)
//			{
//				delete left;
//				left = nullptr;
//			}
//			if (right)
//			{
//				delete right;
//				right = nullptr;
//			}
//			delete use;
//			use = nullptr;
//		}
//	}
//};
//
//class BinStrTree
//{
//public:
//	BinStrTree(const string str=string()):root(new TreeNode(str)){ }
//	BinStrTree(const BinStrTree& rhs):root(new TreeNode(*rhs.root)){ }
//	BinStrTree& operator=(const BinStrTree& rhs);
//	~BinStrTree();
//private:
//	TreeNode* root;
//};
//
//inline
//BinStrTree& BinStrTree::operator=(const BinStrTree& rhs)
//{
//	TreeNode* new_root = new TreeNode(*rhs.root);
//	delete root;
//	root = new_root;
//
//	return *this;
//}
//
//inline 
//BinStrTree::~BinStrTree()
//{
//	delete root;
//}

//13-29
//不会
//swap(lhs.ps, rhs.ps); feed the version : swap(std::string*, std::string*) 
//and swap(lhs.i, rhs.i); feed the version : swap(int, int). 
//Both them can't call swap(HasPtr&, HasPtr&). Thus, the calls don't cause a recursion loop.

//13-30
//inline
//void swap(HasPtr& lhs, HasPtr& rhs)
//{
//	using std::swap;
//	cout << "swap start" << endl;
//	swap(lhs.str, rhs.str);
//	swap(lhs.value, rhs.value);
//	cout << "swap end" << endl;
//}

//13-31
//当元素数目过少时sort使用的是插入排序算法，未使用swap。
//增加元素数目至一定程度，sort会使用快速排序算法，此时使用自定义版本的swap。

//13-32
//默认版本简单交换两个对象的非静态成员，对HasPtr而言，就是交换string指针ps、引用计数指针use和整数i。
//可以看出，这种语义是符合期望的。默认swap版本已经能够正确处理指针HasPtr的交换，专用的版本并不会带来更多收益。

//13-33
//参数如果不是引用类型，我们的save和remove操作都将仅仅操作在目标Folder的拷贝上，目标Folder并不会改变。
//而且，我们不能将参数设置为const，因为我们要改变对象的状态

//13-34,13-36
//class Message;
//void swap(Message &lhs, Message &rhs);
//
//class Folder {
//	friend void swap(Message &lhs, Message &rhs);
//	friend class Message;
//public:
//	Folder() = default;
//	Folder(const Folder&);
//	~Folder();
//	Folder& operator=(const Folder&);
//
//	void print(ostream&);
//
//private:
//	set<Message*> msgs;
//	//工具函数
//	void addMsg(Message *m) { msgs.insert(m); }
//	void remMsg(Message *m) { msgs.erase(m); }
//	void add_to_Messages(const Folder&);
//	void remove_from_Messages();
//};
//
//void Folder::add_to_Messages(const Folder &f) {
//	for (auto m : f.msgs)
//		m->addFldr(this);
//}
//
//void Folder::remove_from_Messages() {
//	for (auto m : msgs)
//		m->remFldr(this);
//}
//
//Folder::Folder(const Folder &f) : msgs(f.msgs) {
//	add_to_Messages(f);
//}
//
//Folder::~Folder() {
//	remove_from_Messages();
//}
//
//Folder& Folder::operator=(const Folder &f) {
//	remove_from_Messages();
//	msgs = f.msgs;
//	add_to_Messages(f);
//
//	return *this;
//}
//
//void Folder::print(ostream &os) {
//	for (auto m : msgs)
//		os << m->contents << endl;
//	os << endl;
//}
//
//class Message {
//	friend class Folder;
//	friend void swap(Message&, Message&);
//public:
//	//默认构造函数
//	Message(const string &s = "") : contents(s) { }
//	//拷贝构造函数
//	Message(const Message&);
//	//析构函数
//	~Message();
//	//拷贝赋值运算符
//	Message& operator=(const Message&);
//
//	//成员函数
//	void save(Folder&);
//	void remove(Folder&);
//
//private:
//	//数据成员
//	string contents;
//	set<Folder*> folders;
//	//工具函数
//	void add_to_folders(const Message&);
//	void remove_from_folders();
//	void addFldr(Folder *f) { folders.insert(f); }
//	void remFldr(Folder *f) { folders.erase(f); }
//};
//
//
//void Message::add_to_folders(const Message &m) {
//	for (auto f : m.folders)
//		f->addMsg(this);
//}
//
//void Message::remove_from_folders() {
//	for (auto f : folders)
//		f->remMsg(this);
//}
//
//
//Message::Message(const Message &m) :
//	contents(m.contents), folders(m.folders) {
//	add_to_folders(m);
//}
//
//
//Message::~Message() {
//	remove_from_folders();
//}
//
//
//Message& Message::operator=(const Message &m) {
//	remove_from_folders();
//	contents = m.contents;
//	folders = m.folders;
//	add_to_folders(m);
//
//	return *this;
//}
//
//void Message::save(Folder &f) {
//	folders.insert(&f);
//	f.addMsg(this);
//}
//
//void Message::remove(Folder &f) {
//	folders.erase(&f);
//	f.remMsg(this);
//}
//
//void swap(Message &lhs, Message &rhs) {
//	using std::swap;
//
//	lhs.remove_from_folders();
//	rhs.remove_from_folders();
//
//	swap(lhs.contents, rhs.contents);
//	swap(lhs.folders, rhs.folders);
//
//	for (auto f : lhs.folders)
//		f->addMsg(&lhs);
//	for (auto f : rhs.folders)
//		f->addMsg(&rhs);
//}

//13-35
//对于合成的拷贝构造函数；
//当我们用类对象m拷贝初始化一个 Message对象时，对应的Folder对象中的set并不包含这个副本的指针。
//相当于这个副本的信息并未添加到对应的Folder对象中。
//对于合成的析构函数：
//当我们的类对象m销毁时，原来保存有m指针的Folder对象中的set依然存有m的指针。相当于信息并未删除。
//对于合成的拷贝赋值运算符：
//相当于原信息不删除，新信息不添加

//13-38
//因为非引用方式的拷贝，会导致实参的副本也添加到相应的Folder类对象之中。
//（之后销毁还会删除）。但这是一种浪费开销的方式。我们需要创建、销毁形参对象并两次添加、删除，导致效率低下。

//13-39,13-40
//class StrVec
//{
//public:
//	StrVec() :elemnts(nullptr), first_free(nullptr), cap(nullptr) { }
//
//	StrVec(initializer_list<string>);
//
//	StrVec(const StrVec&);
//
//	StrVec& operator=(const StrVec&);
//
//	~StrVec();
//
//	void push_back(const string&);
//
//	size_t size() const { return first_free - elemnts; }
//
//	size_t capacity() const { return cap - elemnts; }
//
//	string* begin() const { return elemnts; }
//
//	string* end() const { return first_free; }
//
//	void reserve(size_t);
//	void resize(size_t count, const std::string&);
//	void resize(size_t new_cap);
//
//private:
//	static allocator<string> alloc;
//
//	void chk_n_alloc()
//	{
//		if (size() == capacity()) reallocate();
//	}
//
//	std::pair<string*, string*> alloc_n_copy(const string*, const string*);
//
//	void free();
//
//	void reallocate();
//
//	void alloc_n_move(size_t);
//
//	void range_initialize(const std::string*, const std::string*);
//
//	string* elemnts;
//	string* first_free;
//	string* cap;
//};
//
//StrVec::StrVec(const StrVec&s)
//{
//	auto newdata = alloc_n_copy(s.begin(), s.end());
//	elemnts = newdata.first;
//	first_free = cap = newdata.second;
//}
//
//StrVec::StrVec(initializer_list<string>list)
//{
//	range_initialize(list.begin(), list.end());
//}
//
//
//StrVec& StrVec::operator=(const StrVec&rhs)
//{
//	auto data = alloc_n_copy(rhs.begin(), rhs.end());
//	free();
//	elemnts = data.first;
//	elemnts = data.second;
//	return *this;
//}
//
//
//StrVec::~StrVec()
//{
//	free();
//}
//
//void StrVec::push_back(const string& s)
//{
//	chk_n_alloc();
//	alloc.construct(first_free++, s);
//}
//
//std::pair<string*, string*> StrVec::alloc_n_copy(const string* b, const string* e)
//{
//	auto data = alloc.allocate(e - b);
//	return{ data,uninitialized_copy(b,e,data) };
//}
//
//void StrVec::free()
//{
//	if (elemnts)
//	{
//		//for (auto p = first_free;p != elemnts;)
//		//{
//		//	alloc.destroy(--p);
//		//}
//		for_each(elemnts, first_free, [this](string& rhs) { alloc.destroy(&rhs);});
//		alloc.deallocate(elemnts, cap - elemnts);
//	}
//}
//
//void StrVec::reallocate()
//{
//	size_t newcapacity = size() ? 2 * size() : 1;
//
//	auto newdata = alloc.allocate(newcapacity);
//
//	string* dest = newdata;
//
//	string* elem = elemnts;
//
//	for (size_t i = 0;i != size();++i)
//	{
//		alloc.construct(dest++, std::move(*elem++));
//	}
//
//	free();
//
//	elemnts = newdata;
//	first_free = dest;
//	cap = elemnts + newcapacity;
//}
//
//void StrVec::alloc_n_move(size_t new_cap)
//{
//	auto newdata = alloc.allocate(new_cap);
//
//	string* dest = newdata;
//
//	string* elem = elemnts;
//
//	for (size_t i = 0;i != size();++i)
//	{
//		alloc.construct(dest++, std::move(*elem++));
//	}
//
//	free();
//
//	elemnts = newdata;
//	first_free = dest;
//	cap = elemnts + new_cap;
//
//}
//
//
//void StrVec::reserve(size_t n)
//{
//	if (n <= capacity())
//	{
//		return;
//	}
//
//	alloc_n_move(n);
//}
//
//void StrVec::range_initialize(const std::string* b, const std::string* e)
//{
//	auto newdata = alloc_n_copy(b, e);
//	elemnts = newdata.first;
//	first_free = cap = newdata.second;
//}
//
//void StrVec::resize(size_t count, const std::string& s)
//{
//	if (count > size())
//	{
//		if (count > capacity())
//		{
//			reallocate();
//		}
//		for (size_t i = 0; i != count; ++i)
//		{
//			alloc.construct(first_free++, s);
//		}
//
//	}
//	else if (count < size())
//	{
//		while (first_free != elemnts + count)
//		{
//			alloc.destroy(--first_free);
//		}
//	}
//}
//
//void StrVec::resize(size_t new_cap)
//{
//	resize(new_cap, string());
//}

//13-41
//因为first_free指向最后一个实际元素后的位置；firt_free指向的内存未被构造

//13-43
//for_each,只需给定范围和执行的操作即可。而for版本的还需要控制指针的增减，这里容易出错。

//13-44
//class String
//{
//public:
//	String() :elments(nullptr), end(nullptr) { };
//	String(const char* str);
//	String(const String&);
//	String& operator=(const String&);
//	~String();
//
//	const char* c_str() const { return elments; }
//	size_t size() const { return end - elments; }
//	size_t length() const { return end - elments - 1; }
//
//private:
//	pair<char*, char*> alloc_n_copy(const char*, const char*);
//	void range_initializer(const char*, const char*);
//	void free();
//
//private:
//	char* elments;
//	char* end;
//	allocator<char> alloc;
//};
//
//String::String(const char* str)
//{
//	char* tmp = const_cast<char*> (str);
//	while (*tmp)
//		++tmp;
//	range_initializer(str, ++tmp);
//}
//
//String::String(const String& rhs)
//{
//	auto ptr = alloc_n_copy(rhs.elments, rhs.end);
//	elments = ptr.first;
//	elments = ptr.second;
//	cout << "copy constructor" << endl;
//}
//
//String& String::operator=(const String& rhs)
//{
//	auto ptr = alloc_n_copy(rhs.elments, rhs.end);
//	free();
//	elments = ptr.first;
//	end = ptr.second;
//
//	cout << "copy assignment" <<endl;
//	return *this;
//}
//
//String::~String()
//{
//	free();
//}
//
//
//void String::free()
//{
//	if (elments)
//	{
//		std::for_each(elments, end, [this](char& a) {alloc.destroy(&a);});
//		alloc.deallocate(elments, end - elments);
//	}
//}
//
//
//void String::range_initializer(const char* b, const char* e)
//{
//	auto ptr = alloc_n_copy(b, e);
//	elments = ptr.first;
//	end = ptr.second;
//}
//
//pair<char*, char*> String::alloc_n_copy(const char* b, const char* e)
//{
//	auto ptrb = alloc.allocate(e - b);
//	return{ ptrb,uninitialized_copy(b,e,ptrb) };
//}

//13-45
//左：可以绑定到左值的引用都是返回左值
//返回左值引用的函数，连同赋值、下标、解引用和前置递增/递减运算符
//右：所引用的对象会被销毁
//返回非引用类型的函数，连同算术、关系、位以及后置递增/递减运算符，都是生成右值

//13-46
//vector<int> vi(100);
//int&& r1 = f();
//int& r2 = vi[0];
//int& r3 = r1;
//int&& r4 = vi[0] * f();

//13-47
//class String {
//public:
//	String() : String("") {}
//	String(const char*);
//	String(const String&);
//	String& operator=(const String&);
//	~String();
//
//	const char* c_str() const { return elements; }
//	size_t size() const { return end - elements; }
//	size_t length() const { return end - elements - 1; }
//
//private:
//	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
//	void range_initializer(const char*, const char*);
//	void free();
//
//private:
//	char* elements;
//	char* end;
//	std::allocator<char> alloc;
//};
//
//std::pair<char*, char*> String::alloc_n_copy(const char* b, const char* e)
//{
//	auto str = alloc.allocate(e - b);
//	return{ str, std::uninitialized_copy(b, e, str) };
//}
//
//void String::range_initializer(const char* first, const char* last)
//{
//	auto newstr = alloc_n_copy(first, last);
//	elements = newstr.first;
//	end = newstr.second;
//}
//
//String::String(const char* s)
//{
//	char* sl = const_cast<char*>(s);
//	while (*sl) ++sl;
//	range_initializer(s, ++sl);
//}
//
//String::String(const String& rhs)
//{
//	range_initializer(rhs.elements, rhs.end);
//	std::cout << "copy constructor" << std::endl;
//}
//
//void String::free()
//{
//	if (elements) {
//		std::for_each(elements, end, [this](char& c) { alloc.destroy(&c); });
//		alloc.deallocate(elements, end - elements);
//	}
//}
//
//String::~String()
//{
//	free();
//}
//
//String& String::operator=(const String& rhs)
//{
//	auto newstr = alloc_n_copy(rhs.elements, rhs.end);
//	free();
//	elements = newstr.first;
//	end = newstr.second;
//	std::cout << "copy-assignment" << std::endl;
//	return *this;
//}

//Test code
//char text[] = "world";
//
//String s0;
//String s1("hello");
//String s2(s0);
//String s3 = s1;
//String s4(text);
//s2 = s1;
//
//foo(s1);
//bar(s1);
//foo("temporary");
//bar("temporary");
//String s5 = baz();
//
//std::vector<String> svec;
//svec.reserve(8);
//svec.push_back(s0);
//svec.push_back(s1);
//svec.push_back(s2);
//svec.push_back(s3);
//svec.push_back(s4);
//svec.push_back(s5);
//svec.push_back(baz());
//svec.push_back("good job");
//
//for (const auto& s : svec) {
//	std::cout << s.c_str() << std::endl;
//}

//13-48
//10

//13-49
//StrVec::StrVec(StrVec&& s)noexcept
//	: elemnts(s.elemnts), first_free(s.first_free), cap(s.cap)
//{
//	s.elemnts = s.first_free = s.cap = nullptr;
//}
//
//StrVec& StrVec::operator=(StrVec&&s)noexcept
//{
//	if (this != &s)
//	{
//		free();
//		elemnts = s.elemnts;
//		first_free = s.first_free;
//		cap = s.cap;
//
//		s.elemnts = s.first_free = s.cap = nullptr;
//	}
//	return *this;
//}
//String::String(String&& r) noexcept
//	:elements(r.elements), end(r.end)
//{
//	r.elements = r.end = nullptr;
//}
//
//
//String&String::operator=(String&& r) noexcept
//{
//	if (this != &r)
//	{
//		free();
//		elements = r.elements;
//		end = r.end;
//		r.elements = r.end = nullptr;
//	}
//
//	return *this;
//}


//13-50
//生成临时对象

//13-51
//unique_ptr<int> clone(int p)
//{
//	return unique_ptr<int>(new int(p));
//}
//返回的结果是一个右值，使用移动赋值操作

//13-52
//rhs是一个非引用参数，所以需要拷贝初始化，依赖于实参类型，拷贝初始化要么使用拷贝构造函数要么使用移动构造函数
//hp的第一个赋值中，右侧为左值，需要进行拷贝初始化，分配一个新的string，并拷贝hp2所指向的string
//hp的第二个赋值中，直接调用std::move()将一个右值绑定到hp2上，
//虽然移动构造函数和拷贝构造函数皆可行，但是移动构造函数是精确匹配且不会分配任何内存

//13-53
// When you use HasPtr& operator=(HasPtr rhs) and you write something like hp = std::move(hp2);, 
//ps member is copied twice (the pointer itself not the object to which it points):
//Once from hp2 to rhs as a result of calling move constructor,
//and once from rhs to *this as a result of calling swap. But when you use HasPtr& operator=(HasPtr&& rhs), 
//ps is copied just once from rhs to *this
//HasPtr& HasPtr::operator=(const HasPtr& rhs)
//{
//	++*rhs.use;
//	if (--*use == 0)
//	{
//		delete str;
//		delete use;
//	}
//	str = rhs.str;
//	value = rhs.value;
//	use = rhs.use;
//	return *this;
//}
//
//HasPtr& HasPtr::operator=(HasPtr&& rhs) noexcept
//{
//	if (this != &rhs)
//	{
//		str = rhs.str;
//		value = rhs.value;
//		use = rhs.use;
//		rhs.str = nullptr;
//		rhs.value = NULL;
//		rhs.use = nullptr;
//	}
//	return *this;
//}

//13-55
//void StrVec::push_back(string&& s)
//{
//	chk_n_alloc();
//	alloc.construct(first_free++, std::move(s));
//}

//13-56
//调用Foo::sorted() const &版本导致递归调用,造成堆栈溢出
//13-57
//调用Foo Foo::sorted() && 
//class Foo
//{
//public:
//	Foo sorted() && ;
//	Foo sorted() const &;
//
//
//private:
//	vector<int> data;
//};
//
//Foo Foo::sorted() && 
//{
//	sort(data.begin(), data.end());
//	cout << "Foo Foo::sorted() && " << endl;
//	return *this;
//}
//
//Foo Foo::sorted() const &
//{
//	Foo ret(*this);
//	
//	cout << "Foo Foo::sorted() const & " << endl;
//	sort(data.begin(), data.end());
//	return ret.sorted();
//	//return Foo(*this).sorted();
//}

