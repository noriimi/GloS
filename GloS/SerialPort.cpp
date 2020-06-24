#include "SerialPort.hpp"
SerialPort::SerialPort()
{

}
void SerialPort::Send(const char * packet)
{
	DWORD NoOfBytesWritten=0;
	WriteFile(hSerial_, packet, sizeof(packet), &NoOfBytesWritten, NULL);
}
std::string SerialPort::Read()
{
	return "";
}
bool SerialPort::openPort(const char* nameOfPort)
{
	hSerial_ = CreateFileA(nameOfPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
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