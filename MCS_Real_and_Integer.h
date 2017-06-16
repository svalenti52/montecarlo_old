/**
 * \file MCS_Real_and_Integer.cpp
 * \date 16-Jun-2017
 *
 */

#ifndef MONTECARLO_MCS_REAL_AND_INTEGER_H
#define MONTECARLO_MCS_REAL_AND_INTEGER_H

#include <val/montecarlo/MonteCarloSim.h>
#include <random>

class MCS_Real_and_Integer : public MonteCarloSim {

public:
    std::default_random_engine dre{};
    std::uniform_real_distribution<double> urd;
    std::uniform_int_distribution<int> uid;

public:
    MCS_Real_and_Integer(int i_nr_trials, double lb, double ub,
            int i_min, int i_max, int nr_random_reals,
            std::function<bool(std::vector<double>&)> f_real,
            std::function<bool(std::vector<int>&)> f_integer )
        : MonteCarloSim(i_nr_trials, f_real, f_integer) {

        nr_random_real_values = nr_random_reals;

        std::uniform_real_distribution<double> urd_tmp(lb, ub);
        urd = std::move(urd_tmp);

        std::uniform_int_distribution<int> uid_tmp(i_min, i_max);
        uid = std::move(uid_tmp);
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            for ( int jx = 0; jx < nr_random_real_values; ++jx )
                vector_of_random_real_values.push_back(urd(dre));
            if ( real_condition_met(vector_of_random_real_values) )
                cumulative_value += 1.0;
            vector_of_random_real_values.clear();
        }
    }
};

#endif //MONTECARLO_MCS_REAL_AND_INTEGER_H
