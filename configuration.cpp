#include "configuration.h"

Configurator* Configurator::p_Configurator = 0;

Configurator* Configurator::getConfigurator() {
	if(!p_Configurator) {
		p_Configurator = new Configurator();
	}
	return p_Configurator;
}

Configurator::Configurator() {
	connectionsConfigured = false;
	readConfiguration();
}

Configurator::~Configurator() {
	if(connectionsConfigured == true && numberOfConnections > 0) {
	for(int i = 0; i < 3; i++)
		delete [] connections[i];
	}
}

void Configurator::readConfiguration() {
	setConfigurationPath();
	readConnectionConfiguration();
}

void Configurator::setConfigurationPath() {
	std::string line;
	std::ifstream modeFile(MODEFILE);
	getline(modeFile, line, '\n');
	configurationPath = line + "/";
	modeFile.close();
}

//double *connections[3];

void Configurator::readConnectionConfiguration() {
	std::string line;
	std::ifstream connectionsConfigurationFile(configurationPath + "connectivityConfiguration.txt");
	getline(connectionsConfigurationFile, line, '\n');
	numberOfConnections = line[0] - '0';
	for(int i = 0; i < 3; i++)
		connections[i] = new int[numberOfConnections];

	for(int i = 0; i < numberOfConnections; i++) {
		getline(connectionsConfigurationFile, line, '\n');
		connections[0][i] = line[0] - '0';
		connections[1][i] = line[2] - '0';
		connections[2][i] = line[4] - '0';
	}

	connectionsConfigurationFile.close();
	connectionsConfigured = true;
}

bool Configurator::areConnectionsConfigured() {
	return connectionsConfigured;
}

int Configurator::getNumberOfConnections() {
	return numberOfConnections;
}

int Configurator::getSource(int connectionNumber) {
	if(connectionNumber >= 0 && connectionNumber < numberOfConnections) {
		return connections[0][connectionNumber];
	} else {
		return -1;
	}
}

int Configurator::getDestination(int connectionNumber) {
	if(connectionNumber >= 0 && connectionNumber < numberOfConnections) {
		return connections[1][connectionNumber];
	} else {
		return -1;
	}
}

int Configurator::getDelay(int connectionNumber) {
	if(connectionNumber >= 0 && connectionNumber < numberOfConnections) {
		return connections[2][connectionNumber];
	} else {
		return -1;
	}
}