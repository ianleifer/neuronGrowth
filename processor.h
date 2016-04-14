#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "interface.h"
#include "hippocampus.h"
#include "environment.h"
#include "output.h"

class Processor {
private:
	OpenGLInterface *openGLInterface;
	Hippocampus *hippocampus;
	Environment *environment;
	Output *output;
	void tick(int t);
public:
	Processor();
	void Run();
};

#endif