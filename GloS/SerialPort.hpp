#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
class SerialPort
{
public:
	SerialPort(std::string, unsigned Baudrate, unsigned ByteSize, unsigned StopBits, unsigned Parity, unsigned XON);
	~SerialPort();
	const std::string Read();
	void Send(const std::string&) const;
	void Send(void*,const size_t&) const;
	void UpdateLED(void*,const size_t& size);
	bool isOpen() const;
	void operator<<(const std::string&);
	void operator<<(const char*);
private:
	HANDLE hSerial_;
	DCB dcb{0};
	COMMTIMEOUTS timeouts = { 0 };
	};

