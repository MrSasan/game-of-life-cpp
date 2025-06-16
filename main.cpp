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
int gridRows = 0;
int gridCols = 0;
int grid[999][999];

void getConsoleSize(int& row, int& cols) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {                                
		row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	else {
		// Fallback value if unable to retrieve console size.
		row = 30;
		cols = 50;
	}
}



int main() {
	char menuSelect;
	cout << "Welcome to Conway's Game of Life!" << endl
		<< "Please resize your console window to the desired size, as this will be used to generate the grid for the game." << endl
		<< "When you are ready, type 'R' or type 'Q' to quit the game." << endl;
	cin >> menuSelect;
	if (menuSelect == 'R' || menuSelect == 'r') {
		getConsoleSize(gridRows, gridCols);
		cout << "rows: " << gridRows << ", cols: " << gridCols << endl; //debug
		// TODO
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
