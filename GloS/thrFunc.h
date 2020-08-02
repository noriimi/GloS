#pragma once
#define NOMINMAX
#define NUMOFLEDS 60
#define NUMOFSAMPLES 512

#include<iostream>
#include<array>
#include<chrono>
#include<vector>
#include"SerialPort.hpp"
#include"../commons/RtAudio/RtAudio.h"
#include"simple_fft/fft.hpp"
#include"threadHelper.hpp"
#define MULTIPLIER 1
#define LOGf 0
#if LOGf 
#include<fstream>
#endif
void thrFunc(sample_t data[],unsigned rs, const std::string& serialname) noexcept//Placeholder function
{
#if LOGf
	std::ofstream myfile;
	myfile.open("LOG.txt");
	myfile << "Header\n";
#endif
	static std::array<double, NUMOFSAMPLES> A;
	static std::array<complex_type, NUMOFSAMPLES> B;
	static const char* error;
	static unsigned cursor = 0;
	static unsigned pos = 0;
	static double maxo = 0;
	static std::vector<double> pool;
	static double tes;
	uint8_t frame[184];
	frame[0] = 0xDE;
	frame[1] = 0xAD;
	frame[2] = 0xBE;
	frame[3] = 0xEF;
	//std::string serialname = "COM1";
	SerialPort serial(serialname, 115200, 8, ONESTOPBIT, NOPARITY, FALSE);
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
					it = (data[i]);
					i++;
				}
				threadHelper::staticFlags::s_read_ = false;
			}
			simple_fft::FFT(A, B, NUMOFSAMPLES, error);
			for (int i = 0; i < NUMOFSAMPLES/2; i++)
			{
				B.at(i).real( MULTIPLIER*std::abs(B.at(i))/256/4);
			}
			cursor = 0;
			pos = 0;
			maxo = (*std::max_element(B.begin(), B.begin()+255, [](const complex_type& lhs, const complex_type& rhs){ return rhs.real() > lhs.real(); })).real();
			printf("%f\t", maxo);
			tes = maxo;
			maxo = 254 / maxo;
			maxo = maxo >= 32 ? 32 : maxo;
			maxo = maxo < 1 ? 1 : maxo;
			for (float i = 0; i < NUMOFLEDS; i++)
			{
				
				pos = std::ceil((i + 1.0f) / rs);
				
				frame[5 + 3 * (int)i] = 200;
				for (int j = 1; j <= pos; j++)
				{
					pool.push_back(B.at(cursor++).real());
				}
				frame[4 + 3 * (int)i] = (uint8_t)(std::min(255.0,*std::max_element(pool.begin(), pool.end())));
				frame[6 + 3 * (int)i] =frame[4 + 3 * (int)i]<20?0: frame[4 + 3 * (int)i];
#if LOGf
				myfile << (int)frame[6 + 3 * (int)i] << '\t';
#endif
				pool.clear();  

			}


			
			serial.UpdateLED(frame, 184);
			printf("%f\t%f\n", maxo,maxo*tes);
#if LOGf
			myfile << '\n';
#endif
		}
		if (threadHelper::staticFlags::s_kill_)
		{
#if LOGf 
			myfile.close();
#endif
			return;
		}
	}
}