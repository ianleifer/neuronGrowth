#ifndef SYNAPS_H
#define SYNAPS_H

#include "neuron.h"

class Synaps {
private:
	Neuron *source;
	Neuron *destination;
	int delay;
	//double probability;
public:
	Synaps(Neuron *Source, Neuron *Destination, int Delay = -1);
};

#endif