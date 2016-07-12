#ifndef CELLSTATE_H_
#define CELLSTATE_H_

/*
 * Each cell in the board has one of the following states
 */
enum CellState {
	UNMARKED,
	FULL,
	EMPTY,
};

/*
 * Returns the char representation of the input cell state
 */ 
char cellMarker(CellState cs);

#endif
