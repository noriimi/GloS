#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
class SerialPort
{
public:
	SerialPort();
	std::string Read();
	void Send(std::string);
	bool openPort(std::string &);
	void initPort(unsigned Baudrate, unsigned ByteSize, unsigned StopBits, unsigned Parity);
	void closePort();
	static std::string parse(LPCWSTR);

private:
	HANDLE hSerial_;
	DCB dcb{0};
	};

