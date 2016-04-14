#ifndef NEURITE_H
#define NEURITE_H

#include "cellStack.h"
#include "growthCone.h"
#include "coordinates.h"
#include "output.h"

class Neurite {
protected:
	Output *output;
	//Axon AXON, dendrite DENDRITE
	int type;
	int neuronType;

	int numberOfGrowthCones;
	GrowthCone *growthCones;
	void addGrowthCone(int growthConeId = -1);

	Coordinates coordinates;
	int NeuronId;

	void growNeurite(int growthConeId, double delta, int branching);
	void growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId);
	int numberOfTerminalElements;
	void disableGrowth(int growthConeId);
	void increaseGrowthConeCentrifugalOrder(int growthConeId);

	void printTerminationStats(int growthConeId);

	virtual double solveEquation(int growthConeId) = 0;
	virtual int solveEmbranchmentEquation(int growthConeId) = 0;
public:
	Neurite();
	~Neurite();

	void setCoordinates(Coordinates coord);	//Should be used right after creation and nowhere else
	void setNeuronId(int newId);
	void setType(int Type);
	void setNeuronType(int Type);

	Neurite& operator=(Neurite &neurite);
	int getType();
	int getNumberOfGrowthCones();
	GrowthCone getGrowthCone(int growthConeId);
	Coordinates getCoordinates();
	int getNeuronId();
	int getNeuronType();

	double getGrowthConeDistance(int growthConeId);
	void tick();
};

class Axon : public Neurite {
private:
	double solveEquation(int growthConeId);
	int solveEmbranchmentEquation(int growthConeId);
};

class Dendrite : public Neurite {
private:
	double solveEquation(int growthConeId);
	int solveEmbranchmentEquation(int growthConeId);
};

#endif