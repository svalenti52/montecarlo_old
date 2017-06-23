/**
 * \file MCS_Real_and_Integer.cpp
 * \date 16-Jun-2017
 *
 */

#ifndef MONTECARLO_MCS_REAL_AND_INTEGER_H
#define MONTECARLO_MCS_REAL_AND_INTEGER_H

#include <val/montecarlo/MonteCarloSim.h>
#include <random>
#include <functional>
#include <vector>
#include <val/montecarlo/Deque_of_Difference.h>
#include <val/montecarlo/Random_Event.h>

class MCS_Real_and_Integer : public MonteCarloSim {

public:

    //Random_Event<double> random_real_events;
    Distribution<double> random_real_events;

    //Random_Event<int> random_discrete_events;
    Distribution<int> random_discrete_events;

    MCS_Real_and_Integer(int i_nr_trials,
            double lb,
            double ub,
            int i_min,
            int i_max,
            int nr_random_reals,
            int nr_random_integers,
            std::function<bool(std::vector<double>&)> f_real,
            std::function<bool(std::vector<int>&)> f_integer )
        : MonteCarloSim(i_nr_trials, f_real, f_integer),
          random_real_events(lb, ub, nr_random_reals),
          random_discrete_events(i_min, i_max, nr_random_integers) {
        interim_value = 1.0;
    }
    // TBD - the explicit '1' passed as a parameter needs to be made variable

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            if ( real_condition_met(random_real_events.events) )
                cumulative_value += interim_value;
            random_real_events.reload_random_values();
        }
    }

    //double interim_count;
};

#endif //MONTECARLO_MCS_REAL_AND_INTEGER_H
