#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
class SerialPort
{
public:
	SerialPort(std::string, unsigned Baudrate, unsigned ByteSize, unsigned StopBits, unsigned Parity, unsigned XON);
	~SerialPort();
	std::string Read();
	void Send(std::string);
	void Send(void*,size_t);
	void UpdateLED(void*,size_t size);
	bool isOpen();
	static std::string parse(LPCWSTR);
	void operator<<(std::string&);
	void operator<<(const char*);
private:
	HANDLE hSerial_;
	DCB dcb{0};
	COMMTIMEOUTS timeouts = { 0 };
	};

