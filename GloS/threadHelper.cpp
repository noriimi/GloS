#include "threadHelper.hpp"
#include <iostream>
#include <chrono>
std::atomic<bool> threadHelper::s_interrupt_ = false;
std::atomic<bool> threadHelper::s_kill_ = false;
void thrFunc() noexcept//Placeholder function
{
	while (1)
	{
		if (threadHelper::s_kill_)
			return;
		if (threadHelper::s_interrupt_)
		{
			std::cout << "WORKING\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		else
		{
			std::cout << "SLEEPING\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		if (threadHelper::s_kill_)
			return;
	}
}