#ifndef CMN_STRUCT_H
#define CMN_STRUCT_H

#include "coordinates.h"

class Cell {
private:
	bool IsEmpty;
	Coordinates coordinates;
	//(nothing / neuron / axon / dendrite) (0/1/2/3)
	int cellType;
	int NeuronId;
	int NeuriteId;
	int growthConeId;
	int somaDistance;
public:
	Cell();
	Cell(Coordinates tmpCoordinates, int tmpCellType, int tmpNeuronId, int tmpNeuriteId, int tmpGrowthConeId, int tmpSomaDistance);
	Cell& operator=( Cell &cell );

	void makeEmpty();
	void makeFull();
	bool isEmpty();

	Coordinates getCoordinates();
	int getCellType();
	int getNeuronId();
	int getNeuriteId();
	int getGrowthConeId();
	int getSomaDistance();

	void PrintCoordinates();
};

#endif