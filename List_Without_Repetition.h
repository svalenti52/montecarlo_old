/**
 * \file List_Without_Repetition.h
 * \date 20-Jul-2017
 *
 * \brief
 *
 *
 */

#ifndef MONTECARLO_LIST_WITHOUT_REPETITION_H
#define MONTECARLO_LIST_WITHOUT_REPETITION_H

#include <random>

class List_Without_Repetition {

    std::default_random_engine dre;
    std::uniform_int_distribution<int> randomDistribution;
    int nr_events;

public:

    List_Without_Repetition(int nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.emplace_back(ix);
        
        std::random_shuffle(events.begin(), events.end());
    }
    
    void reload_random_events() {
        std::random_shuffle(events.begin(), events.end());
    } 
    
    std::deque<int> events;
};

#endif //MONTECARLO_LIST_WITHOUT_REPETITION_H

