#include "NonogramSolver.h"

#include "Board.h"
#include "Fail.h"
#include "Line.h"
#include "LineQueue.h"

#include <iostream>

using namespace std;

NonogramSolver::NonogramSolver(Board* board, LogLevel logLevel)
		: board(board), logLevel(logLevel) {
	lineQueue = new LineQueue(*board);
}

NonogramSolver::~NonogramSolver() {
	delete lineQueue;
}

bool NonogramSolver::solve() {
	int nextLineIdx;
	while((nextLineIdx = lineQueue->next()) >= 0) {
		Line *nextLine = board->getLine(nextLineIdx);
		if(logLevel >= INFO) {
			cout << endl;
			cout << "Processing line: " << nextLine->description() << endl;
			cout << "Old state: " << nextLine->cellsToStr() << endl;
		}
		processLine(nextLine);
		if(logLevel >= INFO) {
			cout << "New state: " << nextLine->cellsToStr() << endl;
		}
		delete nextLine;
	}
	//TODO Start guessing if a unique solution is not found
	return solutionIsFound();
}

bool NonogramSolver::solutionIsFound() const {
	for(int rowIdx = 0; rowIdx < board->nRows(); rowIdx++) {
		Line* row = board->getLine(rowIdx);
		for(int colIdx = 0; colIdx < row->size(); colIdx++) {
			if(row->getCellState(colIdx) == UNMARKED) {
				delete row;
				return false;
			}
		}
		delete row;
	}
	return true;
}

void NonogramSolver::processLine(Line* line) {
	//align blocks of filled cells from both ends
	vector<int> beginAligned = align(line, false);
	vector<int> endAligned   = align(line, true);

	//mark cells that are marked with the same ID in both vectors
	for(int pos = 0; pos < line->size(); pos++) {
		if(beginAligned[pos] == endAligned[pos] &&
				line->getCellState(pos) == UNMARKED) {
			if(beginAligned[pos] <= 0) {
				line->setCellState(pos, EMPTY);
			} else {
				line->setCellState(pos, FULL);
			}
			lineQueue->modifiedLine(*line, pos);
		}
	}

	//second pass: Find and remove infeasible cell states
	removeInfeasibleSolutions(line, beginAligned, endAligned);
}

vector<int> NonogramSolver::align(Line *line, bool alignToEnd) {
	//reverse line indexing if we are aligning to the end
	if(alignToEnd) {
		line->reverseIndexing();
	}

	vector<int> aligned(line->size());
	recursiveAlign(*line, &aligned);
	if(aligned.empty()) {
		Fail::terminate("There is no feasible solution!");
	}

	//fix indexing back to original
	line->fixIndexing();
	if(alignToEnd) {
		for(unsigned i = 0; i < aligned.size() / 2; i++) {
			swap(aligned[i], aligned[aligned.size() - i - 1]);
		}
		for(unsigned i = 0; i < aligned.size(); i++) {
			if(aligned[i] <= 0) {
				aligned[i] = -(line->nInputs() + aligned[i]);
			} else {
				aligned[i] = line->nInputs() + 1 - aligned[i];
			}
		}
	}
	return aligned;
}

bool NonogramSolver::recursiveAlign(const Line & line, vector<int>* aligned,
		int pos, int blockIdx) {
	if(blockIdx > line.nInputs()) {
		//All blocks are placed. Good to go if there are no remaining full cells.
		if(noFullRemains(line, pos)) {
			//Fill remaining cells with "next empty block" marker
			for(int cellIdx = pos; cellIdx < line.size(); cellIdx++) {
				aligned->at(cellIdx) = - blockIdx + 1;
			}
		} else { //The solution didn't work, parent recursion must be wrong
			return false;
		}
	} else {
		int blockSize = line.getInput(blockIdx);
		int startPos = pos;	//current block starts here
		int nextStartPos;	//next block starts here
		while(startPos < line.size()) {
			startPos = firstFeasibleStart(line, startPos, blockSize);
			if(startPos < 0) {
				return false; //Cannot start from here
			}
			nextStartPos = startPos + blockSize + 1;
			if(recursiveAlign(line, aligned, nextStartPos, blockIdx + 1)) {
				break; //Current startPos worked. Stop searching.
			}
			if(line.cellIsFull(startPos)) {
				return false; //Cannot skip cell. Parent recursion must be wrong.
			}
			startPos++;
		}
		if(startPos >= line.size()) {
			return false;
		}
		//fill before the current block
		while(pos < startPos) {
			aligned->at(pos++) = - blockIdx + 1;
		}
		//fill the current block
		for(int it = 0; it < blockSize; it++) {
			aligned->at(pos++) = blockIdx;
		}
		//fill after
		if(pos < line.size()) {
			aligned->at(pos) = -blockIdx;
		}
	}
	return true;
}

bool NonogramSolver::noFullRemains(const Line & line, int startIdx) const {
	for(int it = startIdx; it < line.size(); it++) {
		if(line.cellIsFull(it)) {
			return false;
		}
	}
	return true;
}

int NonogramSolver::firstFeasibleStart(const Line & line, int pos,
		int blockSize) const {
	bool encounteredFullCell = false;
	int cellsNeeded = blockSize;
	while(cellsNeeded > 0 && pos < line.size()) {
		cellsNeeded--;
		if(line.getCellState(pos) == EMPTY) {
			if(!encounteredFullCell) {
				cellsNeeded = blockSize;
			} else {
				return -1;
			}
		} else if(line.getCellState(pos) == FULL) {
			encounteredFullCell = true;
		}
		pos++;
	}
	if(cellsNeeded > 0) {
		return -1;
	}
	//we have enough non-empty cells. Following cell shouldn't be full.
	while(pos != line.size() && line.getCellState(pos) == FULL) {
		if(line.getCellState(pos - blockSize) != FULL) {
			pos++;
		} else {
			return -1;
		}
	}
	return (pos - blockSize);
}

void NonogramSolver::removeInfeasibleSolutions(Line *line,
		const vector<int> & leftAligned, const vector<int> & rightAligned) {
	vector<int> dummyVector(line->size());
	for(int cellIdx = 0; cellIdx < line->size(); cellIdx++) {
		if(line->getCellState(cellIdx) == UNMARKED &&
				((leftAligned[cellIdx] < 0 && rightAligned[cellIdx] < 0) ||
				 (leftAligned[cellIdx] > 0 && rightAligned[cellIdx] > 0))) {
			//check whether the opposite solution is feasible
			if(leftAligned[cellIdx] < 0) {
				line->setCellState(cellIdx, FULL);
			} else {
				line->setCellState(cellIdx, EMPTY);
			}
			if(recursiveAlign(*line, &dummyVector)) {
				//Opposite is feasible, revert cell to state
				line->setCellState(cellIdx, UNMARKED);
			} else {
				//Opposite is not feasible. Mark cell
				lineQueue->modifiedLine(*line, cellIdx);
				if(leftAligned[cellIdx] < 0) {
					line->setCellState(cellIdx, EMPTY);
				} else {
					line->setCellState(cellIdx, FULL);
				}
			}
		}
	}
}
