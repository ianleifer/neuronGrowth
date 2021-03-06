#ifndef HIPPOCAMPUS_H
#define HIPPOCAMPUS_H

#include "neuron.h"
#include "synaps.h"
#include "cmn_defines.h"
#include "cmn_struct.h"
#include "output.h"
#include "chart.h"

class Hippocampus {
private:
	/* There are two modes now. Growth and synaptic activity. We are now trying to have growth and then activity.
	0 - growth
	1 - activity */
	int mode;
	int timer;
	static Hippocampus *p_Hippocampus;
	Hippocampus();

	int numberOfNeurons;
	Neuron *neurons;
	int addNeuron(int x = -1, int y = -1);

	int numberOfSynapses;
	Synaps *synapses;
	void addSynaps(int sourceId, int destinationId, double delay = -1);

	Output *output;
	Configurator *configurator;

	/* TODO: Hippocampus must contain cells. It is more logical */
	int neuronType[NUMBEROFCELLSX][NUMBEROFCELLSY];
	int neuronIds[NUMBEROFCELLSX][NUMBEROFCELLSY];

	void checkStack();
	void fireSynapses();
	void fillField(int x, int y, char type, int neuronId);
	void createNeuron();
public:
	~Hippocampus();
	static Hippocampus* getHippocampus();
	int getFieldType(int x, int y);
	double getPotential(int x, int y);
	int getNumberOfSynapses();
	Synaps getSynaps(int idx);
	Neuron* getNeuronById(int neuronId);
	void printConnectivityGraphStatistics();
	void feelPotentialsChart(LineChart &lineChart);
	void tick(int t);
};

#endif