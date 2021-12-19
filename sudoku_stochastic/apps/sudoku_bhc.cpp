/**
 * sudoku_bhc.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */

#include <iostream>
#include <memory>
#include <stdexcept>

#include <boost/program_options.hpp>

#include <GenSudokuBoard.h>
#include <GenSudokuBoardBHCPopulator.h>
#include <HillClimbingAlgorithm.h>

#include "progopts.h"

namespace po = boost::program_options;
using namespace vorpal::gensudoku;
using namespace vorpal::stochastic;

int main(int argc, const char * const argv[]) {
    using solver = HillClimbingAlgorithm<SudokuBoard>;
    solver::options_type options;

    try {
        auto desc = init_options(options);
        auto done = end_options<SudokuBoardBHCPopulator, solver::options_type>(argc, argv, desc, options);
        if (done) return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
	std::string_view board = std::string_view("457682193600000007100000004200000006584716239300000008800000002700000005926835471");
	options.populator = std::make_unique<SudokuBoardBHCPopulator>(SudokuBoard(board));

    run<solver>(options);
}
