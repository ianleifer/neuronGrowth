#include "processor.h"

#include "cmn_struct.h"
#include "cellStack.h"
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Processor processor;
	processor.Run();
	return 0;
}