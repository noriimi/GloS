#pragma once
#include <atomic>
#include <thread>
#include <functional>
void thrFunc(int16_t[],unsigned)noexcept;
class threadHelper
{
public:
	threadHelper(void (*func)(int16_t[],unsigned),int16_t[],unsigned);
	threadHelper(std::function<void(int16_t[],unsigned)>, int16_t[],unsigned);
	~threadHelper();
	void killThread();
	void interruptThread();
	void resumeThread();
	void joinThread();
	class staticFlags {
		static std::atomic <bool> s_kill_;
		static std::atomic<bool> s_interrupt_;
		static std::atomic<bool> s_read_;
	public:
		friend class threadHelper;
		friend void thrFunc(int16_t[],unsigned) noexcept;
		friend int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, unsigned int status, void* userData);
	};
	
private:
	
	std::thread* pThread_;
	
};

