#pragma once
#include <atomic>
#include <thread>
#include <functional>
typedef int16_t sample_t;
class threadHelper
{
public:
	threadHelper(void (*func)(sample_t[],unsigned),sample_t[],unsigned);
	threadHelper(std::function<void(sample_t[],unsigned)>, sample_t[],unsigned);
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
		friend void thrFunc(sample_t[],unsigned) noexcept;
		friend int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, unsigned int status, void* userData);
	};
	
private:
	
	std::thread* pThread_;
	
};

