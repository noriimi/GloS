#pragma once
#include <atomic>
#include <thread>
#include <functional>
void thrFunc()noexcept;
class threadHelper
{
public:
	threadHelper(void (*func)());
	threadHelper(std::function<void()>);
	~threadHelper();
	void killThread();
	void interruptThread();
	void resumeThread();
	void joinThread();
	friend void thrFunc() noexcept;
private:
	static std::atomic <bool> s_kill_;
	static std::atomic<bool> s_interrupt_;
	std::thread* pThread_;
};

