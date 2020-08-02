#pragma once
#include <string>
#include <fstream>
#include<tuple>
class ConfigLoader
{
public:
	ConfigLoader(const std::string& filename);
	~ConfigLoader();
	std::pair<std::string, int> interpret();
private:
	std::ifstream file;
};

