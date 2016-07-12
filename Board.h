#ifndef BOARD_H_
#define BOARD_H_

#include "CellState.h"

#include <string>
#include <vector>

class Line;

/*
 * Keeps the current board state and input numbers
 * Each row or column is represented by a unique line index "lineIdx"
 */
class Board {
public:
	Board(const std::vector<std::vector<int> > & rowInputs,
		  const std::vector<std::vector<int> > & colInputs);
	~Board() { };

	inline int nRows() const { return cells.size(); }
	inline int nCols() const { return cells[0].size(); }

	inline CellState getCellState(int rowIdx, int colIdx) const {
		return cells[rowIdx][colIdx];
	}
	inline void setCellState(int rowIdx, int colIdx, CellState state) {
		cells[rowIdx][colIdx] = state;
	}

	inline bool isRow(int lineIdx) const { return (lineIdx < nRows()); }

	//returns rowIdx if lineIdx is a row, colIdx if lineIdx is a col
	int rowColIdx(int lineIdx) const;

	Line* getLine(int lineIdx);

	int intersectingLineIdx(const Line & line, int cellIdx) const;

	std::vector<int> getInputs(int lineIdx) const { return inputs[lineIdx]; }

	std::string boardString() const;

private:
	std::vector<std::vector<CellState> > cells; //cells[rowIdx][colIdx]
	std::vector<std::vector<int> > inputs;
	void validateInputs(int nRows, int nCols) const;
	void initBoard(int nRows, int nCols);
};

#endif /* BOARD_H_ */
