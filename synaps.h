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
	void transferPerturbation();
public:
	Synaps();
	Synaps(Neuron *Source, Neuron *Destination, double Delay = -1);
	void Set(Neuron *Source, Neuron *Destination, double Delay = -1);

	void printSynaps();
	void tick();

	Synaps& operator=(Synaps &synaps);
	Neuron* getSource();
	Neuron* getDestination();
	double getDelay();
};

#endif