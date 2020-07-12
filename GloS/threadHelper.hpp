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
	class staticFlags {
		static std::atomic <bool> s_kill_;
		static std::atomic<bool> s_interrupt_;
	public:
		friend class threadHelper;
		friend void thrFunc() noexcept;
		friend int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, unsigned int status, void* userData);
	};
	
private:
	
	std::thread* pThread_;
	
};

