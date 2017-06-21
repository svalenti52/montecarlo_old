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
#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Random_Event.h>

class MCS_Real : public MonteCarloSim {
public:

    //Random_Event<double> random_events;
    Distribution<double> random_events;

    MCS_Real(int i_nr_trials, double lb, double ub, int i_nr_random_reals, std::function<bool(std::vector<double>&)> f)
            : MonteCarloSim(i_nr_trials, f ), random_events(lb, ub, i_nr_random_reals),
            interim_count(1.0) {
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            if ( real_condition_met(random_events.events) )
                cumulative_value += interim_count;
            random_events.reload_random_values();
        }
    }

    double interim_count;
};

#endif //MONTECARLO_MCS_REAL_H
