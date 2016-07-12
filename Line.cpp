#include "Line.h"

#include "Board.h"

#include <iomanip>
#include <sstream>

using namespace std;

Line::Line(const Board & board, int lineIdx, const vector<int> & inputs,
		const vector<CellState*> & cells)
		: board(board), lineIdx(lineIdx), inputs(inputs), cells(cells),
		  reversed(false) {
}

void Line::reverseIndexing() {
	reversed = !reversed;
	for(unsigned inputIdx = 0; inputIdx < inputs.size() / 2; inputIdx++) {
		swap(inputs[inputIdx], inputs[inputs.size() - inputIdx - 1]);
	}
	for(unsigned cellIdx = 0; cellIdx < cells.size() / 2; cellIdx++) {
		swap(cells[cellIdx], cells[cells.size() - cellIdx - 1]);
	}
}

void Line::fixIndexing() {
	if(reversed) {
		reverseIndexing();
	}
}

string Line::description() const {
	stringstream sstream;
	if(board.isRow(index())) {
		sstream << "Row #";
	} else {
		sstream << "Column #";
	}
	sstream << board.rowColIdx(index()) << " ( inputs: ";
	for(int i = 0; i < nInputs(); i++) {
		sstream << getInput(i + 1) << " ";
	}
	sstream << ")";
	return sstream.str();
}

string Line::cellsToStr() const {
	stringstream sstream;
	for(int i = 0; i < size(); i++) {
		sstream << setw(2) << cellMarker(getCellState(i));
	}
	return sstream.str();
}
