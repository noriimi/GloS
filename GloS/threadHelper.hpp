#pragma once
#include <atomic>
#include <thread>
#include <functional>
typedef int16_t sample_t;
class threadHelper
{
public:
	template<class _Fn,class ... _Args>
	explicit threadHelper(_Fn&& _Fx, _Args&&... _Ax)
	{
		pThread_ = new std::thread(std::forward<_Fn>(_Fx), std::forward<_Args>(_Ax)...);
	}
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
		friend void thrFunc(sample_t[],unsigned,const std::string&) noexcept;
		friend int record(void* outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streamTime, unsigned int status, void* userData);
	};
	
private:
	
	std::thread* pThread_;
	
};

