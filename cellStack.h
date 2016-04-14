#ifndef CELLSTACK_H
#define CELLSTACK_H

#include "cmn_struct.h"
#include "output.h"

class CellStack {
private:
	static CellStack *p_CellStack;
	Output *output;
	int numberOfCells;
	Cell *cells;
public:
	CellStack();
	~CellStack();
	static CellStack* getStack();
	int stackPush(Cell cell);
	Cell stackPop();
	bool isEmpty();
	bool isFull();
	void PrintStack();
};

#endif