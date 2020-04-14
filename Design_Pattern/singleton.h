#pragma once

#include <thread>
#include <mutex>
#include <atomic>

class Singleton
{
public:
	static Singleton* getInstance();
	static std::atomic<Singleton*> m_instance;
	//{ 
	//	if (m_instace==nullptr)
	//	{
	//		std::lock_guard<std::mutex> m_gurad(m_t);
	//		if (m_instace == nullptr)
	//		{
	//			m_instace = new Singleton();
	//		}
	//	}
	//
	//	return m_instace;
	//}
private:
	Singleton() {}
	Singleton(const Singleton&) {}
	
	static std::mutex m_t;

};
std::atomic<Singleton*> Singleton::m_instance = nullptr;


Singleton* Singleton::getInstance() {
	Singleton* tmp = m_instance.load(std::memory_order_relaxed);
	std::_Atomic_thread_fence(std::memory_order_acquire);
	if (tmp == nullptr)
	{
		std::lock_guard<std::mutex> m_gurad(m_t);
		if (tmp == nullptr)
		{
			tmp = new Singleton;
			std::_Atomic_thread_fence(std::memory_order_release);
			m_instance.store(tmp,std::memory_order_relaxed);
		}
	}
	return tmp;
}
