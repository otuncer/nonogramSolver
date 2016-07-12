#ifndef LINEQUEUE_H_
#define LINEQUEUE_H_

#include <vector>

class Board;
class Line;

/*
 * Simple priority queue that selects the next line to process
 * Initially, the lines with larger input numbers are prioritized
 * Then, the lines with higher number of modified cells are prioritized
 */
class LineQueue {
public:
	LineQueue(const Board & board);
	~LineQueue() { }

	//returns the index of the next line to process
	//returns -1 if there is no line to process
	int next();

	//increases the score of the intersecting line by 1
	void modifiedLine(const Line & line, int cellIdx);
private:
	const Board & board;
	std::vector<int> scores;
};

#endif /* LINEQUEUE_H_ */
