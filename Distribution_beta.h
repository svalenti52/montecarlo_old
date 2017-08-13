/**
 * \file Distribution_beta.h
 * \date 5-Aug-2017
 *
 * \brief Distribution class made more compact by template template construct.
 *
 */


#ifndef MONTECARLO_DISTRIBUTION_BETA_H
#define MONTECARLO_DISTRIBUTION_BETA_H

#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <iostream>

template <class T, class PARAM, template <class> class RANDOM_DIST >
class Distribution {
    RANDOM_DIST<T> randomDistribution;
    int nr_events;
public:

    /**
     * Constructor used for uniform integer and real distributions
     * @param _min Minimum value to be used by the random number distribution
     * @param _max Maximum value to be used by the random number distribution
     * @param _nr_events Number of sequential events to generated
     */
    Distribution(
            T _min,
            T _max,
            int _nr_events)

            : randomDistribution(_min, _max), nr_events(_nr_events) {}

    /**
     * Constructor used for Bernoulli, Poisson, Exponential distributions
     * @param _likelihood (probability_of_true, mean, lambda for above distributions)
     * @param _nr_events Number of sequential events to generated
     */
    Distribution(
            PARAM _likelihood,
            int _nr_events)

            : randomDistribution(_likelihood), nr_events(_nr_events) {}

    using ITERATOR = std::vector<double>::iterator;
    /**
     * Constructor used for Piece-wise Linear distribution
     * @param _begin_intervals begin iterator for vector of intervals
     * @param _end_intervals end iterator for vector of intervals
     * @param _begin_weights begin iterator for vector of weights (probabilities)
     * @param _nr_events Number of sequential events to generated
     */
    Distribution(
            ITERATOR _begin_intervals,
            ITERATOR _end_intervals,
            ITERATOR _begin_weights,
            int _nr_events)

            : randomDistribution(_begin_intervals, _end_intervals, _begin_weights),
            nr_events(_nr_events) {}

    /**
     *
     * @param dre
     */
    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    /**
     *
     * @param dre
     */
    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    /**
     *
     * @param vector_of_values
     */
    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    /**
     *
     * @param index
     * @param dre
     */
    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    /**
     *
     * @param dre
     */
    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
    }

    /**
     *
     * @return
     */
    T sum() {
        T cumulative = 0;
        for ( T element : events )
            cumulative += element;
        return cumulative;
    }

    /**
    * show_contents - show, on cout, the contents of the deque
    */
    void show_contents() {
        for ( T event : events )
            std::cout << event << "  ";
    }

    std::deque<T> events;
};

#endif //MONTECARLO_DISTRIBUTION_BETA_H
