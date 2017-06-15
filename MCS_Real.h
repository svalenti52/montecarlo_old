//
// Created by svalenti on 6/15/2017.
//

#ifndef MONTECARLO_MCS_REAL_H
#define MONTECARLO_MCS_REAL_H

#include <functional>
#include <iostream>
#include <random>
#include <algorithm>
#include "MonteCarloSim.h"

class MCS_Real : public MonteCarloSim {
protected:
    std::default_random_engine dre{};
    std::uniform_real_distribution<double> urd;
public:
    MCS_Real(int i_nr_trials, double lb, double ub, int i_pre_size, std::function<bool(double)> f)
            : MonteCarloSim(i_nr_trials, f) {
        std::uniform_real_distribution<double> urd_tmp(lb, ub);
        urd = std::move(urd_tmp);
        pre_size = i_pre_size;
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            collective_count = 0;
            for ( int jx = 0; jx < pre_size; ++jx )
                vector_of_values.push_back(urd(dre));
            if ( std::count_if(vector_of_values.begin(), vector_of_values.end(), local_condition_met) > 3 )
                cumulative_value += 1.0;
            vector_of_values.clear();
        }
    }
};

#endif //MONTECARLO_MCS_REAL_H
