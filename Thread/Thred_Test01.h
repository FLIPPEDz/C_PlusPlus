#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <Windows.h>
#include <future>
using std::mutex;
using std::thread;
using std::list;
using std::vector;
using namespace std;


namespace Thred_Test01
{

	//void edit_document(std::string const&file)
	//{
	//	open_document_and_display_gui(filename);
	//	while (!done_editing())
	//	{
	//		user_command cmd = get_user_input();
	//		if (cmd.type == open_new_document)
	//		{
	//			std::string const new_name = get_filename_from_user();
	//			std::thread t(edit_document, new_name); // 1
	//			t.detach(); // 2
	//		}
	//		else
	//		{
	//			process_user_input(cmd);
	//		}
	//}
		void  test01()
		{
			//example
			cout << "hello world!" << endl;

			cout << "test finished" << endl;

		}

		void test02()
		{
			//根据经验，还是主线程等待子线程执行完这种传统的方法比较好
			cout << "test thread" << endl;
			for (int i=0;i<100;++i)
			{
				cout << i << endl;
			}
			cout << "test finished" << endl;
		}

		class TA
		{
		

		public:
			int m_i;

			TA(int& i) :m_i(i)
			{
				cout << "构造函数" << endl;
			}
			TA(const TA& rhs)
			{
				cout <<"拷贝构造函数"<< endl;
			}
			~TA()
			{
				cout << "析构函数" << endl;
			}

			void operator()()                    //仿函数？
			{
				cout << "operator()开始执行" << endl;


				cout << "operator()结束执行" << endl;
			}

		};

		//传递临时对象作为线程参数
		//void myprintf(const int& i, char* mybuf)
		//void myprintf(const int i,const string& mybuf)
		//{
		//	cout << i << endl;
		//	cout << mybuf.c_str() << endl;

		//	return;
		//}

		class A
		{
		public:
			A(int a) :m_i(a) {
				cout << "A::ctor" << "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
				<< endl; }
			A(const A& rhs) :m_i(rhs.m_i) { cout <<"A::copyctor" 
				<< "\tthis=" << this
				<< "\tthreadid=" << this_thread::get_id() 
				<< endl; }
			~A() { cout << "A::dector"<<"\tthis=" << this
				<< "\tthreadid=" << this_thread::get_id()
				<< endl; }

		public:
			int m_i;
		};

		void myprintf(const int i,const A& mybuf)
		{
			
			cout <<& mybuf << endl;

			return;
		}

		//临时构造参数能够在主线程结束之前构建出来，确保detach子线程是安全的
		//隐式类型转换是不安全的
		void test03()
		{
			int mvar = 1;
			int myvar = 12;

			thread obj(myprintf, mvar, A(myvar));  /*在创建线程的同时构造
												   临时对象的方法传递参数
													 是可行的*/
			obj.detach();

		}

		void myprintf02(const A& mybuf)
		{
			cout << "myprintf02 Addr=" << &mybuf
				<< "\tthreadid=" << this_thread::get_id()
				<< endl;
		}

		void test04()
		{
			//临时对象作为线程参数，测试
			//线程id;
			//临时对象构造捕获
			cout << "main thread id" << this_thread::get_id() << endl;
			
			int mvar = 1;
			
			//隐式转换在子线程中构造A类对象不安全，不可预料
			//thread obj(myprintf02, mvar);

			thread obj(myprintf02, Thred_Test01::A(mvar));

			obj.join();
		}

		class B
		{
		public:
			B(int a) :m_i(a) {
				cout << "B::ctor" << "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}
			B(const B& rhs) :m_i(rhs.m_i) {
				cout << "B::copyctor"
					<< "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}
			~B() {
				cout << "B::dector" << "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}

		public:
		mutable int m_i;
		};

		void myprintf03(const B& mybuf)
		{
			mybuf.m_i = 33;  //修改该值不会影响到main
			cout << "myprintf02 Addr=" << &mybuf
				<< "\tthreadid=" << this_thread::get_id()
				<< endl;
		}


		void myprintf04(unique_ptr<int> pzn)
		{
			
		}

		void test05()
		{
			//智能指针作为线程参数
			//std::ref函数
		
			//B tmp(10);
			//thread myobj(myprintf03,ref(tmp));
			//myobj.join();

			unique_ptr<int> myp(new int(100));

			

			thread myobj(myprintf04, move(myp));
			myobj.join();

		}


		class C
		{
		public:
			C(int a) :m_i(a) {
				cout << "C::ctor" << "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}
			C(const C& rhs) :m_i(rhs.m_i) {
				cout << "C::copyctor"
					<< "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}
			~C() {
				cout << "C::dector" << "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}

			void thread_work(int num)
			{
				cout << "子线程thread_work执行" 
					<< "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}

			void operator()(int num)
			{
				cout << "子线程operator()执行"
					<< "\tthis=" << this
					<< "\tthreadid=" << this_thread::get_id()
					<< endl;
			}
		public:
			int m_i;
		};

		void test06()
		{
			//用成员函数指针做线程函数
			
			C tmp(12);

/*			thread myobj(&C::thread_work,tmp,15); *///& == std::ref 不用调用拷贝构造函数，不能使用detach
			
			thread myobj(tmp,15);
			myobj.join();

		}

		//创建和等待多个线程
		//  顺序是乱的，和时间片调度有关，如基于优先级的时间片调度算法，抢占式算法
		//  推荐jion程序更稳定
		//  放入到Container中进行管理
		
		//数据共享问题分析
		//	


		//	只读的数据
		//		是安全稳定的

		//	有读有写
		//		两个线程写，八个线程读，如果无特别处理程序肯定奔溃

		//	其他案例
		//		订票

		//共享数据的保护案例代码
		//	

		void mymain(int num)
		{
			cout << "mymain开始执行,id=" << num << endl;
			//...干各种事情
			cout << "mymain finished"<<endl;
			return;
		}

		void test07()
		{
			vector<thread> mythreads;
			for (int i=0;i<10;++i)
			{
				mythreads.push_back(thread(mymain, i)); //创建并开始执行

			}
			for (auto itr=mythreads.begin();itr!=mythreads.end();++itr)
			{
				itr->join();
			}

			cout << "main finished!" << endl;
			return;
		}

		vector<int>g_v{ 1,2,3 };

		void mymain01(int num)
		{
			cout << "id=" << this_thread::get_id() << endl;
			//...干各种事情
			cout << "g_v:"<<g_v[0]<<","<<g_v[1]
				<< "," <<g_v[2] 
				<< "," 
				<< endl;
			return;
		}

		void test08()
		{
			vector<thread> mythreads;
			for (int i = 0;i < 10;++i)
			{
				mythreads.push_back(thread(mymain01, i)); //创建并开始执行

			}
			for (auto itr = mythreads.begin();itr != mythreads.end();++itr)
			{
				itr->join();
			}

			cout << "main finished!" << endl;
		}

		class D
		{
		public:
			void inMsgRecvQueue()
			{
				for (int i=0;i<10000;++i)
				{
					
					cout << "inMsgRecvQueue,ing,插入一个元素"<<i << endl;
					lock(m_mutex_gold, m_mutex_silver);
					//m_mutex_gold.lock();
					//m_mutex_silver.lock();
					msg_queue.push_back(i);
					//m_mutex_silver.unlock();
					//m_mutex_gold.unlock();
					m_mutex_gold.unlock();
					m_mutex_silver.unlock();
				}
			}

			void handleMsgQueue()
			{
				for (int i = 0;i < 10000;++i)
				{
/*					lock_guard<mutex> m_guard(m_mutex); *///lock_guard使用方法
					//m_mutex.lock();
					
					//m_mutex_silver.lock();
					//m_mutex_gold.lock();

					lock(m_mutex_gold, m_mutex_silver);

					lock_guard<mutex> m_guard(m_mutex_gold, adopt_lock);
					lock_guard<mutex> m_guard1(m_mutex_silver, adopt_lock);
					if (!msg_queue.empty())
					{
						int command = msg_queue.front();
						msg_queue.pop_front();
						//处理
						//........	
						//m_mutex.unlock();
						//m_mutex_gold.unlock();
						//m_mutex_silver.unlock();
					}
					else
					{
						cout << "handleMsgQueue()执行，目前MQ为空"<<i<< endl;
						//m_mutex.unlock();
						//m_mutex_gold.unlock();
						//m_mutex_silver.unlock();
					}
				}
				cout << "end" << endl;
			}


		private:
			list<int> msg_queue;
			mutex m_mutex_gold;
			mutex m_mutex_silver;
		};


		void test09()
		{
			D myobjlist;

			thread myobjthread_get(&D::inMsgRecvQueue, &myobjlist);
			thread myobjthread_handle(&D::handleMsgQueue, &myobjlist);


			myobjthread_get.join();
			myobjthread_handle.join();

			cout << "main finished!" << endl;
		}

		//mutex概念

		//互斥量的用法

			//lock(),unlock()     //if条件时 lock和unlock 的使用
			//std::lock_guard template  //可以取代lock(),unlock()
			//lock_guard 调用时构造函数执行mutex::lock,函数结束作用域时在析构函数中执行mutex::unlock
			//通过加{}方法改变作用域
		//死锁
			//解决方案：锁的顺序
			//std::lock()一次锁住两个或以上互斥量（解决死锁风险问题）要么两个一起
			//锁住要么都没锁住，处理多个互斥量
			//std::lock()加lock_guard配合使用
			//lock_guard<mutex> m_guard(m_mutex_gold, adopt_lock)
			//adopt_lock结构体make sure both already-locked
			//mutexes are unlocked at the end of scope
}

//unique_lock

namespace Thread_Test02
{
	class u_lock_te
	{
	public:
		unique_lock<mutex> rtn_unique_lock()
		{
			unique_lock<mutex> tmp(m_mutex_gold);

			return tmp;
		}

		void inMsgRecvQueue()
		{
			for (int i = 0;i < 10000;++i)
			{

				cout << "inMsgRecvQueue,ing,插入一个元素\t" << i << endl;
				//unique_lock<mutex> m_uniq(m_mutex_gold, std::try_to_lock);  //尝试获得互斥的所有权而不阻塞

				//if (m_uniq.owns_lock())
				//{
				//unique_lock<mutex> m_uniq(m_mutex_gold, std::defer_lock);
				//m_uniq.lock();      //不用自己解锁

				//unique_lock<mutex> m_uniq(m_mutex_gold, std::defer_lock);
				//unique_lock<mutex> m_uniq(m_mutex_gold);
				//mutex *ptr = m_uniq.release(); //接管有责任负责解锁
				
				unique_lock<mutex> m_uniq(m_mutex_gold);
				unique_lock<mutex> m_uniq_t(move(m_uniq));//m_uniq指向空，m_uniq_t指向m_mutex_gold

				//if (m_uniq.try_lock()==true)
				//{
					msg_queue.push_back(i);

					//ptr->unlock();

				
				//}
				//else
				//{
				//	cout << "inMsgRecvQueue,ing,但没有拿到锁\t" << endl;
				//}
					
				//}
				//else
				//{
				//	cout << "inMsgRecvQueue,ing,但没有拿到锁\t" << endl;
				//}
				

			}
		}

		void handleMsgQueue()
		{
			for (int i = 0;i < 10000;++i)
			{

				//unique_lock<mutex> m_uniq(m_mutex_gold);

				//chrono::milliseconds dura(200);
				//this_thread::sleep_for(dura);
				unique_lock<mutex> m_uniq(m_mutex_gold, std::defer_lock); //默认不上锁
				m_uniq.lock();
				if (!msg_queue.empty())
				{
					int command = msg_queue.front();
					msg_queue.pop_front();
				}
				else
				{
					cout << "handleMsgQueue()执行，目前MQ为空\t" << i << endl;
				}
			}
			cout << "end" << endl;
		}


	private:
		list<int> msg_queue;
		mutex m_mutex_gold;
		mutex m_mutex_silver;
	};


	void u_test_main()
	{
		u_lock_te myobjlist;

		thread myobjthread_get(&u_lock_te::inMsgRecvQueue, &myobjlist);
		thread myobjthread_handle(&u_lock_te::handleMsgQueue, &myobjlist);

		myobjthread_get.join();
		myobjthread_handle.join();

		cout << "main finished!" << endl;
	}

	//unique_lock是一个类模板，工作中，一般lock_guard（推荐使用）
	//unique_lock比lock_guard效率低一些，内存占用多一些
	//unique_lock也可以带参数std::adopt_lock和lock_guard中意思相同
	//灵活性
	//std::try_to_lock，没有锁定成功，立即返回，不会阻塞
	//std::defer_lock 初始化一个没有加锁的mutex
	//try_lock()尝试给互斥量加锁，不阻塞
	//release(),返回它管理的mutex对象指针，并释放所有权;unique_lock和text不在关联
	//如果原来mutex对象处于加锁状态，有义务接管责任并解锁
	//粒度：锁住的code,合理选择粒度

	//unique_lock所有权的传递 mutex
	//unique_lock mutex所有权可以转移，但是不能复制
	//std::move , returng该类型

}


namespace Thread_Test03
{
	//设计模式概述
	//////////////////////////////////////////////////////////////////////////
	/*用“设计模式”理念写出来的代码晦涩的：《head first》*/
	//////////////////////////////////////////////////////////////////////////

	//单例设计模式
	//////////////////////////////////////////////////////////////////////////
	/*Singleton*/
	//////////////////////////////////////////////////////////////////////////

	//单例设计模式共享数据问题分析、解决
	//////////////////////////////////////////////////////////////////////////
	/*在主线程中将单例初始化，以后只用进行只读操作*/
	/*面临的问题：需要在自己的多个线程中创建单例
	  可能面临Get_Instance()这种成员函数要互斥*/
	//////////////////////////////////////////////////////////////////////////

	//std::call_once()
	//////////////////////////////////////////////////////////////////////////
	/*该函数第二个参数是一个函数名a()
	  call_once功能是能够保证a()只被调用一次*/
	/*需要与std::once_flag结合使用，once_flag
	  是一个结构体*/
	//////////////////////////////////////////////////////////////////////////

	mutex m_silver;
	std::once_flag m_flag;

	class Singleton
	{
		static void Create_Instance()
		{
			//chrono::milliseconds dura(2000);
			//this_thread::sleep_for(dura);
			cout << "Create_Instance() ing!" << endl;

			m_S_ton = new Singleton();
			static Singleton_Recharge cl;

		}
	public:
		static Singleton* Get_Instance()
		{
			//提高效率
			if (m_S_ton == NULL)  //双重锁定
			{
				unique_lock<mutex> m_unique(m_silver);
				if (m_S_ton == NULL)
				{
					m_S_ton = new Singleton();
					static Singleton_Recharge cl;
				}
			}

			//一个线程会等待另外一个线程执行完Create_Instance
			//std::call_once(m_flag, Create_Instance); 

			return m_S_ton;
		}

		class Singleton_Recharge
		{
		public:

			~Singleton_Recharge()
			{
				if (Singleton::m_S_ton)
				{
					delete Singleton::m_S_ton;
					Singleton::m_S_ton = NULL;
				}
			}
		};

		void func()
		{
			cout << "Singleton test" << endl;
		}


	private:
		Singleton(){}

	private:
		static Singleton* m_S_ton;

	};

	Singleton* Singleton::m_S_ton = NULL;


	void mythread()
	{
		cout << "my thread starting" << endl;

		Singleton* ptr = Singleton::Get_Instance();

		ptr->func();

		cout << "my thread finished" << endl;

		return;
	}

	void main_test()
	{
		thread myobj(mythread);
		thread myobj1(mythread);

		myobj.join();
		myobj1.join();

		cout << "main finished" << endl;
	}

}


namespace Thread_Test04
{
	//std::condition_variable\wait()\notify_one()(通知一个线程)
	//////////////////////////////////////////////////////////////////////////
	/*std::condition_variable 是一个条件类
	  等待条件达成，与mutex配合工作*/  //！！！用不好就别用
	//////////////////////////////////////////////////////////////////////////
	//notify_all()
	/**/
	//////////////////////////////////////////////////////////////////////////
	/*能写出来！=稳定！=能写稳定*/
	//////////////////////////////////////////////////////////////////////////

	class A
	{
	public:

		void inMsgRecvQueue()
		{
			for (int i = 0;i < 10000;++i)
			{

				cout << "inMsgRecvQueue ing 插入一个元素\t" << i << endl;
				unique_lock<mutex> tmp(m_mutex_gold);
				msg_queue.push_back(i);
				m_cond.notify_all();
				//m_cond.notify_one();  //唤醒wait()线程

				//如果其他线程没有卡在wait处等待，此时notify_one()无效果
			}

			cout << "inMsgRecvQueue() end" << endl;
		}

		void handleMsgQueue()
		{

			int command = 0;
			while (true)
			{
				unique_lock<mutex> m_uniq(m_mutex_gold);
				
				//wait()用来等一个东西，返回值为true调用mutex继续往下执行
				//如果第二个参数lambda返回false,wait()将解锁互斥量，并阻塞到本行
				//阻塞到其它线程调用notiyf_one()成员函数位为止
				//没有第二个参数，效果阻塞到其它线程调用notiyf_one()成员函数位为止
				m_cond.wait(m_uniq, [this] {
				
					if (!msg_queue.empty())
					{
						return true;
					}

					return false;
				});

				//流程能走下来，mutex一定lock()
				int command = msg_queue.front();
				msg_queue.pop_front();
				cout << "handleMsgQueue()取出数据\t" << command
					<<"\t线程id="<<this_thread::get_id()
					<< endl;
				m_uniq.unlock();   //uniq_lock灵活性，可以随时unlcok

				

			}

			//for (int i = 0;i < 10000;++i)
			//{
			//	if (!msg_queue.empty())
			//	{
			//		int command = msg_queue.front();
			//		msg_queue.pop_front();

			//		unique_lock<mutex> m_uniq(m_mutex_gold);
			//		if (!msg_queue.empty())
			//		{
			//			int command = msg_queue.front();
			//			msg_queue.pop_front();
			//		}
			//		else
			//		{
			//			cout << "handleMsgQueue()执行，目前MQ为空\t" << i << endl;
			//		}
			//	}
			//}

			//cout << "handleMsgQueue() end" << endl;
		}


	private:
		list<int> msg_queue;
		mutex m_mutex_gold;
		mutex m_mutex_silver;
		condition_variable m_cond;
	};


	void main_test()
	{
		/*条件变量作用：
			线程A：等待一个条件满足
			线程B：专门往消息队列中仍消息（数据）*/
		A myobj;

		thread Outobj(&A::handleMsgQueue, &myobj);
		thread Outobj01(&A::handleMsgQueue, &myobj);
		thread Inobj(&A::inMsgRecvQueue, &myobj);

		Outobj.join();
		Outobj01.join();
		Inobj.join();

		cout << "main finished" << endl;
	}

}

namespace Thread_Test05
{
	//////////////////////////////////////////////////////////////////////////
	//std::async,std::future(都是类模板),创建后台任务并返回值
	/*希望线程返回结果
	  std::async 启动异步任务，返回std::future(含有线程入口函数所返回的结果)
	  std::future::get获取结果
	  std::future提供一种访问异步操作结果的机制，返回值在将来能够拿到
	  std::launch::deferred,表示线程的入口函数调用被延迟到std::的wait()或者
	  get()函数调用时才执行
	  wait()或get()没有被调用，线程不会创建
	  std::launch::deferred延迟调用，并在主线程中调用线程入口函数
	  
	  std::launch::async,在调用async函数时就创建线程
	  async函数默认标记*/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//std::packaged_task
	/**/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//std::promise
	/**/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//总结
	/**/
	//////////////////////////////////////////////////////////////////////////

	int mythread()
	{
		cout << "mythread() strating\tid=" << this_thread::get_id() << endl;
		
		//sleep 5s
		chrono::milliseconds dura(2000);  
		this_thread::sleep_for(dura);

		cout << "mythread() ended\tid=" << this_thread::get_id() << endl;

		return 5;
	}

	class A
	{
	public:
		int mythread(int tmp)
		{
			cout << tmp << endl;
			cout << "mythread() strating\tid=" << this_thread::get_id() << endl;

			//sleep 5s
			chrono::milliseconds dura(2000);
			this_thread::sleep_for(dura);

			cout << "mythread() ended\tid=" << this_thread::get_id() << endl;

			return 5;
		}
	};

	void main_test()
	{
		cout << "main\tid=" << this_thread::get_id() << endl;
		A a;
		int tmp = 12;
		
		//std::future<int> result = std::async(mythread);
		std::future<int> result = std::async(std::launch::async,&A::mythread,&a,tmp);//第二个参数对象引用
		cout << "continue....!" << endl;
		
		int def;
		def = 0;

		cout << result.get() << endl;  //get()只能调用一次

		cout << "main finished\tid="<<this_thread::get_id()<< endl;
	}
}

namespace Thread_Test06
{
	//////////////////////////////////////////////////////////////////////////
	//Windows临界区
	/**/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//多次进入临界区
	/*同一个线程，相同的临界区变量代表的临界区进入EnterCriticalSection()
	  可以被多次调用，但要释放干净；c++11标准不允许多次lock*/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//自动析构技术
	/*std::lock_guard<mutex> m_guard*/
	//////////////////////////////////////////////////////////////////////////
	//recursive_mutex递归的独占互斥量
	/*std::mutex独占式互斥量，自己lock别人没办法使用
	  recursive_mutex递归的独占互斥量，同一线程同一个
	  互斥量可以多次lock(考虑代码是否有优化空间，递归次数有限制)*/
	//////////////////////////////////////////////////////////////////////////
	//带超时的互斥量std::timed_mutex和std::recursive_timed_mutex
	/*std::timed_mutex，带超时功能的独占互斥量
	  std::recursive_timed_mutex，带超时功能的递归独占互斥量
	  try_lock_for(),参数一段时间
	  try_lock_unit(),参数是未来的时间点*/
	//////////////////////////////////////////////////////////////////////////

//#define  _WINOWSJQ_  
							//RIAA类（Resource Acquisition is initalization
							//容器，智能指针等
	class WinSec_Guard     //自动释放临界区，防止忘记LeaveCriticalSection()造成死锁类似C++lock_guard
	{
	public:
		WinSec_Guard(CRITICAL_SECTION*  rhs):m_sec(rhs)
		{
			EnterCriticalSection(m_sec);
		}

		~WinSec_Guard()
		{
			LeaveCriticalSection(m_sec);
		}

	private:
		CRITICAL_SECTION* m_sec;
	};


	class A
	{
	public:
		void inMsgRecvQueue()
		{
			for (int i = 0;i < 10000;++i)
			{

				cout << "inMsgRecvQueue ing 插入一个元素\t" << i << endl;
#ifdef _WINOWSJQ_

				WinSec_Guard win_guard(&m_winsec);
				WinSec_Guard win_guard1(&m_winsec);
				//EnterCriticalSection(&m_winsec);
				//EnterCriticalSection(&m_winsec);  //重复进入临界区
				msg_queue.push_back(i);
				//LeaveCriticalSection(&m_winsec);
				//LeaveCriticalSection(&m_winsec);
#else
				//lock_guard<std::recursive_mutex> m_guard(m_r_mutex);

				//testfunc1();

				//chrono::milliseconds timeout(100);
				//if (m_t_mutex.try_lock_for(timeout)) //等待一百毫秒尝试获取锁
				//{
				//	msg_queue.push_back(i);

				//	m_t_mutex.unlock();
				//}
				//else
				//{
				//	std::chrono::milliseconds sleep(100);
				//	this_thread::sleep_for(sleep);
				//}

				chrono::milliseconds timeout(100);
				if (m_t_mutex.try_lock_until(chrono::steady_clock::now()+timeout)) //当前时间加100毫秒
				{
					msg_queue.push_back(i);

					m_t_mutex.unlock();
				}
				else
				{
					std::chrono::milliseconds sleep(100);
					this_thread::sleep_for(sleep);
				}

				//m_mutex_gold.lock();
				//m_mutex_gold.lock();          //不可以重复进入临界区	
				//m_mutex_gold.unlock();
				//m_mutex_gold.unlock();

#endif // _WINOWSJQ_


			
			}

			cout << "inMsgRecvQueue() end" << endl;
		}

		void handleMsgQueue()
		{

			for (int i = 0;i < 10000;++i)
			{
#ifdef _WINOWSJQ_
				EnterCriticalSection(&m_winsec);
				if (!msg_queue.empty())
				{
					int command = msg_queue.front();
					msg_queue.pop_front();
					LeaveCriticalSection(&m_winsec);
				}
				else
				{
					cout << "handleMsgQueue()执行，目前MQ为空\t" << i << endl;
					LeaveCriticalSection(&m_winsec);
				}

#else
				//m_mutex_gold.lock();
				//m_r_mutex.lock();

				m_t_mutex.lock();
				if (!msg_queue.empty())
				{
					int command = msg_queue.front();
					msg_queue.pop_front();
					m_t_mutex.unlock();
				}
				else
				{
					cout << "handleMsgQueue()执行，目前MQ为空\t" << i << endl;
					m_t_mutex.unlock();
				}

#endif // _WINOWSJQ_	
			}

			cout << "handleMsgQueue() end" << endl;
		}

		A()
		{
#ifdef _WINOWSJQ_
			InitializeCriticalSection(&m_winsec); //用之前初始化
#endif // _WINOWSJQ_
		}

		void testfunc1()
		{
			lock_guard<std::recursive_mutex> m_guard(m_r_mutex);
			testfunc2();
		}

		void testfunc2()
		{
			lock_guard<std::recursive_mutex> m_guard(m_r_mutex);
		}

	private:
		list<int> msg_queue;
		mutex m_mutex_gold;
		std::recursive_mutex m_r_mutex;
		std::timed_mutex m_t_mutex;
#ifdef _WINOWSJQ_
		CRITICAL_SECTION m_winsec; //windos中临界区
#endif // _WINOWSJQ_


	};
	
	void main_test()
	{
		//windows临界区
		//多次进入临界区实验
		A aobj;

		thread in_obj(&A::inMsgRecvQueue, &aobj);
		thread out_obj(&A::handleMsgQueue, &aobj);
		

		in_obj.join();
		out_obj.join();


		cout << "main end" << endl;
		return;
	}
}

namespace Thread_Test07
{
	//////////////////////////////////////////////////////////////////////////
	//虚假唤醒
	/*wait中要有第二参数并且要正确判断要处理的公共数据是否存在*/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//atomic
	/*原子操作:执行时不允许CPU进行上下文切换*/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//浅谈线程池
	/*服务器程序,客户端,每来一个客户端,就创建一个新线程为该客户提供服务
	  a)网络游戏场景不符合
	  b)程序稳定性问题
	  */
	  /*线程池:把一堆线程弄到一起，统一管理。统一管理，循环利用线程的方式，就叫
	  线程池。
	  */
	  /*在程序启动时，一次性创建好一定数目的线程，更让人放心，觉得程序代码更稳定
	  */
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//线程创建数量谈
	/*线程开的数量极限问题，20000个基本极限，在创建就崩溃*/
	/*线程创建数量建议
	  采用某些技术开发程序：api接口提供商建议 创建线程数量=cpu数量，cpu*2按照标准来
	  创建线程完成业务：一个线程等于一条执行通路；充值场景100要阻塞，我们这里开110，
	  很合适
	  */
	/*创建线程过多消耗资源更多，系统执行效率下降，线程数量尽量不要超过500，能控制在
	  200个之内*/
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//c++11多线程总结
	/*windows,linux*/
	/**/
	/**/
	//////////////////////////////////////////////////////////////////////////



	class A
	{
	public:
		atomic<int> m_t;
		A()
		{ 
			m_t = 0;
			atomic<int>m_t1(m_t.load());  //load()以原子方式读出内容
			auto m_t2(m_t.load());

			//store()以原子方式写入内容
			m_t.store(12);
			m_t = 15;
		}

	public:

		void inMsgRecvQueue()
		{
			//for (int i = 0;i < 10000;++i)
			//{

			//	cout << "inMsgRecvQueue ing 插入一个元素\t" << i << endl;
			//	unique_lock<mutex> tmp(m_mutex_gold);
			//	msg_queue.push_back(i);
			//	//m_cond.notify_all();
			//	m_cond.notify_one();  //唤醒wait()线程

			//	//如果其他线程没有卡在wait处等待，此时notify_one()无效果
			//}

			for (int i=0;i<1000000;++i)
			{
				m_t += 1;     //原子操作
				//m_t = m_t + 1;
			}



			cout << "inMsgRecvQueue() end" << endl;
		}

		void handleMsgQueue()
		{

			//int command = 0;
			//while (true)
			//{
			//	unique_lock<mutex> m_uniq(m_mutex_gold);

			//	//wait()用来等一个东西，返回值为true调用mutex继续往下执行
			//	//如果第二个参数lambda返回false,wait()将解锁互斥量，并阻塞到本行
			//	//阻塞到其它线程调用notiyf_one()成员函数位为止
			//	//没有第二个参数，效果阻塞到其它线程调用notiyf_one()成员函数位为止
			//	m_cond.wait(m_uniq, [this] {

			//		if (!msg_queue.empty())
			//		{
			//			return true;
			//		}

			//		return false;
			//	});                      //第二个参数预防虚假唤醒问题

			//	//流程能走下来，mutex一定lock()
			//	int command = msg_queue.front();
			//	msg_queue.pop_front();
			//	cout << "handleMsgQueue()取出数据\t" << command
			//		<< "\t线程id=" << this_thread::get_id()
			//		<< endl;
			//	m_uniq.unlock();   //uniq_lock灵活性，可以随时unlcok
			while (true)
			{
				cout << m_t << endl;   //读m_t是原子操作，但是这一整行代码不是
			}


			//}
		}


	private:
		list<int> msg_queue;
		mutex m_mutex_gold;
		mutex m_mutex_silver;
		condition_variable m_cond;
	};


	void main_test()
	{
		A aobj;

		thread in_obj(&A::inMsgRecvQueue, &aobj);
		thread in_obj1(&A::inMsgRecvQueue, &aobj);
		thread out_obj(&A::handleMsgQueue, &aobj);


		in_obj.join();
		in_obj1.join();
		out_obj.join();


		cout << "main end" << endl;
		return;
	}
}

namespace Thread_Test08
{
	std::atomic<int> g_v = 0;
	//std::atomic<bool> g_v = false;
	mutex m_mutex;
	//////////////////////////////////////////////////////////////////////////
	//原子操作std::stomic
	/*原子操作概念引出
	  
	  原子操作:不需要互斥量加锁技术的多线程并发操作；不会被打断的
	  程序执行片段；比互斥量更胜一筹(但只能针对一个变量)

	  原子操作，不可分割的操作

	  一般用于计数和统计（累计发送出去多少个数据包，累计接收到了多少个数据包）
	  工作和商业代码，不确定的代码多次测试或者不用

	  一般原子操作符，针对++，--，-=，+=，&=，|=，^=
	*/
	//////////////////////////////////////////////////////////////////////////

	void mythread()
	{
		for (int i=0;i<1000000;++i)
		{
			//m_mutex.lock();
			g_v += 1;
			//g_v = g_v + 1;     //不是所有运算符都支持原子操作
			//m_mutex.unlock();
		}
		return;
	}

	//void mythread()
	//{
	//	chrono::milliseconds dura(1000);
	//	while (g_v==false)
	//	{
	//		cout << "thread id=" << this_thread::get_id() << endl;

	//		this_thread::sleep_for(dura);
	//	}
	//	cout << "thread id=" << this_thread::get_id()<<"\t finished"<< endl;
	//}
	void main_test()
	{
		thread my_th1(mythread);
		thread my_th2(mythread);

		//chrono::milliseconds dura(5000);
		//this_thread::sleep_for(dura);
		//g_v = true;

		my_th1.join();
		my_th2.join();


		cout << g_v << endl;

		cout << "main end!" << endl;
	}

}
