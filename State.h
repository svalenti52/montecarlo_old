//
// Created by svalenti on 7/8/2017.
//

#ifndef MONTECARLO_STATE_H
#define MONTECARLO_STATE_H

#include <vector>
#include <random>

class State {
public:
    int state_ID;
    std::vector<int> transitions;
    std::uniform_int_distribution<int> uniform_int_distribution;

    State(int i_state_ID,
            std::vector<int> i_transitions,
            int i_min, int i_max)
            : state_ID(i_state_ID), transitions(i_transitions),
            uniform_int_distribution(i_min, i_max) {}

};

#endif //MONTECARLO_STATE_H
