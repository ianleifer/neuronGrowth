#ifndef SYNAPS_H
#define SYNAPS_H

#include "neuron.h"
#include "output.h"

class Synaps {
private:
	Output *output;

	Neuron *source;
	Neuron *destination;
	double delay;
	//double probability;
public:
	Synaps();
	Synaps(Neuron *Source, Neuron *Destination, double Delay = -1);
	void Set(Neuron *Source, Neuron *Destination, double Delay = -1);

	void printSynaps();

	Synaps& operator=(Synaps &synaps);
	Neuron* getSource();
	Neuron* getDestination();
	double getDelay();
};

#endif