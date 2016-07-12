#include "Fail.h"

#include <cstdlib>
#include <execinfo.h>
#include <iostream>

void Fail::terminate(std::string message) {
	std::cerr << message << "\n";
	exit(EXIT_FAILURE);
}

void Fail::fatal(std::string msg) {
	std::cerr << "-----------\n";
	std::cerr << "Fatal error: " << msg << "\n";
	std::cerr << "-----------\n";
	std::cerr << "Backtrace:\n";

	void* tracePtrs[100];
	int count = backtrace(tracePtrs, 100);
	char** funcNames = backtrace_symbols(tracePtrs, count);
	for(int i = 0; i < count; i++)
		std::cerr << funcNames[i] << "\n";
	free(funcNames);
	std::cerr << "-----------\n";

	exit(EXIT_FAILURE);
}

