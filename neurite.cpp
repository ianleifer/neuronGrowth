#include "neurite.h"
#include "environment.h"
#include "cmn_defines.h"

Neurite::Neurite() {
	numberOfGrowthCones      = 0;
	numberOfTerminalElements = 0;
	output = output->getOutput();
}

Neurite::~Neurite() {
	if(numberOfGrowthCones != 0) {
		delete [] growthCones;
	}
}

#include <stdlib.h> /* For rand() */
#define _USE_MATH_DEFINES //for Pi in visual studio 2009 and earlier
#include <math.h>
void Neurite::addGrowthCone(int growthConeId) {
	ENTER_FUNCTION("neurite", "addGrowthCone(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	dynamicArrayRealloc(GrowthCone, growthCones, numberOfGrowthCones);
	
	if (growthConeId != -1) {
		growthCones[numberOfGrowthCones - 1] = growthCones[growthConeId];
		growthCones[growthConeId].printStats();
		growthCones[numberOfGrowthCones - 1].printStats();
	}
	else {
		growthCones[numberOfGrowthCones - 1].setCoordinates(coordinates);
		growthCones[numberOfGrowthCones - 1].setDirection(double( rand()%8 - 4 ) / 8 * ( M_PI * 2 ));
	#ifdef CONNECTIVITYTEST1
	//		growthCones[numberOfGrowthCones - 1].setDirection(M_PI * 2);
	#endif
		growthCones[numberOfGrowthCones - 1].setNeuronType(neuronType);
	}
}

void Neurite::setCoordinates(Coordinates coord) {
	ENTER_FUNCTION("neurite", "setCoordinates(Coordinates coord). Neurite NeuronId = " + std::to_string(NeuronId));
	coordinates = coord;
	//TODO:Growth cone coordinates shouldn`t be set here. Think where to move initialisation
	addGrowthCone();
	growthCones[0].setCoordinates(coordinates);
}

void Neurite::setNeuronId(int newId) {
	ENTER_FUNCTION("neurite", "setNeuronId(int newId). newId = " + std::to_string(newId));
	NeuronId = newId;
}

void Neurite::setType(int Type) {
	ENTER_FUNCTION("neurite", "setType(int Type). Type = " + std::to_string(Type));
	type = Type;
}

void Neurite::setNeuronType(int Type) {
	ENTER_FUNCTION("neurite", "setNeuronType(int Type). Type = " + std::to_string(Type));
	neuronType = Type;
}

double Neurite::getGrowthConeDistance(int growthConeId) {
	return growthCones[growthConeId].getSomaDistance();
}

void Neurite::growNeurite(int growthConeId, double delta, int branching) {
	ENTER_FUNCTION("neurite", "growNeurite(int growthConeId, double delta, bool branching). growthConeId = " + std::to_string(growthConeId) + ", delta = " + std::to_string(delta) + ", branching = " + std::to_string(branching));
	if(branching == 1 && numberOfGrowthCones >= MAXNUMBEROFGROWTHCONES) {branching = 0; PRINTTRACE("neurite", "Branching disabled. Max number of growth cones exceeded");}
	if(growthCones[growthConeId].isGrowthEnabled()) {
		Coordinates oldCoordinates = growthCones[growthConeId].getCoordinates();
		double oldDirection = growthCones[growthConeId].getDirection();

		//get direction from environment
		struct Direction direction;
		Environment *environment = environment->getEnvironment();
		direction = environment->getDirection(oldCoordinates, neuronType, oldDirection);

		if (branching == 1) {
			struct Direction twoDirections[2];
			getTwoDirections(direction, twoDirections);

			PRINTTRACE("neurite", "It`s time to branch now for neuron with neuron id " + std::to_string(NeuronId) + " and growth cone id " + std::to_string(growthConeId));

			increaseGrowthConeCentrifugalOrder(growthConeId);
			addGrowthCone(growthConeId);

			growGrowthCone(oldCoordinates, delta, twoDirections[0], type, NeuronId, numberOfGrowthCones - 1);
			growthCones[numberOfGrowthCones - 1].setDirection(twoDirections[0].fi);

			growGrowthCone(oldCoordinates, delta, twoDirections[1], type, NeuronId, growthConeId);
			growthCones[growthConeId].setDirection(twoDirections[1].fi);
		}
		else {
			growGrowthCone(oldCoordinates, delta, direction, type, NeuronId, growthConeId);
			// Second check is added for case growth was disabled while growing out of bounds
			if (branching == -1 && growthCones[growthConeId].isGrowthEnabled()) {disableGrowth(growthConeId);}
		}
	}
}

void Neurite::growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId) {
	ENTER_FUNCTION("neurite", "growGrowthCone(Coordinates coord, double delta, struct Direction direction, int type, int NeuronId, int growthConeId). delta = " + std::to_string(delta) +
		", direction.fi = " + std::to_string(direction.fi) + ", type = " + std::to_string(type) + 
		", NeuronId = " + std::to_string(NeuronId) + ", growthConeId = " + std::to_string(growthConeId));
	Coordinates newCoordinates = coord;
	double realDelta = newCoordinates.findNewCoordinates(coord, delta, direction, type, NeuronId, growthConeId, 0);
	if (realDelta != -1) {
		growthCones[growthConeId].move(newCoordinates, realDelta);
	}
	else {
		PRINTTRACE("neurite", "realDelta == " + std::to_string(realDelta) + "; disabling growth");
		disableGrowth(growthConeId);
	}
}

void Neurite::disableGrowth(int growthConeId) {
	ENTER_FUNCTION("neurite", "disableGrowth(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	growthCones[growthConeId].disableGrowth();
	printTerminationStats(growthConeId);
	numberOfTerminalElements++;
	PRINTTRACE("neurite", "numberOfTerminalElements for neuron " + std::to_string(NeuronId) + " neurite is now " + std::to_string(numberOfTerminalElements));
}

void Neurite::increaseGrowthConeCentrifugalOrder(int growthConeId) {
	ENTER_FUNCTION("neurite", "increaseGrowthConeCentrifugalOrder(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	printTerminationStats(growthConeId);
	growthCones[growthConeId].increaseCentrifugalOrder();
}

void Neurite::printTerminationStats(int growthConeId) {
	ENTER_FUNCTION("neurite", "printTerminationStats(int growthConeId)");
	int co = growthCones[growthConeId].getCentrifugalOrder();
	double length = growthCones[growthConeId].getSomaDistance() - growthCones[growthConeId].getPreviousLevelLength();
	PRINTTRACE("neurite", "Soma dist = " + std::to_string(growthCones[growthConeId].getSomaDistance()) + ". Previous length = " + std::to_string(growthCones[growthConeId].getPreviousLevelLength()));
	PRINTTRACE("neurite", "Level " + std::to_string(co) + " terminated. Length = " + std::to_string(length));
	PRINTSTATISTICS(LENGTHSTATISTICKSFILEID, "" + std::to_string(co) + "\t" + std::to_string(length));
}

#include <stdlib.h> /* For rand() */

void Neurite::tick() {
	ENTER_FUNCTION("neurite", "Neurite::tick(). NeuronId = " + std::to_string(NeuronId));
	double delta;
	int numberOfGrowthConesBeforeTick = numberOfGrowthCones;
	for(int i = 0; i < numberOfGrowthConesBeforeTick; i++) {
		growthCones[i].tick();
		if ( ( delta = solveEquation(i) ) > 0) {
			growNeurite(i, delta, solveEmbranchmentEquation(i));
		}
	}
}

#include <math.h>
double Axon::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Axon::solveEquation(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	double delta;
	/* Coefficients below and formulas for growth are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha = 0.5;
	double betta = 1.1;
	double c0    = 14;
	double T     = 0.2927;
	double Vat   = 12;
	double k     = 0.035;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * pow ( 1 + k * length, 2 ) * exp ( - ( T * length / Vat ) ) - betta;
	PRINTTRACE("neurite", "Solved axon equation of neuron with id " + std::to_string(NeuronId) + " and growth cone id " + std::to_string(growthConeId) + ". Delta = " + std::to_string(delta));
	return delta;
	//return 110;
}

int Axon::solveEmbranchmentEquation(int growthConeId) {
//	return rand()%2;
	return false;
}

#include <math.h>
double Dendrite::solveEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Dendrite::solveEquation(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	double delta;
	/* Coefficients below and formulas for growth are taken from Mironov, Semyanov, Kazantsev "Dendrite and axon specific geometrical adaptation in neurite development" */
	double alpha = 1.1;
	double betta = 1.18;
	double c0    = 14;
	double T     = 0.005;
	double Vat   = 40;
	double k     = 0.0001;
	double length = getGrowthConeDistance(growthConeId);
	delta = alpha * c0 * exp ( ( k - T / Vat ) * length ) - betta;
	delta = delta / numberOfGrowthCones;
	//delta = delta / 2;
	PRINTTRACE("neurite", "Solved dendrite equation of neuron with id " + std::to_string(NeuronId) + " and growth cone id " + std::to_string(growthConeId));
	return delta;
}

#include <math.h>
/* All statistic formulas are taken from Jaap van Pelt, Harry B.M. Uylings "Modeling Neuronal Growth and Shape" - pp 195-215 */
#define E     (double)1
#define D(t)  (double)1 //exp 
#define S     (double)1
#define gamma (double)growthCones[growthConeId].getCentrifugalOrder()
#define C(t)  (double)1
int Dendrite::solveEmbranchmentEquation(int growthConeId) {
	ENTER_FUNCTION("neurite", "Dendrite::solveEmbranchmentEquation(int growthConeId). growthConeId = " + std::to_string(growthConeId));
	/* Probability to create terminal segment */
	//if(rand()%10 / 10 > 0.8) {return -1;};
	double branchingProbability = D(t) * pow(numberOfGrowthCones, -E) * pow(2, - S * gamma) / C(t);

	if (branchingProbability > 1 || branchingProbability < 0) {ERRORTRACE("neurite", "ERROR!!!!!!!!!!!!!!!!!!branchingProbability < 0 or > 1\n\n\n\n\n\n\n");}
	PRINTTRACE("neurite", "numberOfGrowthCones = " + std::to_string(numberOfGrowthCones) + ", gamma = " + std::to_string(gamma) + ", branchingProbability = " + std::to_string(branchingProbability));

	double probability = double(rand()%100 - 10) / 100;
	PRINTTRACE("neurite", "chance = " + std::to_string(probability) + ", " + std::to_string(probability < branchingProbability));
	if(probability < branchingProbability) {return 1;};
	return 0;
}
#undef E
#undef D
#undef S
#undef gamma
#undef C

Neurite& Neurite::operator=(Neurite &neurite) {
	type = neurite.getType();
	coordinates = neurite.getCoordinates();
	NeuronId    = neurite.getNeuronId();
	neuronType  = neurite.getNeuronType();

	numberOfGrowthCones = neurite.getNumberOfGrowthCones();
	for(int i = 0; i < numberOfGrowthCones; i++) {
		growthCones[i] = neurite.getGrowthCone(i);
	}
	return *this;
}

int Neurite::getType() {
	return type;
}

int Neurite::getNumberOfGrowthCones() {
	return numberOfGrowthCones;
}

GrowthCone Neurite::getGrowthCone(int growthConeId) {
	return growthCones[growthConeId];
}

Coordinates Neurite::getCoordinates() {
	return coordinates;
}

int Neurite::getNeuronId() {
	return NeuronId;
}

int Neurite::getNeuronType() {
	return neuronType;
}