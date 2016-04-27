#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <fstream>
#include <iostream>
#include <string>

#define MODEFILE "input/mode.txt"

class Configurator {
private:
	static Configurator *p_Configurator;
	Configurator();
	void readConfiguration();
public:
	static Configurator* getConfigurator();
};

#endif