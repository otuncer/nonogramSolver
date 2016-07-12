#include "CellState.h"

#include "Fail.h"

char cellMarker(CellState cs) {
	switch(cs) {
	case UNMARKED:	return '?';
	case FULL: 		return '@';
	case EMPTY: 	return '_';
	default:
		Fail::fatal("Unknown cell state");
		return ' ';
	}
}
