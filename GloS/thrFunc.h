#pragma once
#define NOMINMAX
#define NUMOFLEDS 60
#define NUMOFSAMPLES 512
#include<iostream>
#include<array>
#include"PortsFinder.hpp"
#include<chrono>
#include<vector>
#include"SerialPort.hpp"
#include"RtAudio/RtAudio.h"
#include"simple_fft/fft.hpp"
#include"threadHelper.hpp"
void thrFunc(int16_t data[],unsigned rs) noexcept//Placeholder function
{
	static std::array<double, NUMOFSAMPLES> A;
	static std::array<complex_type, NUMOFSAMPLES> B;
	static const char* error;
	static unsigned cursor = 0;
	static unsigned pos = 0;
	static std::vector<double> pool;
	uint8_t frame[184];
	frame[0] = 0xDE;
	frame[1] = 0xAD;
	frame[2] = 0xBE;
	frame[3] = 0xEF;
	PortsFinder finder{};
	finder.find();
	auto port = SerialPort::parse(finder.getFoundPort(0));
	std::cout << "Found port : " << port << std::endl;
	SerialPort serial(port, 115200, 8, ONESTOPBIT, NOPARITY, FALSE);
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
			if (threadHelper::staticFlags::s_read_)
			{
				int i = 0;
				for (auto& it : A)
				{
					it = (data[i] / 32768.0f);
					//it = (data[i] / 8192.0f);
					//it=(0);
					i++;
				}
				threadHelper::staticFlags::s_read_ = false;
			}
			simple_fft::FFT(A, B, NUMOFSAMPLES, error);
			for (int i = 0; i < NUMOFSAMPLES/2; i++)
			{
				B.at(i).real(4 * std::abs(B.at(i)));
			}
			cursor = 0;
			pos = 0;
			for (float i = 0; i < NUMOFLEDS; i++)
			{
				
				pos = std::ceil((i + 1.0f) / rs);
				
				frame[5 + 3 * (int)i] = 200;
				for (int i = 1; i <= pos; i++)
				{
					pool.push_back(B.at(++cursor).real());
				}
				frame[6 + 3 * (int)i] = (uint8_t)*std::max_element(pool.begin(), pool.end());
				frame[4 + 3 * (int)i] = frame[6 + 3 * (int)i];
				pool.clear();  

			}



			
			serial.UpdateLED(frame, 184);
		}
		if (threadHelper::staticFlags::s_kill_)
			return;
	}
}