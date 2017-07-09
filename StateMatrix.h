/**
 * \file StateMatrix.h
 * \date 8-Jul-2017
 *
 *
 */

#ifndef MONTECARLO_STATEMATRIX_H
#define MONTECARLO_STATEMATRIX_H

#include <iostream>
#include <vector>
#include <val/montecarlo/State.h>

class StateMatrix {

    int nr_trials;

    std::vector<State> states;
    int current_state;
    int absorbing_state;

    std::default_random_engine dre;

    double cumulative_value;

public:

    StateMatrix(int i_nr_trials, std::vector<State> i_states, int i_current_state, int i_absorbing_state) :
            nr_trials(i_nr_trials),
            states(i_states),
            current_state(i_current_state),
            absorbing_state(i_absorbing_state),
            cumulative_value(0.0) {}

    void run() {

        for ( int ix = 0; ix < nr_trials; ++ix ) {
            double interim_value = 0.0;
            double current_state = 0;
            while ( current_state != absorbing_state ) {
                int interim_index = states[current_state].uid(dre);
                current_state = states[current_state].transitions[interim_index];
                interim_value += 1.0;
            }
            cumulative_value += interim_value;
        }
    }

    void print_results() {
        std::cout << "\nAverage number of transitions = "
                  << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }

    friend std::ostream& operator << (std::ostream& o, StateMatrix& sm);
};

std::ostream& operator << (std::ostream& o, StateMatrix& sm) {

    for ( State& s : sm.states )
        o << s;
    return o;
}

#endif //MONTECARLO_STATEMATRIX_H
