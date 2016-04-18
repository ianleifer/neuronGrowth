#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iostream>
#include <string>
#include "settings.h"

#define LOGFILEID						0
#define LENGTHSTATISTICKSFILEID			1
#define CONNECTIVITYGRAPHSTATICSFILEID	2
#define ENVIRONMENTSTATISTICSFILEID		3

class Output {
private:
	static Output *p_Output;
	Output();
	~Output();
	
	std::ofstream logFile;
	std::ofstream lenghtStatisticsFile;
	std::ofstream connectivityGraphStatisticsFile;
	std::ofstream environmentStatisticsFile;

	void openOutputFiles();
	void closeOutputFiles();
public:
	static Output* getOutput();

	void enterFunctionTrace(std::string fileName, std::string trace);
	void printTrace(std::string fileName, std::string trace, int traceGroup = -1);
	void printErrorTrace(std::string fileName, std::string trace);
	void printToFile(int outputFile, std::string trace);
	bool isPrintingEnabled(int traceGroup);
};

/* There are 5 trace groups.
	0 - Enter function
	1 - Branching traces
	2 - Growth cone
	3 - Connection
	4 - Cell stack
	5 - Error traces
	6 - Coordinates
*/
#define TG(tgIx) (1 << tgIx)

#endif