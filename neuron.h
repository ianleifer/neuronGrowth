#ifndef NEURON_H
#define NEURON_H

#include "cmn_struct.h"
#include "neurite.h"
#include "chart.h"

class Neuron {
private:
	Output *output;
	int NeuronId;
	Coordinates coord;
	int neuronType;
	int timer;

	int addAxon(Coordinates coordinates);
	int numberOfAxons;
	Axon *axons;

	int addDendrite(Coordinates coordinates);
	int numberOfDendrites;
	Dendrite *dendrites;

	bool fired;
	double synapticCurrent;
	double neuronPotential[WORKTIME + 1];
	double Um[WORKTIME + 1];
	double izhik_Vm();
	double izhik_Um();
	void solvePotentialEquation();
	int numberOfSynapses;
public:
	static int NeuronCounter;
	void resetIdCounter();

	Neuron();
	~Neuron();
	void setCoordinates(int x, int y);
	void setCoordinates(Coordinates tmpCoord);
	
	void pushPotentialToChart(LineChart &lineChart);
	void tick();
	void addSynaps();
	void transferPerturbation();

	Neuron& operator=(Neuron &neuron);
	int getNeuronId();
	Coordinates getCoordinates();
	int getNeuronType();
	int getNumberOfAxons();
	int getNumberOfDendrites();
	Axon getAxon(int neuriteId);
	Dendrite getDendrite(int neuriteId);
	int getNumberOfSynapses();
	bool isFired();
};

#endif