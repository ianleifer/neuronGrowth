#ifndef CMN_DEFINES_H
#define CMN_DEFINES_H

#include "settings.h"

//(nothing / neuron / axon / dendrite) (0/1/2/3)
#define NOTHING    0
#define NEURON     1
#define AXON       2
#define	DENDRITE   3
#define GROWTHCONE 4

#define dynamicArrayRealloc(type, arrayName, numberOfElements)      \
	type *tmpArrayName;                                             \
	tmpArrayName = new type[numberOfElements];                      \
                                                                    \
	if (numberOfElements != 0) {                                    \
		for(int i = 0; i < numberOfElements; i++) {                 \
			tmpArrayName[i] = arrayName[i];                         \
		}                                                           \
        delete [] arrayName;                                        \
	}                                                               \
                                                                    \
	arrayName = new type[++numberOfElements];                       \
                                                                    \
	if (numberOfElements != 0) {                                    \
		for(int i = 0; i < numberOfElements - 1; i++) {             \
			arrayName[i] = tmpArrayName[i];                         \
		}                                                           \
	}                                                               \
                                                                    \
	delete [] tmpArrayName

#define XYCORRECTIONCHECKER(x, y) ( ( (x >= 0) && (y >= 0) && x < NUMBEROFCELLSX && y < NUMBEROFCELLSY ) ? 1 : 0 )

#include <stdio.h>
#include <cstring> // For strlen

#define PRINTTRACE(fileName, trace)			output->printTrace(fileName, trace)
#define ERRORTRACE(fileName, trace)			output->printErrorTrace(fileName, trace)
#define ENTER_FUNCTION(fileName, trace)		output->enterFunctionTrace(fileName, trace)
#define PRINTSTATISTICS(outputFile, trace)	output->printToFile(outputFile, trace)
//" + std::to_string(delta) + "

#endif