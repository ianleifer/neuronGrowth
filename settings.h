#ifndef SETTINGS_H
#define SETTINGS_H

#include "configuration.h"

/************************************/
/*			General settings		*/
/************************************/

#define NUMBEROFDIMENSIONS 2

#define NUMBEROFCELLSX 200
#define NUMBEROFCELLSY 200

#define WORKTIME 50000

#define MAXNUMBEROFNEURONS 3
#define MAXNUMBEROFGROWTHCONES 16

#define NUMBEROFNEURONTYPES 2
#define INTERACTION00 ( 0.0 )
#define INTERACTION01 ( 1.0 )
#define INTERACTION10 ( 1.0 )
#define INTERACTION11 ( 0.0 )

//#define STEPBYSTEP
#define STOPONERROR

//#define TRACESON
#define TRACEINFILE
/* TODO: create trace groups */
#define ENTERFUNCTIONTRACES
//#define CELLSTACKTRACES
//#define GROWTHCONETRACES
//#define CONNECTIONTRACES
//#define BRANCHINGTRACES

#define STATISTICSON
#ifdef STATISTICSON
//#define LENGTHSTATISTICS
//#define ENVIRONMENTSTATISTICS
#define CONNECTIVITYGRAPHSTATISTICS
#endif

//#define CONNECTIVITYTEST1
#ifdef CONNECTIVITYTEST1
#undef MAXNUMBEROFNEURONS
#define MAXNUMBEROFNEURONS 2
#endif

//#define SYNAPTICDISTURBANCETEST1
#ifdef SYNAPTICDISTURBANCETEST1
#undef MAXNUMBEROFNEURONS
#define MAXNUMBEROFNEURONS 2
#endif

#define AXONGROWTH
#define DENDRITEGROWTH

/************************************/
/*		End of general settings		*/
/************************************/

/************************************/
/*			Picture settings		*/
/************************************/
//#define BIGSCREEN
#ifdef BIGSCREEN
#define PICTURESIZEX	1400
#define PICTURESIZEY	1000
#else
#define PICTURESIZEX	800
#define PICTURESIZEY	600
#endif

#define PICTURESCALEX	PICTURESIZEX / NUMBEROFCELLSX
#define PICTURESCALEY	PICTURESIZEY / NUMBEROFCELLSY
#define ENVIRONMENTINTENSITYMULTIPLIER	10
#define NUMBEROFXVALUELABELS	4
#define NUMBEROFYVALUELABELS	4
#define MAXPOTENTIALPICTUREWIDTH	500

//#define DIFFUSIONVISIBLE

/************************************/
/*		End of picture settings		*/
/************************************/

/************************************/
/*		 Output file settings		*/
/************************************/

#define LOGFILENAME     "output/log.txt"
#define LENGTHSTATISTICSFILE  "output/length.txt"
#define ENVIRONMENTSTATISTICSFILE  "output/environment.txt"
#define CONNECTIVITYGRAPHSTATISTICSFILE  "output/connectivitygraph.txt"
#define CONNECTIVITYGRAPHSTATISTICSRATE 100

/************************************/
/*		End of output file settings	*/
/************************************/

/************************************/
/*		Izhikevich model constants	*/
/************************************/

#define IzhikevichH			1
#define IzhikevichIex		0
#define IzhikevichA			0.02
#define IzhikevichB			0.5
#define IzhikevichC			-40
#define IzhikevichD			100
#define IzhikevichK			0.5
#define IzhikevichVr		-60
#define IzhikevichVt		-45
#define IzhikevichVpeak		30
#define IzhikevichV0		-60
#define IzhikevichU0		0
#define IzhikevichCm		50
#define IzhikevichNoise		15
#define IzhikevichG			3

/************************************/
/*End of Izhikevich model constants	*/
/************************************/


#endif