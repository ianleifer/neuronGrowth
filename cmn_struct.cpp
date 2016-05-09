#include "cmn_struct.h"

Cell& Cell::operator=( Cell &cell ) {
	IsEmpty      = cell.isEmpty();
	coordinates  = cell.getCoordinates();
	cellType     = cell.getCellType();
	NeuronId     = cell.getNeuronId();
	NeuriteId    = cell.getNeuriteId();
	growthConeId = cell.getGrowthConeId();
	somaDistance = cell.getSomaDistance();
	return *this;
}

Cell::Cell() {
	makeEmpty();
	output = output->getOutput();
}

Cell::Cell(Coordinates tmpCoordinates, int tmpCellType, int tmpNeuronId, int tmpNeuriteId, int tmpGrowthConeId, int tmpSomaDistance) {
	makeFull();
	output = output->getOutput();
	coordinates  = tmpCoordinates;
	cellType     = tmpCellType;
	NeuronId     = tmpNeuronId;
	NeuriteId    = tmpNeuriteId;
	growthConeId = tmpGrowthConeId;
	somaDistance = tmpSomaDistance;
}

void Cell::makeEmpty() {
	IsEmpty = true;
}

void Cell::makeFull() {
	IsEmpty = false;
}

bool Cell::isEmpty() {
	return IsEmpty;
}

Coordinates Cell::getCoordinates() {
	return coordinates;
}

int Cell::getCellType() {
	return cellType;
}

int Cell::getNeuronId() {
	return NeuronId;
}

int Cell::getNeuriteId() {
	return NeuriteId;
}

int Cell::getGrowthConeId() {
	return growthConeId;
}

int Cell::getSomaDistance() {
	return somaDistance;
}

void Cell::printCell() {
	PRINTTRACE("Cell", "Type of cell is " + std::to_string(cellType) + ", neuronId is " + std::to_string(NeuronId) + ", growthConeId is " + std::to_string(NeuriteId) + " and coordinates are:");
	coordinates.PrintCoordinates();
}