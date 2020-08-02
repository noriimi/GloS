#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
class PortsFinder
{
public:
	bool find();
	const wchar_t *& getFoundPort(unsigned);
	size_t numberOfPorts();
	static std::string parse(LPCWSTR);
private:
	std::vector<const wchar_t*> foundPorts_;
	const wchar_t* lpDeviceName[9]= { L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6", L"COM7", L"COM8", L"COM9" };

};

