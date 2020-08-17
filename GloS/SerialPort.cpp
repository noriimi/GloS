#include "SerialPort.hpp"
#include <Windows.h>
SerialPort::SerialPort(std::string nameOfPort, unsigned Baudrate, unsigned ByteSize, unsigned StopBits, unsigned Parity, unsigned XON)
{
	hSerial_ = CreateFileA(nameOfPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	dcb.BaudRate = Baudrate;
	dcb.ByteSize = ByteSize;
	dcb.StopBits = StopBits;
	dcb.Parity = Parity;
	if (XON) {
		char xn = 17;
		char xf = 19;
		dcb.fOutX = XON;
		dcb.XoffChar = xf;
		dcb.XonChar = xn;
	}
	SetCommState(hSerial_, &dcb);
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
}
void SerialPort::Send(const std::string& packet) const
{
	unsigned long NoOfBytesWritten=0;
	WriteFile(hSerial_,	packet.c_str(),(DWORD)packet.size(), &NoOfBytesWritten, NULL);
}
void SerialPort::Send(void* source,const size_t& size) const
{
	unsigned long NoOfBytesWritten = 0;
	WriteFile(hSerial_,source, (DWORD)size, &NoOfBytesWritten, NULL);
}
const std::string SerialPort::Read()
{//TODO
	/*bool Status;
	DWORD dwEventMask;
	char TempChar;
	char SerialBuffer[256];
	DWORD NoBytesRead;
	int i = 0;
	std::string result;
	
	
	Status = SetCommMask(hSerial_, EV_RXCHAR);
	Status = WaitCommEvent(hSerial_, &dwEventMask, NULL);
	if (Status)
	{
		do
		{
			Status = ReadFile(hSerial_, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
			SerialBuffer[i] = TempChar;
			i++;
			
		}
		while ((NoBytesRead > 0)&&SerialBuffer[2]!='\n');
	}
	int j = 0;
	for (j = 0; j < i - 1; j++)
		result += SerialBuffer[j];
	return result;*/
	return "";
}
bool SerialPort::isOpen() const
{
	return !(hSerial_ == INVALID_HANDLE_VALUE);
}
void SerialPort::operator<<(const std::string& packet)
{
	this->Send(packet);
}
void SerialPort::operator<<(const char* packet)
{
	this->Send(std::string(packet));
}
SerialPort::~SerialPort()
{
	CloseHandle(hSerial_);
}
void SerialPort::UpdateLED(void* frame, const size_t& size)
{
	unsigned long NoOfBytesWritten = 0;
	WriteFile(hSerial_, frame, (DWORD)size, &NoOfBytesWritten, NULL);
}