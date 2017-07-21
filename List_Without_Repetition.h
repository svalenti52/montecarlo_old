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
#include <algorithm>
#include <deque>
#include <set>

class List_Without_Repetition {

    int nr_trials;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> randomDistribution;
    int nr_events;
    int nr_possible_events;
    std::set<int> ordered_events;

public:

    List_Without_Repetition(int i_nr_trials, int i_nr_events, int i_nr_possible_events)
            : nr_trials(i_nr_trials), randomDistribution(0, i_nr_possible_events-1),
            nr_events(i_nr_events), nr_possible_events(i_nr_possible_events) {
        if ( nr_events == nr_possible_events ) {
            for (int ix = 0; ix<nr_events; ++ix)
                events.emplace_back(ix);
        }
        else {
            int count = 0;
            while ( count < nr_events )
                if ( ordered_events.insert(randomDistribution(dre)).second )
                    ++count;

            for ( int member : ordered_events )
                events.emplace_back(member);
        }
        std::shuffle(events.begin(), events.end(), dre);
    }
    
    void reload_random_values() {
        std::shuffle(events.begin(), events.end(), dre);
    }

    void run() {

    }

    std::deque<int> events;
};

#endif //MONTECARLO_LIST_WITHOUT_REPETITION_H

