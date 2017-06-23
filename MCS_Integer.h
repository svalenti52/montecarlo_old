/**
 * \file MCS_Integer.h
 * \date 15-Jun-2017
 *
 */

#ifndef MONTECARLO_MCS_INTEGER_H
#define MONTECARLO_MCS_INTEGER_H

#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <val/montecarlo/MonteCarloSim.h>
#include <val/montecarlo/Random_Event.h>

class MCS_Integer : public MonteCarloSim {
public:

    //Random_Event<int> random_events;

    Distribution<int> random_events;

    MCS_Integer(int i_nr_trials, int i_min, int i_max, int i_nr_random_integer_values,
            Func_Two_Int_Vectors f)
            : MonteCarloSim(i_nr_trials, f),
              random_events(i_min, i_max, i_nr_random_integer_values) {
        interim_value = 1.0;
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            interim_value = 0.0;
            transient_state_vector = initial_state_vector;
            if ( integer_condition_met_2(random_events.events, transient_state_vector) )
                cumulative_value += interim_value; // have to accommodate more than just incrementing by one
        }

    }

    void load_integer_state_vector(std::vector<int>& i_state_vector) {
        for ( int i : i_state_vector )
            initial_state_vector.push_back(i);
    }

    //double interim_count;
    std::vector<int> transient_state_vector;
    std::vector<int> initial_state_vector;
};

#endif //MONTECARLO_MCS_INTEGER_H
