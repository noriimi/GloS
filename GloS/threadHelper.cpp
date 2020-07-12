#include "threadHelper.hpp"
#include <iostream>
#include <chrono>
std::atomic<bool> threadHelper::staticFlags::s_interrupt_ = false;
std::atomic<bool> threadHelper::staticFlags::s_kill_ = false;
void thrFunc() noexcept//Placeholder function
{
	while (1)
	{
		if (threadHelper::staticFlags::s_kill_)
			return;
		if (threadHelper::staticFlags::s_interrupt_)
		{
			std::cout << "SLEEPING\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			
		}
		else
		{
			std::cout << "WORKING\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		if (threadHelper::staticFlags::s_kill_)
			return;
	}
}
threadHelper::threadHelper(void(*func)())
{
	pThread_ = new std::thread(func);
}
threadHelper::threadHelper(std::function<void()> func)
{
	pThread_ = new std::thread(func);
}
threadHelper::~threadHelper()
{
	killThread();
	delete pThread_;
}
void threadHelper::killThread()
{
	staticFlags::s_kill_ = true;
	if (pThread_->joinable())
		pThread_->detach();
}
void threadHelper::joinThread()
{
	if (pThread_->joinable())
		pThread_->join();
}
void threadHelper::interruptThread()
{
	if (!staticFlags::s_kill_)
		staticFlags::s_interrupt_ = true;
}
void threadHelper::resumeThread()
{
	if (!staticFlags::s_kill_)
		staticFlags::s_interrupt_ = false;
}