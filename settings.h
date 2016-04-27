#ifndef SETTINGS_H
#define SETTINGS_H

/************************************/
/*			General settings		*/
/************************************/

#define NUMBEROFDIMENSIONS 2

#define NUMBEROFCELLSX 5
#define NUMBEROFCELLSY 5

#define WORKTIME 50000

#define MAXNUMBEROFNEURONS 4
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
#define CONNECTIONTRACES
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

#define SYNAPTICDISTURBANCETEST1
#ifdef SYNAPTICDISTURBANCETEST1
#undef MAXNUMBEROFNEURONS
#define MAXNUMBEROFNEURONS 3
#endif

//#define AXONGROWTH
//#define DENDRITEGROWTH

/************************************/
/*		End of general settings		*/
/************************************/

/************************************/
/*			Picture settings		*/
/************************************/

#define PICTURESIZEX	1200
#define PICTURESIZEY	600
#define PICTURESCALEX	PICTURESIZEX / NUMBEROFCELLSX
#define PICTURESCALEY	PICTURESIZEY / NUMBEROFCELLSY
#define ENVIRONMENTINTENSITYMULTIPLIER	10
#define NUMBEROFXVALUELABELS	4
#define NUMBEROFYVALUELABELS	4

//#define DIFFUSIONVISIBLE

/************************************/
/*		End of picture settings		*/
/************************************/

/************************************/
/*		 Output file settings		*/
/************************************/

#define LOGFILENAME     "stat/log.txt"
#define LENGTHSTATISTICSFILE  "stat/length.txt"
#define ENVIRONMENTSTATISTICSFILE  "stat/environment.txt"
#define CONNECTIVITYGRAPHSTATISTICSFILE  "stat/connectivitygraph.txt"
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
#define IzhikevichVpeak		0
#define IzhikevichV0		-60
#define IzhikevichU0		0
#define IzhikevichCm		50
#define IzhikevichNoise		15
#define IzhikevichG			5

/************************************/
/*End of Izhikevich model constants	*/
/************************************/


#endif