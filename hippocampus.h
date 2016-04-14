#ifndef HIPPOCAMPUS_H
#define HIPPOCAMPUS_H

#include "neuron.h"
#include "cmn_defines.h"
#include "cmn_struct.h"
#include "output.h"

class Hippocampus {
private:
	static Hippocampus *p_Hippocampus;
	Hippocampus();
	int numberOfNeurons;
	Neuron *neurons;
	Output *output;

	/* TODO: Hippocampus must contain cells. It is more logical */
	int neuronType[NUMBEROFCELLSX][NUMBEROFCELLSY];
	int neuronIds[NUMBEROFCELLSX][NUMBEROFCELLSY];

	void checkStack();
	int  addNeuron(int x = -1, int y = -1);
	void fillField(int x, int y, char type, int neuronId);
	void createNeuron();
	Neuron* getNeuronById(int neuronId);
public:
	static Hippocampus* getHippocampus();
	int getFieldType(int x, int y);
	void printConnectivityGraphStatistics();
	void tick(int t);
};

#endif