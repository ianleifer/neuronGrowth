#include "synaps.h"

Synaps::Synaps() {output = output->getOutput();}

Synaps::Synaps(Neuron *Source, Neuron *Destination, double Delay) {
	output = output->getOutput();
	Set(Source, Destination, Delay);
}

void Synaps::Set(Neuron *Source, Neuron *Destination, double Delay) {
	source = Source;
	destination = Destination;
	delay = Delay;
}

void Synaps::printSynaps() {
	PRINTSTATISTICS(CONNECTIVITYGRAPHSTATICSFILEID, std::to_string(source->getNeuronId()) + "\t" + std::to_string(destination->getNeuronId()) + "\t" + std::to_string(delay));
}

/* Operator= and get everything */

Synaps& Synaps::operator=(Synaps &synaps) {
	source		= synaps.getSource();
	destination = synaps.getDestination();
	delay		= synaps.getDelay();
	return *this;
}

Neuron* Synaps::getSource() {
	return source;
}

Neuron* Synaps::getDestination() {
	return destination;
}

double  Synaps::getDelay() {
	return delay;
}