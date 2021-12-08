#ifndef SUDOKU_H
#define SUDOKU_H

#define COLUMNS 9
#define ROWS 9

#include <stdio.h>
#include <iostream>

class Sudoku {
	public:
		char board[ROWS][COLUMNS];

		Sudoku();

		bool validate();
		void print();
		void build_challenge(std::string str);

	private:
		void error(std::string msg);
		void fill_zeroes(int* list, int length);
};

#endif //end SUDOKU_H header guard
