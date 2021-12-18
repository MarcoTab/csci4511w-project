#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "sudoku.h"
#include "sudoku_solver.h"

enum algs {
	DLX,
	BACKTRACK
};

int main(int argc, char **argv) {

	if (argc < 2) {
		std::cerr << "usage: " << argv[0] << " <filename>" << std::endl;
		exit(1);
	}

	// algorithm from filename
	enum algs alg;
	std::string fname = std::string(argv[0]);
	if (fname.find("backtrack") != std::string::npos) {
		alg = BACKTRACK;
	}
	else if (fname.find("dlx") != std::string::npos) {
		alg = DLX;
	}
	else {
		std::cerr << "invalid algorithm selected" << std::endl;
		exit(EXIT_FAILURE);
	}

	Sudoku s;
	std::ifstream infile(argv[1]);
	std::string line;
	std::vector<clock_t> runTimes;
	clock_t startTime, endTime;

	// read lines
	while (std::getline(infile, line)) {
		// run appropriate function
		char data[82];
		s.board_from_string(line);
		s.to_char_array(data);
		sudoku_GJK::Sudoku<3> sdku(data);
		
		switch (alg) {
			case DLX:
				startTime = clock();
				sdku.solve();
				endTime = clock();
				//s.from_char_array(data);
				//s.print();
				sdku.display_ASCII();
				runTimes.push_back(endTime - startTime);
				break;

			case BACKTRACK:
				startTime = clock();
				s.backtrack_solve();
				endTime = clock();
				runTimes.push_back(endTime - startTime);
				s.print();
				if (!s.validate()) {
					std::cerr << "failed to validate" << std::endl;
					exit(EXIT_FAILURE);
				}
				break;

			default:
				std::cerr << "invalid algorithm selected" << std::endl;
				exit(EXIT_FAILURE);
		}
	}

	// save times to file
	std::ofstream csv;
	std::string datafname;
	switch (alg) {
		case DLX:
			datafname = std::string("output/data-dlx.csv");
			break;
		case BACKTRACK:
			datafname = std::string("output/data-backtrack.csv");
			break;
	}

	csv.open(datafname, std::ios_base::app);
	line = "";
	line.append(argv[0]);
	line.append(",");
	line.append(argv[1]);
	line.append(",");
	for (time_t t : runTimes) {
		double time = (double) t / (double) CLOCKS_PER_SEC;
		std::string tmp_str;
		tmp_str = std::to_string(time);
		tmp_str.append(",");
		line.append(tmp_str);
	}
	csv << line << std::endl;
	csv.close();

	return 0;
}
