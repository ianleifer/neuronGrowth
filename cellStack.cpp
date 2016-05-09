#include "cellStack.h"
#include "cmn_struct.h"
#include "cmn_defines.h"

#define CELLSTACKMAXNUMBEROFCELLS ( NUMBEROFCELLSX * NUMBEROFCELLSY / 4 )

CellStack* CellStack::p_CellStack = 0;

CellStack::CellStack() {
	output = output->getOutput();
	ENTER_FUNCTION("cellStack", "CellStack::CellStack()");
	PRINTTRACETG("cellStack", "Cell stack created", TG(4));
	numberOfCells = 0;
	first = NULL;
};

CellStack::~CellStack() {
};

CellStack* CellStack::getStack() {
	if(!p_CellStack)
		p_CellStack = new CellStack();
	return p_CellStack;
};

int CellStack::stackPush(Cell cell) {
	ENTER_FUNCTION("cellStack", "stackPush()");
	if(numberOfCells >= CELLSTACKMAXNUMBEROFCELLS) {
		ERRORTRACE("cellStack", "Can`t push to stack max number of elements exceeded");
		return 1;
	}
	Node* newNode = new Node;
	newNode->cell = cell;
	
	if(first != NULL) {
		newNode->next = first;
	} else {
		newNode->next = NULL;
	}
	first = newNode;
	numberOfCells++;

	PRINTTRACETG("cellStack", "New element successfully pushed. Stack now has " + std::to_string(numberOfCells) + " elements", TG(4));
	cell.PrintCoordinates();
	return 0;
};

Cell CellStack::stackPop() {
	ENTER_FUNCTION("cellStack", "stackPull()");
	Cell cell;
	cell.makeEmpty();
	if(isEmpty()) {return cell;}

	cell = first->cell;

	Node* newFirst = first->next;
	delete [] first;
	first = newFirst;
	numberOfCells--;
	
	PRINTTRACETG("cellStack", "element successfully pulled from stack. Stack now has " + std::to_string(numberOfCells) + " elements", TG(4));
	cell.PrintCoordinates();
	return cell;
};

bool CellStack::isEmpty() {
	return (numberOfCells == 0)?1:0;
};

bool CellStack::isFull() {
	return (numberOfCells == CELLSTACKMAXNUMBEROFCELLS)?1:0;
};

void CellStack::PrintStack() {
	ENTER_FUNCTION("cellStack", "PrintStack");
	for(int i = 0; i < numberOfCells; i++) {
		//TRACE("cellStack", "");
	//	PRINTTRACE("cellStack", "Type of element " + std::to_string(i) + " is " + std::to_string(cells[i].getCellType()) + ", neuronId is " + std::to_string(cells[i].getNeuronId()) + ", growthConeId is " + std::to_string(cells[i].getGrowthConeId()) + " and coordinates are:");
	//	cells[i].PrintCoordinates();
	}
};