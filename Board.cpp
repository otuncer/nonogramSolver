#include "Board.h"

#include "Fail.h"
#include "Line.h"

#include <iomanip>
#include <sstream>

using namespace std;

Board::Board(const vector<vector<int> > & rowInputs,
		  	 const vector<vector<int> > & colInputs) {
	int nRows = rowInputs.size();
	int nCols = colInputs.size();
	inputs = vector<vector<int> >(nRows + nCols);
	int inIdx = 0;
	for(int rowIdx = 0; rowIdx < nRows; rowIdx++) {
		inputs[inIdx++] = rowInputs[rowIdx];
	}
	for(int colIdx = 0; colIdx < nCols; colIdx++) {
		inputs[inIdx++] = colInputs[colIdx];
	}
	validateInputs(nRows, nCols);
	initBoard(nRows, nCols);
}

void Board::validateInputs(int nRows, int nCols) const {
	if(nRows == 0 || nCols == 0) {
		Fail::terminate("Row or column inputs cannot be empty.");
	}
	for(unsigned inIdx = 0; inIdx < inputs.size(); inIdx++) {
		if(inputs[inIdx].size() == 0) {
			Fail::terminate("Row or column inputs cannot be empty.");
		}
		for(unsigned numIdx = 0; numIdx < inputs[inIdx].size(); numIdx++) {
			if(inputs[inIdx][numIdx] < 0) {
				Fail::terminate("Input numbers must be non-negative.");
			}
		}
	}
}

void Board::initBoard(int nRows, int nCols) {
	cells = vector<vector<CellState> >(nRows);
	for(int rowIdx = 0; rowIdx < nRows; rowIdx++) {
		cells[rowIdx] = vector<CellState>(nCols, UNMARKED);
	}
}

string Board::boardString() const {
	stringstream retStr;
	for(int rowIdx = 0; rowIdx < nRows(); rowIdx++) {
		retStr << std::setw(2) << rowIdx + 1 << ": ";
		for(int colIdx = 0; colIdx < nCols(); colIdx++) {
			if(colIdx % 5 == 0 && colIdx != 0) {
				retStr << "|";
			}
			retStr << cellMarker(getCellState(rowIdx, colIdx));
		}
		retStr << "\n";
	}
	return retStr.str();
}

Line* Board::getLine(int lineIdx) {
	if(isRow(lineIdx)) {
		vector<CellState*> cellAddrs(nCols());
		for(int colIdx = 0; colIdx < nCols(); colIdx++) {
			cellAddrs[colIdx] = &cells[rowColIdx(lineIdx)][colIdx];
		}
		return new Line(*this, lineIdx, inputs[lineIdx], cellAddrs);
	} else {
		vector<CellState*> cellAddrs(nRows());
		for(int rowIdx = 0; rowIdx < nRows(); rowIdx++) {
			cellAddrs[rowIdx] = &cells[rowIdx][rowColIdx(lineIdx)];
		}
		return new Line(*this, lineIdx, inputs[lineIdx], cellAddrs);
	}
}

int Board::intersectingLineIdx(const Line & line, int cellIdx) const {
	if(isRow(line.index())) {
		return nRows() + cellIdx;
	} else {
		return cellIdx;
	}
}

int Board::rowColIdx(int lineIdx) const {
	if(isRow(lineIdx)) {
		return lineIdx;
	} else {
		return lineIdx - nRows();
	}
}
