#include "Board.h"
#include "InputReader.h"
#include "NonogramSolver.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void argError(char* argv[]) {
	cout << "Usage: " << argv[0] << " <input_file> [-i]" << endl;
	cout << "    -i    Info flag. Print 'before' & 'after' line state" \
			" for every iteration" << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	if(argc != 2 && argc != 3) {
		argError(argv);
	} else if(argc == 3 && strcmp(argv[2], "-i") != 0) {
		argError(argv);
	}
	
	InputReader* reader = new TextInput(argv[1]);
	Board* board = reader->getBoard();
	
	NonogramSolver* solver;
	if(argc == 3) {
		solver = new NonogramSolver(board, NonogramSolver::INFO);
	} else {
		solver = new NonogramSolver(board, NonogramSolver::SILENT);
	}

	if(!solver->solve()) {
		cout << "Solution is not unique and/or cannot be";
		cout <<	" found without guessing!" << endl;
		cout << "Final board state:" << endl;
	} else {
		cout << "Solution:" << endl;
	}
	cout << board->boardString();

	delete solver;
	delete board;
	delete reader;

	return (EXIT_SUCCESS);
}

