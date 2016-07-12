#ifndef NONOGRAMSOLVER_H_
#define NONOGRAMSOLVER_H_

class Board;
class Line;

#include "LineQueue.h"

#include <vector>

class NonogramSolver {
public:
	enum LogLevel {
		SILENT,	//Only prints the solution
		INFO	//Also prints the lines that are being processed
	};

	NonogramSolver(Board* board, LogLevel logLevel=SILENT);
	~NonogramSolver();
	bool solve();

private:
	Board *board;
	LineQueue *lineQueue;
	LogLevel logLevel;

	bool solutionIsFound() const;

	void processLine(Line *line);

	/*
	 * Returns a vector that contains the indices of input numbers when all
	 * inputs are aligned to the beginning or to the end of the line.
	 * In the returned vector, <1, 2, 3, ...> are the cells filled with given
	 * block indices, whereas <0, -1, -2, -3, ...> are the empty cells.
	 * line: The line being processed
	 * alignToEnd: Push all blocks to the beginning or to the end of the line
	 */
	std::vector<int> align(Line *line, bool alignToEnd);

	/*
	 * This function does the actual job of align(). Each recursion places one
	 * block.
	 * pos: the position (index) of the cell to start looking at
	 * blockIdx: the current block index we are placing
	 * aligned: filled & empty block indices
	 * returns whether there is a feasible solution for the given input
	 */
	bool recursiveAlign(const Line & line, std::vector<int>* aligned,
			int pos = 0, int blockIdx = 1);

	/* 
	 * Returns true if there is no full cell after the startIdx'th cell
	 */
	bool noFullRemains(const Line & line, int startIdx) const;

	/*
	 * Returns the first feasible starting cell for a single block.
	 * pos: the index of the cell to start looking at
	 */
	int firstFeasibleStart(const Line & line, int pos, int blockSize) const;

	/*
	 * Based on left- and right-aligned solutions, finds and removes
	 * infeasible cell states for currently "unknown" cells.
	 */  
	void removeInfeasibleSolutions(Line *line,
			const std::vector<int> & leftAligned,
			const std::vector<int> & rightAligned);
};

#endif /* NONOGRAMSOLVER_H_ */
