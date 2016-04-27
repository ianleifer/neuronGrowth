#include "configuration.h"

Configurator* Configurator::p_Configurator = 0;

Configurator* Configurator::getConfigurator() {
	if(!p_Configurator) {
		p_Configurator = new Configurator();
	}
	return p_Configurator;
}

Configurator::Configurator() {
	readConfiguration();
}

void Configurator::readConfiguration() {
	std::string line;
	std::ifstream configurationFile(MODEFILE);

	while(!configurationFile.eof()) {
		getline(configurationFile, line, '\n');
	}
	configurationFile.close();
}