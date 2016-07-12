#ifndef LINE_H_
#define LINE_H_

#include "CellState.h"

#include <string>
#include <vector>

class Board;

/*
 * Class that represents a single row or column.
 * Containes pointers to the cell data which is kept in the Board object.
 */
class Line {
public:
	Line(const Board & board, int lineIdx, const std::vector<int> & inputs,
			const std::vector<CellState*> & cells);
	~Line() { }

	inline void setCellState(int cellIdx, CellState state) { *cells[cellIdx] = state; }
	inline CellState getCellState(int cellIdx) const { return *cells[cellIdx]; }

	inline int nInputs() const { return inputs.size(); }
	inline int size() const { return cells.size(); }

	//fortran-style indexing: first element is inputIdx=1
	inline int getInput(int inputIdx) const { return inputs[inputIdx - 1]; }

	inline bool cellIsFull(int cellIdx) const {
		return (getCellState(cellIdx) == FULL);
	}
	inline bool cellIsEmpty(int cellIdx) const {
		return (getCellState(cellIdx) == EMPTY);
	}

	//reverses the indexing in the above cell- and input-related functions
	void reverseIndexing();
	//re-reverses if needed
	void fixIndexing();

	inline int index() const { return lineIdx; }

	std::string description() const;
	std::string cellsToStr() const;

private:
	const Board & board;
	const int lineIdx;
	std::vector<int> inputs;
	std::vector<CellState*> cells;
	bool reversed;
};

#endif /* LINE_H_ */
