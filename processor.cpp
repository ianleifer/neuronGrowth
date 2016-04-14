#include "processor.h"
#include "cmn_defines.h"

//For pause
#include <cstdlib>

#ifdef MEMORYCHECKING
#include <vld.h>
#endif

Processor::Processor() {
	output = output->getOutput();
	ENTER_FUNCTION("processor", "Processor::Processor()");
	hippocampus = hippocampus->getHippocampus();
	openGLInterface = openGLInterface->getOpenGLInterface();
	environment = environment->getEnvironment();
};

/*
Environment tick is the first tick. While this tick equations are solved and all growth cones will get directions after solving equation.
After tick all sources are deleted from environment to be refreshed on next hippocampus tick
Then happens hippocampus tick where equations for all neurons are solved. All neurons while ticking signalize themselves to environment
*/
void Processor::tick(int t) {
	hippocampus->tick(t);
	environment->tick();
	openGLInterface->tick();
};

#include <ctime>    /* For time(0) seed */
void Processor::Run() {
	ENTER_FUNCTION("processor", "Processor::Run()");
	srand((unsigned int)time(0));
	int t = 0;
	while(t < WORKTIME) {
		t++;
		PRINTTRACE("processor", "tick(" + std::to_string(t) + ")");
		tick(t);
	}
	system("pause");
};