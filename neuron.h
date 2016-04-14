#ifndef NEURON_H
#define NEURON_H

#include "cmn_struct.h"
#include "neurite.h"
#include "connection.h"

class Neuron {
private:
	Output *output;
	int NeuronId;
	Coordinates coord;
	int neuronType;

	int addAxon(Coordinates coordinates);
	int numberOfAxons;
	Axon *axons;

	int addDendrite(Coordinates coordinates);
	int numberOfDendrites;
	Dendrite *dendrites;

	int numberOfConnections;
	//Connection *connections;
	struct Connection {
		Neuron *neuron;
		int delay;
		//double probability;
	}*connections;
public:
	static int NeuronCounter;
	void resetIdCounter();

	Neuron();
	~Neuron();
	void setCoordinates(int x, int y);
	void setCoordinates(Coordinates tmpCoord);

	int addConnection(int growthConeId, Neuron* neuron, int extraDelay);

	Neuron& operator=(Neuron &neuron);
	int getNeuronId();
	Coordinates getCoordinates();
	int getNeuronType();
	int getNumberOfAxons();
	int getNumberOfDendrites();
	Axon getAxon(int neuriteId);
	Dendrite getDendrite(int neuriteId);
	int getNumberOfConnections();
	int getConnectionDestination(int connectionId);
	int getConnectionDelay(int connectionId);
	//struct Connection getConnection(int connectionId);

	void tick();
};

#endif