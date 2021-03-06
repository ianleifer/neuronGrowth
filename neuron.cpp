#include "neuron.h"
#include "cmn_defines.h"

int Neuron::NeuronCounter = 0;

void Neuron::resetIdCounter() {
   NeuronCounter = 0;
}

/* For random */
#include <cstdlib>
Neuron::Neuron() {
	output = output->getOutput();
	environment = environment->getEnvironment();
	configurator = configurator->getConfigurator();
	timer = 0;
	ENTER_FUNCTION("neuron", "Neuron::Neuron()");
	if (NeuronCounter < MAXNUMBEROFNEURONS) {
		NeuronId = NeuronCounter++;
	};
	neuronType = rand()%NUMBEROFNEURONTYPES;
	#ifdef CONNECTIVITYTEST1
		neuronType = NeuronId;
	#endif

	numberOfAxons = 0;
	axons = new Axon[numberOfAxons];

	numberOfDendrites = 0;
	dendrites = new Dendrite[numberOfDendrites];

	numberOfSynapses = 0;

	for(int i = 0; i < WORKTIME; i++) {
		neuronPotential[i] = 0;
		Um[i] = 0;
		synapticCurrent[i] = 0;
	}
	neuronPotential[0]	= IzhikevichV0;
	Um[0]				= IzhikevichU0;
	fired = false;

	PRINTTRACE("neuron", "Neuron with id " + std::to_string(NeuronId) + " was created");
}

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
	delete [] dendrites;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	ENTER_FUNCTION("neuron", "setCoordinates(int x, int y). x = " + std::to_string(x) + ", y = " + std::to_string(y));
	coord.SetX(x);
	coord.SetY(y);

	PRINTTRACE("neuron", "Coordinates of neuron number " + std::to_string(NeuronId) + " were changed. New coordinates are:");
	coord.PrintCoordinates();
}

void Neuron::setCoordinates(Coordinates tmpCoord) {//TODO: proper checking of coordinates availability
	ENTER_FUNCTION("neuron", "setCoordinates(Coordinates tmpCoord)");
    coord = tmpCoord;

	PRINTTRACE("neuron", "Coordinates of neuron number " + std::to_string(NeuronId) + " were changed. New coordinates are:");
	coord.PrintCoordinates();
}

int Neuron::addAxon(Coordinates coordinates) {
	ENTER_FUNCTION("neuron", "addAxon(Coordinates coordinates)");
	dynamicArrayRealloc(Axon, axons, numberOfAxons);

	axons[numberOfAxons - 1].setType(AXON);
	axons[numberOfAxons - 1].setNeuronId(NeuronId);
	axons[numberOfAxons - 1].setNeuronType(neuronType);
	axons[numberOfAxons - 1].setCoordinates(coordinates);
	
	PRINTTRACE("neuron", "Neuron id " + std::to_string(NeuronId) + " now has new axon. The number of axons: " + std::to_string(numberOfAxons));
	return 0;
}

int Neuron::addDendrite(Coordinates coordinates) {
	ENTER_FUNCTION("neuron", "addDendrite(Coordinates coordinates)");
	dynamicArrayRealloc(Dendrite, dendrites, numberOfDendrites);

	dendrites[numberOfDendrites - 1].setType(DENDRITE);
	dendrites[numberOfDendrites - 1].setNeuronId(NeuronId);
	dendrites[numberOfDendrites - 1].setNeuronType(neuronType);
	dendrites[numberOfDendrites - 1].setCoordinates(coordinates);
	
	PRINTTRACE("neuron", "Neuron id " + std::to_string(NeuronId) + " now has new dendrite. The number of dendrites: " + std::to_string(numberOfDendrites));
	return 0;
}

double Neuron::izhik_Vm(){
	ENTER_FUNCTION("neuron", "Neuron::izhik_Vm(). NeuronId = " + std::to_string(NeuronId));
	double k	= IzhikevichK;
	double Vr	= IzhikevichVr;
	double Vt	= IzhikevichVt;
	double Iex	= IzhikevichIex;
	double Cm	= IzhikevichCm;
	return (k*(neuronPotential[timer] - Vr)*(neuronPotential[timer] - Vt) - Um[timer] + Iex + synapticCurrent[timer])/Cm;
}
 
double Neuron::izhik_Um(){
	ENTER_FUNCTION("neuron", "Neuron::izhik_Um(). NeuronId = " + std::to_string(NeuronId));
	double a	= IzhikevichA;
	double b	= IzhikevichB;
	double Vr	= IzhikevichVr;
	return a*(b*(neuronPotential[timer] - Vr) - Um[timer]);
}

void Neuron::solvePotentialEquation() {
	double h		= IzhikevichH;
	double Vpeak	= IzhikevichVpeak;
	double c		= IzhikevichC;
	double d		= IzhikevichD;
	double noise	= (IzhikevichNoise != 0) ? (- IzhikevichNoise / 2 + rand()%IzhikevichNoise) : 0;
	#ifdef SYNAPTICDISTURBANCETEST1
		if(NeuronId == 1) {noise = 0;}
	#endif
	fired = false;
	neuronPotential[timer + 1] = neuronPotential[timer] + h * izhik_Vm() + noise;
	Um			   [timer + 1] = Um[timer]				+ h * izhik_Um();

	if (neuronPotential[timer + 1] > Vpeak) {
		neuronPotential[timer + 1] = c;
		Um[timer + 1] = Um[timer] + d;
		fired = true;
	}
}

/************************************/
/*				Interface			*/
/************************************/
void Neuron::tick() {
	ENTER_FUNCTION("neuron", "Neuron::tick(). NeuronId = " + std::to_string(NeuronId));
	solvePotentialEquation();
	timer++;
	
	if(configurator->getWorkMode() == 1) {return;}
	environment->addSource(coord, neuronType);
	#ifndef CONNECTIVITYTEST1
		#ifdef AXONGROWTH
			if(numberOfAxons != 0) {
				for(int i = 0; i < numberOfAxons; i++)
					axons[i].tick();
			} else { 
				addAxon(coord);
			}
		#endif

		#ifdef DENDRITEGROWTH
			if(numberOfDendrites != 0) {
				for(int i = 0; i < numberOfDendrites; i++)
					dendrites[i].tick();
			} else {
				addDendrite(coord);
			}
		#endif
	#else
		if(NeuronId == 0) {
			if(numberOfAxons != 0) {
				for(int i = 0; i < numberOfAxons; i++)
					axons[i].tick();
			} else { 
				addAxon(coord);
			}
		} else {
			if(numberOfDendrites != 0) {
				for(int i = 0; i < numberOfDendrites; i++)
					dendrites[i].tick();
			} else {
				addDendrite(coord);
			}
		}
	#endif
}

void Neuron::addSynaps() {
	numberOfSynapses++;
}

void Neuron::transferPerturbation(double current, int delay) {
	synapticCurrent[timer + delay] += current;
}

Neuron& Neuron::operator=(Neuron &neuron) {
	NeuronId			= neuron.getNeuronId();
	coord				= neuron.getCoordinates();
	neuronType			= neuron.getNeuronType();
	numberOfSynapses	= neuron.getNumberOfSynapses();

	numberOfAxons     = neuron.getNumberOfAxons();
	for(int i = 0; i < numberOfAxons; i++)
		axons[i]      = neuron.getAxon(i);

	numberOfDendrites = neuron.getNumberOfDendrites();
	for(int i = 0; i < numberOfDendrites; i++)
		dendrites[i]  = neuron.getDendrite(i);

	return *this;
}

void Neuron::pushPotentialToChart(LineChart &lineChart) {
	for(int i = 0; i < timer; i++)
		lineChart.addNextValue(neuronPotential[i]);
}

int Neuron::getNeuronId() {
	return NeuronId;
}

Coordinates Neuron::getCoordinates() {
	return coord;
}

int Neuron::getNeuronType() {
	return neuronType;
}

int Neuron::getNumberOfAxons() {
	return numberOfAxons;
}

int Neuron::getNumberOfDendrites() {
	return numberOfDendrites;
}

Axon Neuron::getAxon(int neuriteId) {
	return axons[neuriteId];
}

Dendrite Neuron::getDendrite(int neuriteId) {
	return dendrites[neuriteId];
}

int Neuron::getNumberOfSynapses() {
	return numberOfSynapses;
}

double Neuron::getPotential(int Timer) {
	if(Timer == -1) {return neuronPotential[timer];}
	if(Timer < 0 || Timer > WORKTIME) {return NULL;}
	return neuronPotential[Timer];
}

bool Neuron::isFired() {
	return fired;
}