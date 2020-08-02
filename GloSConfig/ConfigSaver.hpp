#pragma once
#include<string>
#include<fstream>
class ConfigSaver
{
public:
	ConfigSaver(const std::string& filename);
	~ConfigSaver();
	template<typename T>
	void operator<<(const T& text)
	{
		if (cfile.is_open())
			cfile << text;
	}
private:
	std::ofstream cfile;

};


