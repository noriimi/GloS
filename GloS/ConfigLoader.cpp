#include "ConfigLoader.hpp"
#include <iostream>
#include<regex>
ConfigLoader::ConfigLoader(const std::string& filename)
{
	file.open(filename);
	std::cout << "Opened config\n";
}
ConfigLoader::~ConfigLoader()
{
	file.close();
}

std::pair<std::string, int> ConfigLoader::interpret()
{
	std::regex serialR("COM[0-9]");
	std::regex audioR("[0-9]");
	std::smatch matchesS;
	std::smatch matchesA;

	int audioDeviceId=0;
	std::string buffv;
	std::string serialName;
	std::getline(file, buffv, '\n');
	std::getline(file, buffv);
	while (std::regex_search(buffv, matchesS, serialR))
	{
		serialName = matchesS.str();
		buffv = matchesS.suffix().str();
	}
	std::getline(file, buffv);
	while (std::regex_search(buffv, matchesA, audioR))
	{
		audioDeviceId = std::stoi(matchesA.str());
		buffv = matchesA.suffix().str();
	}
	return std::pair<std::string, int>(serialName,audioDeviceId);
}
