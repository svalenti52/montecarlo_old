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
    std::uniform_int_distribution<int> uid;

    State(int i_state_ID,
            std::vector<int> i_transitions,
            int i_min, int i_max)
            : state_ID(i_state_ID), transitions(i_transitions),
            uid(i_min, i_max) {}

    friend std::ostream& operator << (std::ostream& o, State& s);
};

std::ostream& operator << (std::ostream& o, State& s) {

    o << s.state_ID << " - ";
    for ( int tx_id : s.transitions )
        o << tx_id << " ";
    o << '\n';
    return o;
}

#endif //MONTECARLO_STATE_H
