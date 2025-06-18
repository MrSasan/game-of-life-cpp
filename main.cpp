/*
	Titel: Informatik Labor 6-7 - Conway's Game of Life
	Beschreibung: A C++ implementation of Conway's Game of Life.
	Name: Sasan Karim / Meliksah Unal / Daniel Ochs
	Datum: 16.06.2025
*/

#include <iostream>
#include <windows.h>

using namespace std;
// Globale Variablen
int sleepTime = 100; // Time in miliseconds
int gridRows = 0;
int gridCols = 0;
char grid[999][999];
char aliveCell = '0';
char deadCell = '.';

void getConsoleSize(int& row, int& cols) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {                                
		row = csbi.srWindow.Bottom - csbi.srWindow.Top - 3;
		cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	else {
		// Fallback value if unable to retrieve console size.           
		row = 30;
		cols = 50;
	}
}

void clearInvalidInput() {
	cin.clear(); // Clear the error flag on cin
	cin.ignore(1000, '\n'); // Discard invalid input
}

void initializeGrid(int rows, int cols) {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			grid[x][y] = deadCell; // Initialize each cell to dead
		}
	}
}

void printGrid(int maxRows, int maxCols) {
	for (int x = 0; x < maxRows; x++) {
		for (int y = 0; y < maxCols; y++) {
			cout << grid[x][y]; // Print each cell in the grid
		}
		cout << endl; // New line after each row
	}
}

void runSimulation(int MaxRows, int MaxCols) {
	char tempGrid[999][999]; // Temporary grid to store the next state
	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 }; // Directions for x-axis
	const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 }; // Directions for y-axis
	for (int x = 0; x < MaxRows; x++) {
		for (int y = 0; y < MaxCols; y++) {
			int tempSum = 0;
			for (int d = 0; d < 8; d++) {
				int newX = x + dx[d]; // Calculate new x position
				int newY = y + dy[d]; // Calculate new y position
				if (newX >= 0 && newX < MaxRows && newY >= 0 && newY < MaxCols) { // Check bounds
					if (grid[newX][newY] == aliveCell) {
						tempSum++; // Count alive neighbors
					}
				}
			}
			if (grid[x][y] == aliveCell) {
				if (tempSum < 2 || tempSum > 3) {
					tempGrid[x][y] = deadCell; // Cell dies due to underpopulation or overpopulation
				}
				else {
					tempGrid[x][y] = aliveCell; // Cell remains alive
				}
			}
			else {
				if (tempSum == 3) {
					tempGrid[x][y] = aliveCell; // Cell becomes alive due to reproduction
				}
				else {
					tempGrid[x][y] = deadCell; // Cell remains dead
				}
			}
		}
	}
	for (int x = 0; x < MaxRows; x++) { // Copy the temporary grid back to the main grid
		for (int y = 0; y < MaxCols; y++) {
			grid[x][y] = tempGrid[x][y]; // Update the cell state
		}
	}
}


int main() {
	int cellX, cellY;
	int gridRows = 0; // Number of rows in the grid
	int gridCols = 0; // Number of columns in the grid

	bool isSelecting = true; // is the user selecting cells?
	bool isRunning = true; // is the simulation running?
	char menuSelect;
	cout << "Welcome to Conway's Game of Life!" << endl
		<< "Please resize your console window to the desired size, as this will be used to generate the grid for the game." << endl
		<< "When you are ready, type 'R' or type 'Q' to quit the game." << endl;
	cin >> menuSelect;
	if (menuSelect == 'R' || menuSelect == 'r') {
		getConsoleSize(gridRows, gridCols);
		system("cls"); // Clear the console screen for a fresh start
		initializeGrid(gridRows, gridCols);	
		cout << "rows: " << gridRows << ", cols: " << gridCols << endl; //debug
		printGrid(gridRows, gridCols);
	while(isSelecting)	{
		cout << "Please enter the coordinates of a cell to toggle its state (x y), or type 'c' to continue. ";
		if (cin.get() != 'c') {
			cin >> cellX;
			if (cin.fail()) {
				clearInvalidInput();
				break; // Exit the loop if input is invalid
			}
			cin >> cellY;
			if (cin.fail()) {
				clearInvalidInput();
				break; // Exit the loop if input is invalid
			}
			if (cellX < 0 || cellX >= gridRows || cellY < 0 || cellY >= gridCols) {
				cout << "Invalid coordinates. Please try again." << endl;
				continue; // Skip to the next iteration if coordinates are out of bounds
			}
			grid[cellX][cellY] = (grid[cellX][cellY] == aliveCell) ? deadCell : aliveCell; // Toggle cell state
			system("cls"); // Clear the console screen for a fresh display
			printGrid(gridRows, gridCols);
		}
	}
		while(isRunning) {
			system("cls"); // Clear the console screen for a fresh display
			runSimulation(gridRows, gridCols);
			printGrid(gridRows, gridCols); // Print the updated grid after each simulation step
			Sleep(sleepTime);
		}
	}
	else if (menuSelect == 'Q' || menuSelect == 'q') {
		cout << "Exiting the game. Goodbye!" << endl;
		return 0;
	}
	else {
		cout << "Invalid selection. Please restart the program." << endl;
		return 1;
	}
}
