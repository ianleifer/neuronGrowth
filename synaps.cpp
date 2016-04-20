#include "synaps.h"

Synaps::Synaps(Neuron *Source, Neuron *Destination, int Delay) {
	source = Source;
	destination = Destination;
	delay = Delay;
}