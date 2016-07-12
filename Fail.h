#ifndef FAIL_H_
#define FAIL_H_

#include <string>

/*
 * Static functions to call upon failure
 */
class Fail {
public:
	// Prints input message and terminates the program
	static void terminate(std::string message);
	// Also prints backtrace
	static void fatal(std::string message);
};

#endif /* FAIL_H_ */
