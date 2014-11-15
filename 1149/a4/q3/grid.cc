#include "grid.h"

// Cell **theGrid;  // The actual n x n grid. 
// int gridSize;    // Size of the grid (n)
// TextDisplay *td; // The text display.

void Grid::clearGrid(){ // Frees the theGrid field.
	if (NULL != theGrid) {
		for (int i = 0; i < gridSize; i++) {
			delete[] theGrid[i];
		}
		delete[] theGrid;
		theGrid = NULL;
	}
}

Grid::Grid() { // Default constructor
	// set default values to prevent wacky "unset" errors
	theGrid = NULL;
	gridSize = 0;
	td = NULL;
}

Grid::~Grid() {
	// make sure that the grid memory is deallocated
	clearGrid();

	// make sure there is no more TextDisplay
	if (NULL !=  td) {
		delete td;
	}
}

bool Grid::isWon() { // check the textdisplay to see if the grid is filled
	return td->isFilled();
}

void Grid::init(int n) { // Sets up an n x n grid.  Clears old grid, if necessary.
	clearGrid(); // Doesn't do anything if theGrid already = NULL
	gridSize = n; // set gridSize

	// initialize the new TextDisplay
	if (NULL !=  td) {
		delete td;
	}
	td = new TextDisplay(n);

	// allocate memory for theGrid
	theGrid = new Cell*[n];
	for(unsigned i = 0; i < n; ++i) {
		theGrid[i] = new Cell[n];
	}

	// create new cells and initialize basic vars for theGrid
	for (int i = 0; i < n; ++i) {
		for(unsigned j = 0; j < n; ++j) {
			// set basics
			theGrid[i][j].setCoords(i, j);
			theGrid[i][j].setDisplay(td);
		}
	}

	// sets neighbours for all cells in theGrid
	for (unsigned i = 0; i < n; ++i) {
		for(unsigned j = 0; j < n; ++j) {
			// set neighbors
			if (0 != i) {
				theGrid[i][j].addNeighbour(&theGrid[i-1][j]);
			}
			if (0 != j) {
				theGrid[i][j].addNeighbour(&theGrid[i][j-1]);
			}
			if (n-1 != i) {
				theGrid[i][j].addNeighbour(&theGrid[i+1][j]);
			}
			if (n-1 != j) {
				theGrid[i][j].addNeighbour(&theGrid[i][j+1]);
			}
		}
	}
}

void Grid::change(const int & state) { // Notify Cell (0,0) of the change to new state: state 
	theGrid[0][0].notify(state);
}

void Grid::init(int r, int c, int state) { //set the state for r,c to state
	theGrid[r][c].setState(state);
}

std::ostream &operator<<(std::ostream &out, const Grid &g) {
	out << *(g.td);
	return out;
}

