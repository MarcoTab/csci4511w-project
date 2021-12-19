#ifndef SIM_ANNEALING_H
#define SIM_ANNEALING_H

#include <string>
#include <iostream>

class SimAnnealing {
    int board[9][9];
    int givens[9][9];
    int steps = 1000000;
    int T;

    void init_randomly();
    double accept();


    public:
        SimAnnealing(std::string str);


        void solve();

        void print();
        bool validate();
        
};

#endif