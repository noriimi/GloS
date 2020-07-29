
#include "threadHelper.hpp"
std::atomic<bool> threadHelper::staticFlags::s_interrupt_ = false;
std::atomic<bool> threadHelper::staticFlags::s_kill_ = false;
std::atomic<bool> threadHelper::staticFlags::s_read_ = false;

threadHelper::threadHelper(void(*func)(sample_t[],unsigned ),sample_t data[],unsigned rs)
{
	pThread_ = new std::thread(func,data,rs);
}
threadHelper::threadHelper(std::function<void(sample_t[],unsigned)> func,sample_t data[],unsigned rs)
{
	pThread_ = new std::thread(func,data,rs);
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