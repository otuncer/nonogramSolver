#include "InputReader.h"

#include "Board.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Fail.h"

TextInput::TextInput(string fileName) {
	this->fileName = fileName;
}

Board* TextInput::getBoard() {
	ifstream input(fileName.c_str());
	if(!input.good())
		Fail::terminate("Cannot read input file: " + fileName);
	vector<vector<int> > rowCodes;
	vector<vector<int> > colCodes;
	vector<int> tempVec;

	bool colsFinished = false;

	string line;
	int num;
	while(getline(input, line)) {
		stringstream ss(line);
		if(ss.str().empty()) {
			colsFinished = true;
		} else if(colsFinished) {
			rowCodes.push_back(vector<int>());
			while(ss >> num) {
				rowCodes.back().push_back(num);
			}
		} else {
			colCodes.push_back(vector<int>());
			while(ss >> num) {
				colCodes.back().push_back(num);
			}
		}
	}

	Board* board = new Board(rowCodes, colCodes);

	return board;
}



