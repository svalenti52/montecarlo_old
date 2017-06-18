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
    MCS_Real(int i_nr_trials, double lb, double ub, int i_nr_random_reals, std::function<bool(std::vector<double>&)> f)
            : MonteCarloSim(i_nr_trials, f ) {
        std::uniform_real_distribution<double> urd_tmp(lb, ub);
        urd = std::move(urd_tmp);
        nr_random_real_values = i_nr_random_reals;
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            for ( int jx = 0; jx < nr_random_real_values; ++jx )
                random_real_vector.push_back(urd(dre));
            if ( real_condition_met(random_real_vector) )
                cumulative_value += 1.0;
            random_real_vector.clear();
        }
    }
};

#endif //MONTECARLO_MCS_REAL_H
