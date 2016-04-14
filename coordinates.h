#ifndef COORDINATES_H
#define COORDINATES_H

#include "output.h"

struct Direction {
	double fi;
};

//TODO:Better remove extern function as soon as it`s possible. just move it to environment class
extern void getTwoDirections(struct Direction direction, struct Direction *twoDirections);

class Coordinates {
private:
	Output *output;
	int CoordX;
	int CoordY;
public:
	Coordinates();
	Coordinates& operator=( Coordinates &coord );
	void PrintCoordinates();
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	double findNewCoordinates(Coordinates oldCoordinates, double delta, Direction direction, int cellType, int NeuronId, int growthConeId, int somaDistance); // Helps neurite to find new coordinates
	double findDistanceBetween(double x1, double y1, double x2, double y2);
};

#endif