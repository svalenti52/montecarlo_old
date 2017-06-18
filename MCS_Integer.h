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
#include "MonteCarloSim.h"
#include "Random_Event.h"

class MCS_Integer : public MonteCarloSim {
protected:
    std::default_random_engine dre{};
    std::uniform_int_distribution<int> uid;
public:

    Random_Event random_event;

    MCS_Integer(int i_nr_trials, int i_min, int i_max, int i_nr_random_integer_values,
            Func_Two_Int_Vectors f)
            : MonteCarloSim(i_nr_trials, f), interim_count(1.0),
              random_event(i_min, i_max, i_nr_random_integer_values) {
        std::uniform_int_distribution<int> uid_tmp(i_min, i_max);
        uid = std::move(uid_tmp);
        nr_random_integer_values = i_nr_random_integer_values;
    }

    void run() override {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            interim_count = 0.0;
            integer_state_vector = permanent_state_vector;
            /*for ( int jx = 0; jx < nr_random_integer_values; ++jx )
                random_integer_vector.push_back(uid(dre));*/
            if ( integer_condition_met_2(random_event.integer_event, integer_state_vector) )
                cumulative_value += interim_count; // have to accommodate more than just incrementing by one
            random_integer_vector.clear();
        }

    }

    void load_integer_state_vector(std::vector<int>& i_state_vector) {
        for ( int i : i_state_vector )
            permanent_state_vector.push_back(i);
    }

    double interim_count;
    std::vector<int> integer_state_vector;
    std::vector<int> permanent_state_vector;
};

#endif //MONTECARLO_MCS_INTEGER_H
