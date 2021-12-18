#ifndef SUDOKU_H
#define SUDOKU_H

#define COLUMNS 9
#define ROWS 9

#include <stdio.h>
#include <iostream>
#include "dlx.h"

class Sudoku {
	public:
		char board[ROWS][COLUMNS];

		Sudoku();

		bool validate();
		void print();
		void board_from_string(std::string str);

		// for dlx
		void to_char_array(char *data);
		void from_char_array(char *data);

		// solvers
		void backtrack_solve();

	private:
		void error(std::string msg);
		void fill_zeroes(int* list, int length);
		bool backtrack_helper(char row, char col);
		bool pointIsValid(int row, int col, char value);
};
#endif //end SUDOKU_H header guard
