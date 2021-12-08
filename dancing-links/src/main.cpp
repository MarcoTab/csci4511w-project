#include <iostream>
#include <fstream>
#include "sudoku.h"

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cerr << "usage: ./dlx <filename>" << std::endl;
		exit(1);
	}

	Sudoku s;
	std::ifstream infile(argv[1]);
	std::string line;

	while (std::getline(infile, line)) {
		s.build_challenge(line);
		s.print();
	}

	//s.build_challenge("..15.........7.8...........5......167...2...........3....1.6..347....2...8.......");

	//s.print();

	/*
	if (s.validate()) {
		std::cout << "Board is valid" << std::endl;
	}
	else {
		std::cout << "Board is not valid" << std::endl;
	}
	*/

	return 0;
}
