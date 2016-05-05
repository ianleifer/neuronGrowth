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
	~Configurator();
	std::string configurationPath;

	void readConfiguration();
	void setConfigurationPath();
	void readConnectionConfiguration();

	/********************************/
	/* Configuration is stored here */
	/********************************/

	/* Connection configuration */
	bool connectionsConfigured;
	int numberOfConnections;
	int *connections[3];
	/* End of Connection configuration */

	/* Growth and activity configuration */
	int growthEndTimer;
	/* End of growth and activity configuration */

	/********************************/
	/*		End of configuration	*/
	/********************************/
public:
	static Configurator* getConfigurator();
	
	/********************************/
	/*			 Interface			*/
	/********************************/
	
	/* Connection configuration */
	bool areConnectionsConfigured();
	int getNumberOfConnections();
	int getSource(int connectionNumber);
	int getDestination(int connectionNumber);
	int getDelay(int connectionNumber);
	/* End of Connection configuration */

	int getGrowthEndTimer();
};

#endif