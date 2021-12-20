/**
 * sudoku_sa.cpp
 *
 * By Sebastian Raaphorst, 2018.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <memory>
#include <stdexcept>

#include <boost/program_options.hpp>

#include <GenSudokuBoard.h>
#include <GenSudokuBoardAscenderPopulator.h>
#include <SimulatedAnnealingAlgorithm.h>

#include "progopts.h"

namespace po = boost::program_options;
using namespace vorpal::gensudoku;
using namespace vorpal::stochastic;

std::string to_zeros(std::string str) {
    std::string ret = "";
    for (const char& c : str) {
        if (c == '.') {
            ret += '0';
        } else {
            ret += c;
        }
    }
    return ret;
}

int main(int argc, const char * const argv[]) {
    using solver = SimulatedAnnealingAlgorithm<SudokuBoard>;
    solver::options_type options;

    char * fake = "./sudoku_sa";
    argc = 1;
    argv = &fake;

    try {
        
        auto desc = init_options(options);
        desc->add_options()
                ("initial-temperature,t", po::value<double>()->default_value(10000), "initial temperature")
                ("alpha,a", po::value<double>()->default_value(0.99), "alpha (cooling rate)");
        auto done = end_options<SudokuBoardAscenderPopulator, solver::options_type>(argc, argv, desc, options,
        [](po::variables_map &vm, solver::options_type &options) {
            options.initial_temperature = vm["initial-temperature"].as<double>();
            options.alpha               = vm["alpha"].as<double>();
        });
        if (done) return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    std::ifstream infile;
    infile.open(argv[1]);
    std::string line;
    std::vector<clock_t> runTimes;
    clock_t startTime, endTime;

    while (std::getline(infile, line)) {
        std::cerr << line << "\n";
        std::string_view board = std::string_view(to_zeros(line));
        options.populator = std::make_unique<SudokuBoardAscenderPopulator>(SudokuBoard(board));

        startTime = clock();
        run<solver>(options);
        endTime = clock();

        runTimes.push_back(endTime - startTime);

    }

	infile.close();
}


