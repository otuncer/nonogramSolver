#include "LineQueue.h"

#include "Board.h"

using namespace std;

LineQueue::LineQueue(const Board & board) : board(board) {
	scores = vector<int>(board.nRows() + board.nCols());
	//initialize scores using the largest input in them
	for(unsigned lineIdx = 0; lineIdx < scores.size(); lineIdx++) {
		vector<int> inputs = board.getInputs(lineIdx);
		int maxVal = 0;
		for(unsigned inIdx = 0; inIdx < inputs.size(); inIdx++) {
			maxVal = inputs[inIdx] > maxVal ? inputs[inIdx] : maxVal;
		}
		scores[lineIdx] = maxVal;
	}
}

int LineQueue::next() {
	int maxScore = 0;
	int nextLineIdx = -1;
	for(unsigned lineIdx = 0; lineIdx < scores.size(); lineIdx++) {
		if(scores[lineIdx] > maxScore) {
			maxScore = scores[lineIdx];
			nextLineIdx = lineIdx;
		}
	}
	if(nextLineIdx >= 0) {
		scores[nextLineIdx] = 0;
	}
	return nextLineIdx;
}

void LineQueue::modifiedLine(const Line & line, int cellIdx) {
	scores[board.intersectingLineIdx(line, cellIdx)]++;
}
