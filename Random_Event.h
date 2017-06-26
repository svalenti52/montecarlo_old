/**
 * \file Random_Event.h
 * \date 18-Jun-2017
 * \brief Encapsulates a sequence of random events in a vector.
 *
 * \details The length of the sequence of random events is given by the
 * third parameter, with the first two parameters giving the lower and
 * upper ends of the range from which the random numbers are derived.
 */

#ifndef MONTECARLO_RANDOM_EVENT_H
#define MONTECARLO_RANDOM_EVENT_H

#include <vector>
#include <random>

template <class T, class Enable = void>
class Distribution {};

template <class T>
class Distribution <T, typename std::enable_if<std::is_integral<T>::value>::type> {
    std::default_random_engine dre;
    std::uniform_int_distribution<T> uniform_distribution;
    int nr_events;
public:
    Distribution(T i_min, T i_max, int i_nr_events)
            : uniform_distribution(i_min, i_max), nr_events(i_nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uniform_distribution(dre));
    }

    Distribution(T i_min, T i_max, int i_nr_events, int i_seed)
            : uniform_distribution(i_min, i_max), nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uniform_distribution(dre));
    }

    void reload_random_values() {
        for ( T& value : events )
            value = uniform_distribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    std::vector<T> events;
};

template <class T>
class Distribution <T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
    std::default_random_engine dre;
    std::uniform_real_distribution<T> uniform_distribution;
    int nr_events;
public:
    Distribution(T i_lb, T i_ub, int i_nr_events)
            : uniform_distribution(i_lb, i_ub), nr_events(i_nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uniform_distribution(dre));
    }

    Distribution(T i_lb, T i_ub, int i_nr_events, int i_seed)
            : uniform_distribution(i_lb, i_ub), nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uniform_distribution(dre));
    }

    void reload_random_values() {
        for ( T& value : events )
            value = uniform_distribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    std::vector<T> events;
};

#endif //MONTECARLO_RANDOM_EVENT_H
