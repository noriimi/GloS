#pragma once
#include <string>
#include <fstream>
#include<tuple>
class ConfigLoader
{
public:
	ConfigLoader(const std::string& filename);
	~ConfigLoader();
	const std::pair<const std::string,const int> interpret();
private:
	std::ifstream file;
};

