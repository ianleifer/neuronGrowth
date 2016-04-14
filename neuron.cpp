#include "neuron.h"
#include "cmn_defines.h"

int Neuron::NeuronCounter = 0;

void Neuron::resetIdCounter() {
   NeuronCounter = 0;
};

/* For random */
#include <cstdlib>
Neuron::Neuron() {
	output = output->getOutput();
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

	numberOfConnections = 0;
	connections = new Connection[numberOfConnections];

	PRINTTRACE("neuron", "Neuron with id " + std::to_string(NeuronId) + " was created");
};

Neuron::~Neuron() {
	NeuronCounter--;
	delete [] axons;
	delete [] dendrites;
	delete [] connections;
}

void Neuron::setCoordinates(int x, int y) {//TODO: proper checking of coordinates availability
	ENTER_FUNCTION("neuron", "setCoordinates(int x, int y). x = " + std::to_string(x) + ", y = " + std::to_string(y));
	coord.SetX(x);
	coord.SetY(y);
#ifdef NEUROGENESIS
	if(x > NUMBEROFCELLSX / 2) {neuronType = 1;}
	else {neuronType = 0;}
#endif

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
};

int Neuron::addDendrite(Coordinates coordinates) {
	ENTER_FUNCTION("neuron", "addDendrite(Coordinates coordinates)");
	dynamicArrayRealloc(Dendrite, dendrites, numberOfDendrites);

	dendrites[numberOfDendrites - 1].setType(DENDRITE);
	dendrites[numberOfDendrites - 1].setNeuronId(NeuronId);
	dendrites[numberOfDendrites - 1].setNeuronType(neuronType);
	dendrites[numberOfDendrites - 1].setCoordinates(coordinates);
	
	PRINTTRACE("neuron", "Neuron id " + std::to_string(NeuronId) + " now has new dendrite. The number of dendrites: " + std::to_string(numberOfDendrites));
	return 0;
};

int Neuron::addConnection(int growthConeId, Neuron* neuron, int extraDelay) {
	ENTER_FUNCTION("neuron", "addConnection(int growthConeId, Neuron* neuron). Source: neuronId = " + std::to_string(NeuronId) + ", Destination: neuronId = " + std::to_string(neuron->getNeuronId()) + "; growthConeId = " + std::to_string(growthConeId));
	Connection *tmpConnections;
	tmpConnections = new Connection[numberOfConnections];
	for(int i = 0; i < numberOfConnections; i++) {
		tmpConnections[i].neuron = connections[i].neuron;
		tmpConnections[i].delay  = connections[i].delay;
	}

	connections = new Connection[++numberOfConnections];

	for(int i = 0; i < numberOfConnections - 1; i++) {
		connections[i].neuron = tmpConnections[i].neuron;
		connections[i].delay  = tmpConnections[i].delay;
	}

	delete [] tmpConnections;

	connections[numberOfConnections - 1].neuron = neuron;
	connections[numberOfConnections - 1].delay  = extraDelay + (int)axons[0].getGrowthConeDistance(growthConeId);
		//(int)axons->getGrowthConeDistance(growthConeId);
	
	PRINTTRACE("neuron", "Neuron id " + std::to_string(NeuronId) + " now has new connection with delay " + std::to_string(connections[numberOfConnections - 1].delay) + ". The number of connections: " + std::to_string(numberOfConnections) + "");
	return 0;
};

void Neuron::tick() {
	ENTER_FUNCTION("neuron", "Neuron::tick(). NeuronId = " + std::to_string(NeuronId));
	Environment *environment;
	environment = environment->getEnvironment();
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
};

Neuron& Neuron::operator=(Neuron &neuron) {
	NeuronId          = neuron.getNeuronId();
	coord             = neuron.getCoordinates();
	neuronType        = neuron.getNeuronType();

	numberOfAxons     = neuron.getNumberOfAxons();
	for(int i = 0; i < numberOfAxons; i++)
		axons[i]      = neuron.getAxon(i);

	numberOfDendrites = neuron.getNumberOfDendrites();
	for(int i = 0; i < numberOfDendrites; i++)
		dendrites[i]  = neuron.getDendrite(i);

	numberOfConnections = neuron.getNumberOfConnections();
/*	for(int i = 0; i < numberOfConnections; i++) {
		connections[i].neuron = neuron.getConnection(i).neuron;
		connections[i].delay  = neuron.getConnection(i).delay;
	}*/
	return *this;
};

int Neuron::getNeuronId() {
	return NeuronId;
};

Coordinates Neuron::getCoordinates() {
	return coord;
};

int Neuron::getNeuronType() {
	return neuronType;
};

int Neuron::getNumberOfAxons() {
	return numberOfAxons;
};

int Neuron::getNumberOfDendrites() {
	return numberOfDendrites;
};

Axon Neuron::getAxon(int neuriteId) {
	return axons[neuriteId];
};

Dendrite Neuron::getDendrite(int neuriteId) {
	return dendrites[neuriteId];
};

int Neuron::getNumberOfConnections() {
	return numberOfConnections;
};

int Neuron::getConnectionDestination(int connectionId) {
	return connections[connectionId].neuron->getNeuronId();
};

int Neuron::getConnectionDelay(int connectionId){
	return connections[connectionId].delay;
};

/*struct Connection Neuron::getConnection(int connectionId) {
	return connections[connectionId];
};*/