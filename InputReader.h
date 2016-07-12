#ifndef INPUTREADER_H_
#define INPUTREADER_H_

#include <string>

using namespace std;

class Board;

/*
 * Interface for getting inputs
 */
class InputReader {
public:
	virtual ~InputReader() { }
	virtual Board* getBoard() = 0;
};

/*
 * Get inputs from a text file
 */
class TextInput : public InputReader {
public:
	TextInput(string fileName);
	~TextInput() { }
	Board* getBoard();
private:
	string fileName;
};


#endif /* INPUTREADER_H_ */
