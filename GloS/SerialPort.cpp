#include "SerialPort.hpp"
SerialPort::SerialPort()
{

}
void SerialPort::Send(std::string packet)
{
	unsigned long NoOfBytesWritten=0;
	WriteFile(hSerial_,
		packet.c_str()
		,packet.size()
		, &NoOfBytesWritten, NULL);
}
std::string SerialPort::Read()
{
	return "";
}
bool SerialPort::openPort(std::string& nameOfPort)
{
	hSerial_ = CreateFileA(nameOfPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hSerial_ == INVALID_HANDLE_VALUE)
		return false;
	else
		return true;


}
void SerialPort::initPort(unsigned Baudrate,unsigned ByteSize,unsigned StopBits,unsigned Parity)
{
	dcb.BaudRate = Baudrate;
	dcb.ByteSize = ByteSize;
	dcb.StopBits = StopBits;
	dcb.Parity = Parity;
	SetCommState(hSerial_, &dcb);


}
void SerialPort::closePort()
{
	CloseHandle(hSerial_);
}

std::string SerialPort::parse(LPCWSTR source)
{
	unsigned size = 0;
	while (source[size] != '\0')
		size++;
	if (size > 1)
	{
		std::string test = "";
		for (int i = 0; i < size; i++)
		{
			test += char(source[i]);
		}
		return test;
	}
	else
		return "";
}
void SerialPort::operator<<(std::string& packet)
{
	this->Send(packet);
}
void SerialPort::operator<<(const char* packet)
{
	this->Send(std::string(packet));
}