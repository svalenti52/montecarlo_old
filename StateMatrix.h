/**
 * \file StateMatrix.h
 * \date 8-Jul-2017
 *
 *
 */

#ifndef MONTECARLO_STATEMATRIX_H
#define MONTECARLO_STATEMATRIX_H

#include <vector>
#include <val/montecarlo/State.h>

class StateMatrix {

    std::vector<State> states;
    int current_state;
    int absorbing_state;

    std::default_random_engine dre;

public:

    StateMatrix(std::vector<State> i_states, int i_current_state, int i_absorbing_state) :
            states(i_states),
            current_state(i_current_state),
            absorbing_state(i_absorbing_state) {}

};

#endif //MONTECARLO_STATEMATRIX_H
