#pragma once
#include <Windows.h>
#include <iostream>
class SerialPort
{
public:
	SerialPort();
	std::string Read();
	void Send(const char *);
	bool openPort(const char*);
	void initPort(unsigned Baudrate, unsigned ByteSize, unsigned StopBits, unsigned Parity);
	void closePort();
private:
	HANDLE hSerial_;
	DCB dcb{0};



};

