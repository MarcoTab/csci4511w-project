#include "sim_annealing.h"

SimAnnealing::SimAnnealing(std::string str) {
    int row = 0;
	int col = 0;

	for (char const &c : str) {

		int num = -1;
		if (c >= '1' && c <= '9') {
			num = c - '1' + 1;
		}
		else if (c == '0') {
			num = 0;
		}
		else {
			std::cerr << "unexpected character '" << c << "'" << std::endl;
			return;
		}

		givens[row][col] = num;

		col++;
		if (col > 8) {
			col = 0;
			row++;
		}
		if (row > 8) {
            init_randomly();
			return;
		}
	}


}

void SimAnnealing::init_randomly() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            
        }
    }
}

void SimAnnealing::solve() {

}


double SimAnnealing::accept() {
    
}

void SimAnnealing::print() {

}
bool SimAnnealing::validate() {

}