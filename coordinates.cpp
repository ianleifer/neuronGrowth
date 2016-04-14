#include "coordinates.h"
#include "cmn_defines.h"

Coordinates::Coordinates() {
	output = output->getOutput();
}

Coordinates& Coordinates::operator=( Coordinates &coord ) {
	CoordX = coord.CoordX;
	CoordY = coord.CoordY;
	return *this;
};

void Coordinates::PrintCoordinates() {
	ENTER_FUNCTION("coordinates", "PrintCoordinates()");
	PRINTTRACE("coordinates", "X = " + std::to_string(CoordX) + "; Y = " + std::to_string(CoordX));
	if(!XYCORRECTIONCHECKER(CoordX, CoordY)) {ERRORTRACE("coordinates", "ERROR!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\n");}
};

void Coordinates::SetX(int x) {
	CoordX = x;
};

void Coordinates::SetY(int y) {
	CoordY = y;
};

int Coordinates::GetX() {
	return CoordX;
};

int Coordinates::GetY() {
	return CoordY;
};

#define _USE_MATH_DEFINES //for Pi in visual studio 2009 and earlier
#include <math.h> //For sin, cos and pi
#include "cellStack.h"

double Coordinates::findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId, int somaDistance) {
	ENTER_FUNCTION("coordinates", "findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId). delta = " + std::to_string(delta) +
		", direction.fi = " + std::to_string(direction.fi) + ", cellType = " + std::to_string(cellType) + ", NeuronId = " + std::to_string(NeuronId) +
		", growthConeId = " + std::to_string(growthConeId) + ". Old coordinates:");
	oldCoordinates.PrintCoordinates();
	double realDelta;
	double oldX = oldCoordinates.GetX();
	double oldY = oldCoordinates.GetY();
	if (delta < 1) {
		realDelta = 0;
	}
	else {
		CellStack *cellStack = cellStack->getStack();
		int tmpCoordX = (int) (double)oldX;
		int tmpCoordY = (int) (double)oldY;
		for(int i = 1; i <= delta; i++) {
			tmpCoordX = (int) ( (double)oldX + (double)i * cos(direction.fi) );
			tmpCoordY = (int) ( (double)oldY + (double)i * sin(direction.fi) );
		
			if ( (tmpCoordX == CoordX) && (tmpCoordY == CoordY) ) {continue;}
			if (!XYCORRECTIONCHECKER(tmpCoordX, tmpCoordY)) {return -1;}

			CoordX = tmpCoordX;
			CoordY = tmpCoordY;
			Coordinates coord;
			coord.SetX(CoordX);
			coord.SetY(CoordY);
			/* TODO: neurite ID is not defined!!!!!!!!!!!!!!!!!!!! */
			Cell cell(coord, cellType, NeuronId, -1, growthConeId, somaDistance + (int)findDistanceBetween((double)CoordX, (double)CoordY, oldX, oldY));
			if(!cellStack->isFull()) {cellStack->stackPush(cell);}
		}
		cellStack->PrintStack();
		if (CoordX == oldX && CoordY == oldY) {
			realDelta = 0;
		}
		else {
			realDelta = pow( pow( double(CoordX - oldX), 2 ) + pow( double(CoordY - oldY), 2 ), 0.5 );
		}
	}
	PRINTTRACE("coordinates", "After finding coordinates real delta is " + std::to_string(realDelta) + ", new coordinates:");
	PrintCoordinates();
	return realDelta;
};

double Coordinates::findDistanceBetween(double x1, double y1, double x2, double y2) {
	return (x1 == x2 && y1 == y2) ? 0 : pow( 
		                                pow( double(x1 - x2), 2 ) + 
		                                pow( double(y1 - y2), 2 )
										    , 0.5 );
};

void getTwoDirections(struct Direction direction, struct Direction *twoDirections) {
	twoDirections[0].fi = direction.fi + M_PI / 4;
	twoDirections[1].fi = direction.fi - M_PI / 4;
};