#include "hippocampus.h"
#include "neuron.h"

Hippocampus* Hippocampus::p_Hippocampus = 0;

Hippocampus* Hippocampus::getHippocampus() {
	if(!p_Hippocampus) {
		p_Hippocampus = new Hippocampus();
	}
	return p_Hippocampus;
}

/* For random */
#include <cstdlib>

Hippocampus::Hippocampus() {
	mode = 0;
	timer = 0;
	numberOfNeurons = 0;
	numberOfSynapses = 0;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronType[i][j] = NOTHING;

	for(int i = 0; i < NUMBEROFCELLSX; i++)
		for(int j = 0; j < NUMBEROFCELLSY; j++)
			neuronIds[i][j] = 0;
	output = output->getOutput();
	configurator = configurator->getConfigurator();
}

Hippocampus::~Hippocampus() {
	if(numberOfNeurons != 0) {delete [] neurons;}
	if(numberOfSynapses != 0) {delete [] synapses;}
}

#include "cellStack.h"
void Hippocampus::checkStack() {
	ENTER_FUNCTION("hippocampus", "checkStack()");
	CellStack *cellStack = cellStack->getStack();
	while(!cellStack->isEmpty()) {
		Cell cell = cellStack->stackPop();
		Coordinates coordinates;
		coordinates = cell.getCoordinates();
		int x = coordinates.GetX();
		int y = coordinates.GetY();
		switch(neuronType[x][y])
		{
		case NOTHING:
			// Case field is clear
			fillField(x, y, cell.getCellType(), cell.getNeuronId());
			break;
		case DENDRITE:
			// Case we need to create a new connection
			// Axon can be connected to dendrite
			if(cell.getNeuronId() != neuronIds[x][y] && cell.getCellType() == AXON) {
				addSynaps(cell.getNeuronId(), neuronIds[x][y], cell.getSomaDistance());
			}
			break;
		case AXON:
			// Case we need to create a new connection
			// Dendrite can be connected to axon
			if(cell.getNeuronId() != neuronIds[x][y] && cell.getCellType() == DENDRITE) {
				addSynaps(neuronIds[x][y], cell.getNeuronId(), cell.getSomaDistance());
			}
			break;
		}
	}
}

int Hippocampus::addNeuron(int x, int y) {
	ENTER_FUNCTION("hippocampus", "addNeuron(int x, int y). x = " + std::to_string(x) + ", y = " + std::to_string(y));
	//TODO: fix recursive bug. Add counter to prevent loop
	//TODO: use cell stack to add neuron
	if (numberOfNeurons < MAXNUMBEROFNEURONS) {
		bool availability = false, randomity = false;
		if ((x == -1) && (y == -1)) {x = rand()%(NUMBEROFCELLSX - 2) + 1; y = rand()%(NUMBEROFCELLSY - 2) + 1; randomity = true;}
		if (getFieldType(x, y) == NOTHING) {availability = true;}

		if (availability == true) {
			createNeuron();
            neurons[numberOfNeurons - 1].setCoordinates(x, y);
            fillField(x, y, NEURON, numberOfNeurons - 1);
		}
		else {
			if (randomity == true)
				addNeuron();
			else {
				PRINTTRACE("hippocampus", "Can`t create neuron here (" + std::to_string(x) + ", " + std::to_string(y) + ")");
			}
		}
	}
	return 0;
}

void Hippocampus::fillField(int x, int y, char type, int neuronId) {
	ENTER_FUNCTION("hippocampus", "fillField(int x, int y, char type, int neuronId). x = " + std::to_string(x) + ", y = " + std::to_string(y) + ", type = " + std::to_string(type) + ", neuronId = " + std::to_string(neuronId));
	neuronType[x][y] = type;
	neuronIds[x][y]  = neuronId;

	PRINTTRACE("hippocampus", "Space (" + std::to_string(x) + ", " + std::to_string(y) + ") is now `" + std::to_string(getFieldType(x, y)) + "` type with id " + std::to_string(neuronIds[x][y]));
}

void Hippocampus::createNeuron() {
	ENTER_FUNCTION("hippocampus", "createNeuron. numberOfNeurons = " + std::to_string(numberOfNeurons));
	if (numberOfNeurons < MAXNUMBEROFNEURONS) {
		Neuron *tmpNeurons;
		neurons->resetIdCounter();
		tmpNeurons = new Neuron[numberOfNeurons];
		for(int i = 0; i < numberOfNeurons; i++)
			tmpNeurons[i] = neurons[i];

		neurons->resetIdCounter();
		neurons = new Neuron[++numberOfNeurons];

		for(int i = 0; i < numberOfNeurons - 1; i++)
			neurons[i] = tmpNeurons[i];

		delete [] tmpNeurons;
	}
	PRINTTRACE("hippocampus", "Hippocampus now has " + std::to_string(numberOfNeurons) + " neurons");
}

Neuron* Hippocampus::getNeuronById(int neuronId) {
	Neuron* neuron = NULL;
	for(int i = 0; i < numberOfNeurons; i++) {
		if (neurons[i].getNeuronId() == neuronId) {
			neuron = neurons + i;
			break;
		}
	};
	return neuron;
}

void Hippocampus::addSynaps(int sourceId, int destinationId, double delay) {
	Neuron *source = getNeuronById(sourceId);
	Neuron *destination = getNeuronById(destinationId);
	if(numberOfSynapses != 0) {dynamicArrayRealloc(Synaps, synapses, numberOfSynapses);}
	else {synapses = new Synaps; numberOfSynapses++;}
	synapses[numberOfSynapses - 1].Set(source, destination, delay * 10);
	source->addSynaps();
	PRINTTRACETG("hippocampus", "Added new synaps between neuron " + std::to_string(source->getNeuronId()) + " and neuron " + std::to_string(destination->getNeuronId()), TG(3));
}

void Hippocampus::fireSynapses() {
	for(int i = 0; i < numberOfSynapses; i++)
		synapses[i].tick();
}

/************************/
/*      Interface       */
/************************/

void Hippocampus::tick(int t) {
	ENTER_FUNCTION("hippocampus", "Hippocampus tick");
	if (numberOfNeurons == 0) {
		#ifdef CONNECTIVITYTEST1
			addNeuron(NUMBEROFCELLSX/2 - 50, NUMBEROFCELLSY/2);
			addNeuron(NUMBEROFCELLSX/2 + 50, NUMBEROFCELLSY/2);
		#else
			addNeuron(NUMBEROFCELLSX/2, NUMBEROFCELLSY/2);
		#endif

		for (int i = 0; i < MAXNUMBEROFNEURONS; i++) {
			addNeuron();
		}

		#ifdef SYNAPTICDISTURBANCETEST1
		addSynaps(0, 1);
		#endif
		if(configurator->areConnectionsConfigured()) {
			for(int i = 0; i < configurator->getNumberOfConnections(); i++)
				addSynaps(configurator->getSource(i), configurator->getDestination(i), configurator->getDelay(i));
		}
	}
	mode = configurator->getWorkMode(timer);
	
	for(int i = 0; i < numberOfNeurons; i++)
		neurons[i].tick();
	if(mode == 0) {
		checkStack();
	}

	if(mode == 1) {
		fireSynapses();
	}

	#ifdef CONNECTIVITYGRAPHSTATISTICS
		if( (t % CONNECTIVITYGRAPHSTATISTICSRATE) == 1 ) {printConnectivityGraphStatistics();}
	#endif
	//if(numberOfNeurons == 0) {addNeuron(2, 5); addNeuron(2, 15); addNeuron(2, 25); addNeuron(7, 25); addNeuron(3, 25);}
	timer++;
}

void Hippocampus::printConnectivityGraphStatistics() {
	ENTER_FUNCTION("hippocampus", "printConnectivityGraphStatistics()");

	if(numberOfSynapses == 0) {return;}
	if(numberOfNeurons != 0) {
		PRINTSTATISTICS(CONNECTIVITYGRAPHSTATICSFILEID, "Number of synapses:");

		for(int i = 0; i < numberOfNeurons; i++) {
			PRINTSTATISTICS(CONNECTIVITYGRAPHSTATICSFILEID, std::to_string(i) + "\t" + std::to_string(neurons[i].getNumberOfSynapses()));
		}
		
		PRINTSTATISTICS(CONNECTIVITYGRAPHSTATICSFILEID, "Synapses are:\nSource\tDestination\tDelay");
		for(int i = 0; i < numberOfSynapses; i++)
			synapses[i].printSynaps();
	}
}

void Hippocampus::feelPotentialsChart(LineChart &lineChart) {
	for(int i = 0; i < MAXNUMBEROFNEURONS; i++) {
		lineChart.setTmpChartIndex(i);
		neurons[i].pushPotentialToChart(lineChart);
	}
}

int Hippocampus::getFieldType(int x, int y) {
	return neuronType[x][y];
}

double Hippocampus::getPotential(int x, int y) {
	if(neuronType[x][y] == NEURON) {return getNeuronById(neuronIds[x][y])->getPotential();}
	else {return -1;}
}