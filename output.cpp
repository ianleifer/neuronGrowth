#include "output.h"

Output* Output::p_Output = 0;

Output* Output::getOutput() {
	if(!p_Output) {
		p_Output = new Output();
	}
	return p_Output;
}

Output::Output() {
	openOutputFiles();
}

Output::~Output() {
	closeOutputFiles();
}

void Output::openOutputFiles() {
	logFile.open(LOGFILENAME, std::ios::out);
	lenghtStatisticsFile.open(LENGTHSTATISTICSFILE, std::ios::out);
	connectivityGraphStatisticsFile.open(CONNECTIVITYGRAPHSTATISTICSFILE, std::ios::out);
	environmentStatisticsFile.open(ENVIRONMENTSTATISTICSFILE, std::ios::out);
}

void Output::closeOutputFiles(){
	logFile.close();
	lenghtStatisticsFile.close();
	connectivityGraphStatisticsFile.close();
	environmentStatisticsFile.close();
}

void Output::printToFile(int outputFile, std::string trace) {
	switch(outputFile) {
	case LOGFILEID:
		logFile << trace << std::endl;
		break;
#ifdef STATISTICSON
	case LENGTHSTATISTICKSFILEID:
		lenghtStatisticsFile << trace << std::endl;
		break;
	case CONNECTIVITYGRAPHSTATICSFILEID:
		connectivityGraphStatisticsFile << trace << std::endl;
		break;
	case ENVIRONMENTSTATISTICSFILEID:
		environmentStatisticsFile << trace << std::endl;
		break;
#endif
	}
}

/* There are 5 trace groups.
	0 - Enter function
	1 - Branching traces
	2 - Growth cone
	3 - Connection
	4 - Cell stack
	5 - Error traces
*/
#define TG(tgIx) (1 << tgIx)
void Output::enterFunctionTrace(std::string fileName, std::string trace) {
	printTrace(fileName + ": Entering function", trace, TG(0));
}

#include <ctime>
void Output::printTrace(std::string fileName, std::string trace, int traceGroup) {
	bool enablePrinting = false;
	if(traceGroup != -1) {enablePrinting = isPrintingEnabled(traceGroup);}

	time_t currentTime;
	struct tm localTime;
	currentTime = time(NULL);
	localtime_s(&localTime, &currentTime);

	int Hour   = localTime.tm_hour;
	int Min    = localTime.tm_min;
	int Sec    = localTime.tm_sec;

	trace = std::to_string(Hour) + ":" + std::to_string(Min) + ":" + std::to_string(Sec) + ":" + trace;
	if(enablePrinting) {
		#ifdef TRACESON
			#ifdef TRACEINFILE
				printToFile(LOGFILEID, fileName + ": " + trace);
			#else
				std::cout << fileName << ": " << trace << std::endl;
			#endif
		#endif
	}
	if(traceGroup == TG(5)) {
		#ifdef STOPONERROR
			system("pause");
		#endif
	}
}

bool Output::isPrintingEnabled(int traceGroup) {
	bool enabled = false;
	if(traceGroup & TG(0)) {
		enabled = true;
	}
	if(traceGroup & TG(1)) {
	//	printf("Branching traces\n");
	}
	if(traceGroup & TG(2)) {
	//	printf("Growth cone\n");
	}
	if(traceGroup & TG(3)) {
	//	printf("Connection\n");
	}
	if(traceGroup & TG(4)) {
	//	printf("Cell stack\n");
	}
	if(traceGroup & TG(5)) {
		enabled = true;
	//	printf("Error traces\n");
	}
	return enabled;
}

void Output::printErrorTrace(std::string fileName, std::string trace) {
	//std::cout << "Error trace:" << fileName << ".cpp: " << trace << std::endl;
	printTrace(fileName + ": Error trace", trace, TG(5));
}