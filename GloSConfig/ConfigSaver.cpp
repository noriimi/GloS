#include "ConfigSaver.hpp"


ConfigSaver::ConfigSaver(const std::string& filename)
{
	
	cfile.open(filename);
	cfile << "GloSConfig\n";
}
ConfigSaver::~ConfigSaver()
{
	cfile.close();
	
}
