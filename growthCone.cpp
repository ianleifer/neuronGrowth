#include "growthCone.h"
#include "cmn_defines.h"

GrowthCone::GrowthCone() {
	output = output->getOutput();
	growthEnabled       = true;
	somaDistance        = 0;
	centrifugalOrder    = 1;
	previousLevelLength = 0;
	direction = 0;
};

void GrowthCone::setCoordinates(Coordinates coord) {
	ENTER_FUNCTION("growthCone", "setCoordinates(Coordinates coord)");
	coordinates = coord;
	PRINTTRACE("growthCone", "Coordinates now are:");
	coordinates.PrintCoordinates();
};

void GrowthCone::setNeuronType(int Type) {
	ENTER_FUNCTION("growthCone", "setNeuronType(int Type). Type = " + std::to_string(Type));
	neuronType = Type;
};

void GrowthCone::tick() {
	ENTER_FUNCTION("growthCone", "GrowthCone::tick(). Coordinates are:");
	coordinates.PrintCoordinates();
	/*
	Environment *environment;
	environment = environment->getEnvironment();
	environment->addSource(coordinates, neuronType);
	*/
};

void GrowthCone::disableGrowth() {
	ENTER_FUNCTION("growthCone", "disableGrowth()þ Coordinates are:");
	coordinates.PrintCoordinates();
	growthEnabled = false;
};

bool GrowthCone::isGrowthEnabled() {
	return growthEnabled;
};

void GrowthCone::move(Coordinates coord, double delta) {
	ENTER_FUNCTION("growthCone", "move(Coordinates coord, double delta). delta = " + std::to_string(delta));
	setCoordinates(coord);
	increaseSomaDistance(delta);
	printStats();
};

void GrowthCone::setDirection(double direct) {
	direction = direct;
};

void GrowthCone::increaseSomaDistance(double delta) {
	ENTER_FUNCTION("growthCone", "increaseSomaDistance(double delta). delta = " + std::to_string(delta));
	somaDistance += delta;
	PRINTTRACE("growthCone", "Soma distance is " + std::to_string(somaDistance) + " now");
};

void GrowthCone::increaseCentrifugalOrder() {
	ENTER_FUNCTION("growthCone", "increaseCentrifugalOrder()");
	centrifugalOrder++;
	previousLevelLength = somaDistance;

	PRINTTRACE("growthCone", "Centrifugal order is now " + std::to_string(centrifugalOrder) + ". previousLevelLength is " + std::to_string(previousLevelLength));
};

/*****************
	Interface
*****************/
GrowthCone& GrowthCone::operator=(GrowthCone &growthCone) {
	growthEnabled       = growthCone.isGrowthEnabled();
	somaDistance        = growthCone.getSomaDistance();
	direction           = growthCone.getDirection();
	coordinates         = growthCone.getCoordinates();
	centrifugalOrder    = growthCone.getCentrifugalOrder();
	previousLevelLength = growthCone.getPreviousLevelLength();
	neuronType          = growthCone.getNeuronType();
	return *this;
};

double GrowthCone::getSomaDistance() {
	return somaDistance;
};

double GrowthCone::getDirection() {
	return direction;
};

double GrowthCone::getPreviousLevelLength(){
	return previousLevelLength;
};

Coordinates GrowthCone::getCoordinates() {
	return coordinates;
};

int GrowthCone::getCentrifugalOrder() {
	return centrifugalOrder;
};

int GrowthCone::getNeuronType() {
	return neuronType;
};

void GrowthCone::printStats() {
	ENTER_FUNCTION("growthCone", "printStats()");

	PRINTTRACE("growthCone", "Growth cone stats. Soma distance = " + std::to_string(getSomaDistance()) + ", centrifugalOrder = " + std::to_string(centrifugalOrder) + " and coordinates are:");
	coordinates.PrintCoordinates();
};