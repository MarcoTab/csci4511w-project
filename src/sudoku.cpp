#include "sudoku.h"

// public methods
Sudoku::Sudoku() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board[i][j] = 0;
		}
	}
}

bool Sudoku::validate() {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (board[i][j] == 0) {
				return false;
			}
		}
	}

	//check all rows for unique values
	for (int i = 0; i < ROWS; i++) {

		int valueCounts[COLUMNS];
		fill_zeroes(valueCounts, COLUMNS);
		for (int j = 0; j < COLUMNS; j++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= COLUMNS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					return false;
				}
			}
		}
	}

	//check all columns for unique values
	for (int j = 0; j < COLUMNS; j++) {

		int valueCounts[ROWS];
		fill_zeroes(valueCounts, ROWS);
		for (int i = 0; i < ROWS; i++) {

			int currentValue = board[i][j];
			if (currentValue > 0 && currentValue <= ROWS) {
				valueCounts[currentValue - 1]++;
				if (valueCounts[currentValue - 1] > 1) {
					return false;
				}
			}
		}
	}

	// divide the board into 9 squares and check each for unique values
	for (int startRow = 0; startRow < ROWS; startRow += (ROWS / 3)) {
		for (int startCol = 0; startCol < COLUMNS; startCol += (COLUMNS / 3)){

			int valueCounts[(ROWS / 3) * (COLUMNS / 3)];
			fill_zeroes(valueCounts, (ROWS / 3) * (COLUMNS / 3));
			for (int i = startRow; i < startRow + (ROWS / 3); i++) {
				for (int j = startCol; j < startCol + (COLUMNS / 3); j++) {

					int currentValue = board[i][j];
					if (currentValue > 0 && currentValue <= ROWS) {
						valueCounts[currentValue - 1]++;
						if (valueCounts[currentValue - 1] > 1) {
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}

void Sudoku::print() {
	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
			fputs("┬", stdout);
		}
		else if (k == 0) {
			fputs("┌", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┐", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
	for (int i = 0; i < ROWS; i++) {
		// print horizontal board lines
		if (i != 0 && i % 3 == 0) {
			fputs("├", stdout);
			for (int k = 0; k < COLUMNS * 2 + 5; k++) {
				if ((k != 0 && k == (COLUMNS / 3) * 2 + 1) || (k == (COLUMNS / 3) * 4 + 3)) {
					fputs("┼", stdout);
				}
				else {
					fputs("─", stdout);
				}
			}
			fputs("┤", stdout);
			putchar('\n');
		}
		fputs("│ ", stdout);
		for (int j = 0; j < COLUMNS; j++) {
			// print vertical board lines
			if (j != 0 && j % 3 == 0) {
				fputs("│ ", stdout);
			}

			if (board[i][j] == 0) {
				putchar(' ');
			}
			else {
				printf("%d", board[i][j]);
			}

			if (j != COLUMNS - 1) {
				putchar(' ');
			}
		}
		fputs(" │", stdout);
		putchar('\n');
	}
	for (int k = 0; k < COLUMNS * 2 + 7; k++) {
		if ((k != 0 && k == (COLUMNS / 3) * 2 + 2) || (k == (COLUMNS / 3) * 4 + 4)) {
			fputs("┴", stdout);
		}
		else if (k == 0) {
			fputs("└", stdout);
		}
		else if (k == COLUMNS * 2 + 6) {
			fputs("┘", stdout);
		}
		else {
			fputs("─", stdout);
		}
	}
	putchar('\n');
}

void Sudoku::board_from_string(std::string str) {

	int row = 0;
	int col = 0;

	for (char const &c : str) {

		int num = -1;
		if (c >= '1' && c <= '9') {
			num = c - '1' + 1;
		}
		else if (c == '.') {
			num = 0;
		}
		else {
			std::cerr << "unexpected character '" << c << "'" << std::endl;
			return;
		}

		board[row][col] = num;

		col++;
		if (col > 8) {
			col = 0;
			row++;
		}
		if (row > 8) {
			return;
		}
	}
}

void Sudoku::to_char_array(char *data) {
	int dataIndex = 0;
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			data[dataIndex++] = ('0' + board[row][col]);
		}
	}
	data[dataIndex] = '\0';
}

void Sudoku::from_char_array(char *data) {
	int dataIndex = 0;
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLUMNS; col++) {
			board[row][col] = (data[dataIndex++] - '0');
		}
	}
}

void Sudoku::backtrack_solve() {
	backtrack_helper(0,0);
}

// private methods
void Sudoku::error(std::string msg) {
	std::cerr << msg << std::endl;
	exit(1);
}

void Sudoku::fill_zeroes(int* list, int length) {

	for (int i = 0; i < length; i++) {
		list[i] = 0;
	}
}

// return true if should backtrack
bool Sudoku::backtrack_helper(char row, char col) {

	if (row >= 9 || col >= 9) {
		error("row or column out of range");
		return true;
	}

	// if the number is already filled in
	if (board[row][col] != 0) {
		// overflow check
		if (col < (COLUMNS - 1)) {
			return backtrack_helper(row, col+1);
		}
		else if (row < (ROWS - 1)) {
			return backtrack_helper(row + 1, 0);
		}
		else {
			return true;
		}
	}
	else {
		for (int num = 1; num <= ROWS; num++) {
			if (pointIsValid(row, col, num)) {
				board[row][col] = num;

				if (col < 8) {
					if (backtrack_helper(row, col+1)) {
						return true;
					}
					else {
						board[row][col] = 0;
					}
				}
				else if (row < 8) {
					if (backtrack_helper(row+1, 0)) {
						return true;
					}
					else {
						board[row][col] = 0;
					}
				}
				else {
					return true;
				}
			}
		}
	}
	return false;
}

bool Sudoku::pointIsValid(int row, int col, char value) {

	for (int i = 0; i < ROWS; i++) {
		if (board[row][i] == value) {
			return false;
		}
		if (board[i][col] == value) {
			return false;
		}
		if (board[row - (row % 3) + (i / 3)][col - (col % 3) + (i % 3)] == value) {
			return false;
		}
	}
	return true;
}
