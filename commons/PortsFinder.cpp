#include "PortsFinder.hpp"

bool PortsFinder::find()
{
	bool isFound = false;
	wchar_t lpTargetPath[1000];
	for (int i = 0; i <= 8; i++)
	{
		if (QueryDosDeviceW(lpDeviceName[i], (LPWSTR)lpTargetPath, 1000))
		{
			foundPorts_.push_back(lpDeviceName[i]);
			isFound = true;
		}
	}
	return isFound;
}

const wchar_t*& PortsFinder::getFoundPort(unsigned position)
{
	return foundPorts_.at(position);
}
size_t PortsFinder::numberOfPorts()
{
	return foundPorts_.size();
}
std::string PortsFinder::parse(LPCWSTR source)
{
	size_t size = 0;
	size = wcsnlen_s(source, 10);
	if (size > 1)
	{
		std::string test = "";
		for (auto i = 0; i < size; i++)
		{
			test += char(source[i]);
		}
		return test;
	}
	else
		return "";
}
