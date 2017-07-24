/**
 * \file List_Without_Repetition.h
 * \date 20-Jul-2017
 *
 * \brief Integers selected from 0 up to nr_possible_events-1 (inclusive),
 * distributed across nr_events (nr_events <= nr_possible_events).
 *
 *
 */

#ifndef MONTECARLO_LIST_WITHOUT_REPETITION_H
#define MONTECARLO_LIST_WITHOUT_REPETITION_H

#include <random>
#include <algorithm>
#include <deque>
#include <set>
#include <functional>
#include <iostream>

class List_Without_Repetition {

    int nr_trials;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> randomDistribution;
    int nr_events;
    int nr_possible_events;
    std::function<bool(std::deque<int>&, double&)> condition_met;
    double interim_value;
    double cumulative_value;
    std::string message;

    /**
     * select_members_from_possible_events - a set is used to randomly select
     * nr_events from the pool of possible events. Once selection is complete,
     * the selected members are then loaded into the events deque.
     */
    void select_members_from_possible_events() {
        std::set<int> ordered_events;
        while ( ordered_events.size() < nr_events )
            ordered_events.insert(randomDistribution(dre));

        events.clear();  /// out with the old events

        for ( int member : ordered_events )
            events.emplace_back(member); /// and in with the new events
    }

public:

    List_Without_Repetition(int _nr_trials, int _nr_events, int _nr_possible_events,
            std::function<bool(std::deque<int>&, double&)> _condition_met )
            : nr_trials(_nr_trials), randomDistribution(0, _nr_possible_events-1),
            nr_events(_nr_events), nr_possible_events(_nr_possible_events),
              condition_met(std::move(_condition_met)),
            interim_value(1.0), cumulative_value(0.0),
            message("probability is = ") {

        if ( nr_events == nr_possible_events ) {
            for (int ix = 0; ix<nr_events; ++ix)
                events.emplace_back(ix);
        }
        else
            select_members_from_possible_events();

        std::shuffle(events.begin(), events.end(), dre);
    }
    
    void reload_random_values() {
        if ( nr_events != nr_possible_events )
            select_members_from_possible_events();

        std::shuffle(events.begin(), events.end(), dre);
    }

    void run() {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            if ( condition_met(events, interim_value) )
                cumulative_value += interim_value;
            reload_random_values();
        }
    }

    void print_result() {
        std::cout << message << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }

    void print_elements() {
        for ( int elements : events )
            std::cout << elements << " ";
        std::cout << '\n';
    }

    std::deque<int> events;
};

#endif //MONTECARLO_LIST_WITHOUT_REPETITION_H

