/**
 * \file StateMatrix.h
 * \date 8-Jul-2017
 *
 * \brief StateMatrix with vector of states, current_state (initialized with
 * initial state for each trial), absorbing_state (the end state).
 *
 * \details Replaces Monte Carlo Simulation class in that it includes the
 * number of trials, a cumulative value, and contains a method for running
 * the simulation. An interesting detail is the separation of the default
 * random engine from the multiple distributions for the states.
 * IMPORTANT: STATE NUMBERING MUST ALIGN WITH THE VECTOR POSITION OF THE
 * STATES.
 */

#ifndef MONTECARLO_STATEMATRIX_H
#define MONTECARLO_STATEMATRIX_H

#include <iostream>
#include <vector>
#include <val/montecarlo/State.h>

class StateMatrix {

    int nr_trials;

    std::vector<State> states; ///> Aligned vector positions and state values in transitions
    int initial_state; ///> holds initial state
    int absorbing_state; ///> holds final state

    std::default_random_engine dre; ///> core random number generator

    double cumulative_value; ///> Accumulates interim value

public:

    StateMatrix(int _nr_trials, std::vector<State>& _states, int _initial_state, int _absorbing_state) :
            nr_trials(_nr_trials),
            states(std::move(_states)),
            initial_state(_initial_state),
            absorbing_state(_absorbing_state),
            cumulative_value(0.0) {}

    void run() {

        for ( int ix = 0; ix < nr_trials; ++ix ) {
            double interim_value = 0.0;
            int current_state = initial_state;
            while ( current_state != absorbing_state ) {
                current_state = states[current_state].get_next_state(dre);
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
