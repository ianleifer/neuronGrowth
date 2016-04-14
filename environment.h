#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "cmn_struct.h"
#include "coordinates.h"
#include "cmn_defines.h"
#include "output.h"

/*
In Hentschel and van Ooyen (1999) a model is presented in which growing axons
on a plain are modeled by means of differential equations for the locations
of the growth cones. These equations are coupled to diffusion equations that describe
the concentration fields of diffusible chemoattractants and chemorepellents
(henceforth referred to as guidance molecules). The system is simplified by using
quasi-steady-state approximations for the concentration fields. This approach
turns the problem of solving a system consisting of PDEs (partial differential equations)
plus ODEs (ordinary differential equations) into a much simpler problem
where only ODEs have to be solved. This works fine as long as the whole plain is
used as a domain for the diffusion equations, but we also want to be able to consider
more general domains with, for example, areas where diffusion cannot take
place (“holes”) or with boundaries. Also, Krottje (2003a) showed that in Hentschel
and van Ooyen’s approach moving growth cones that secrete diffusible guidance
molecules upon which they respond themselves cause the speed of growth to be
strongly dependent on the diameter of the growth cone (a phenomenon that was
called self-interaction). The use of a quasi-steady-state approximation will then
result in heavily distorted dynamics.
*/

#define OLDANGLEWEIGHT 0

#define SOURCERADIUS  0

#if (NUMBEROFDIMENSIONS == 2)
#define SOURCE(x, y)       (x == 0 && y == 0) ? 1 : 0
#define TriS(x, y, xi, yi) ( SOURCE(xi - x, yi - y) )
#endif

//#define SOURCE(ro)    ( ( ro > 2 ) ? 0 : 1 )
#define GAUSSBELL(ro) ( 2 * M_PI / ( ( pow(double(M_PI), 2) - 4 ) * pow(double(SOURCERADIUS), 2) ) * pow(cos ( M_PI / ( 2 * SOURCERADIUS) * ro), 2 ) )

/* For random */
#include <cstdlib>
/* When rand is nine it`s 1 othewise 0 */
#define PRODUCTIONRATE 1
//( rand()%10 % 8 )

class Environment {
private:
	Environment();
	static Environment* p_environment;
	Output *output;

	int numberOfSources;
	Coordinates *sources;

	double field[NUMBEROFCELLSX][NUMBEROFCELLSY][NUMBEROFNEURONTYPES];
	/* Declaration moved here because of stack overflow exception.
	When we try to get 400x400 array of doubles we need about megabyte in stack that is treated like unusual behavior and it causes exception */
	double tmpField[NUMBEROFCELLSX][NUMBEROFCELLSY];

	void solveEquation(int type);
public:
	static Environment* Environment::getEnvironment();

	struct Direction getDirection(Coordinates coord, int type, double angle = 0);
	void addSource(Coordinates coord, int type);
	void printSources();

	double getField(int x, int y, int type);

	void tick();
};

#endif