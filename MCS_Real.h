/**
 * \file MCS_Real.h
 * \date 15-Jun-2017.
 * \brief Class for Uniform Real Distribution.
 */

#ifndef MONTECARLO_MCS_REAL_H
#define MONTECARLO_MCS_REAL_H

#include <functional>
#include <iostream>
#include <random>
#include "MonteCarloSim.h"

class MCS_Real : public MonteCarloSim {
protected:
    std::default_random_engine dre{};
    std::uniform_real_distribution<double> urd;
public:
    MCS_Real(int i_nr_trials, double lb, double ub, int i_pre_size, std::function<bool(std::vector<double>&)> f)
            : MonteCarloSim(i_nr_trials, f ) {
        std::uniform_real_distribution<double> urd_tmp(lb, ub);
        urd = std::move(urd_tmp);
        pre_size = i_pre_size;
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            collective_count = 0;
            for ( int jx = 0; jx < pre_size; ++jx )
                vector_of_values.push_back(urd(dre));
            if ( condition_met(vector_of_values) )
                cumulative_value += 1.0;
            vector_of_values.clear();
        }
    }
};

#endif //MONTECARLO_MCS_REAL_H
