/**
 * \file Distribution.h
 * \date 27-Jun-2017
 */

#ifndef MONTECARLO_DISTRIBUTION_H
#define MONTECARLO_DISTRIBUTION_H

#include <vector>
#include <deque>
#include <random>

/**
 * DistributionType enum class
 * - VoidDistribution: provided as the default for the primary template
 * - UniformIntegral: when using a uniform integral type
 * - UniformReal: when using a uniform floating point type
 * - BernoulliIntegral: when using a uniform integral type that is restricted to two choices
 *      (We avoid using bool as type because internally vector<bool> would be used
 *      and it does not work with other internal functions that are part of the MCS).
 *      NOTE: The prior statement is currently not applicable because of
 *      changing over to a deque as the basic structure for multiple events.
 *      It appears to have little effect on performance...
 */
enum class DistributionType {
    VoidDistribution,
    UniformIntegral,
    UniformReal,
    BernoulliIntegral
};

/**
 * Primary template, note it has VoidDistribution as the default DistributionType.
 * @tparam T
 */
template <class T, DistributionType = DistributionType::VoidDistribution>
class Distribution {};

/**
 * Template Specialization
 * Distribution of Uniform Integral values
 * @tparam T should be an integral type (other than bool)
 */
template <class T>
class Distribution <T, DistributionType::UniformIntegral> {
    std::default_random_engine dre;
    std::uniform_int_distribution<T> randomDistribution;
    int nr_events;
public:

    /**
     *
     * @param i_min Minimum value to be used by the random number generator
     * @param i_max Maximum value to be used by the random number generator
     * @param i_nr_events Number of sequential events to generated
     * @param i_seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T i_min, T i_max, int i_nr_events, int i_seed=1)
            : randomDistribution(i_min, i_max), nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values() {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end() {
        events.push_back(randomDistribution(dre));
    }

    T sum() {
        T cumulative = 0;
        for ( T element : events )
            cumulative += element;
        return cumulative;
    }

    std::deque<T> events;
};

/**
 * Template Specialization
 * Distribution of Uniform Floating Point values
 * @tparam T should be an floating point type
 */
template <class T>
class Distribution <T, DistributionType::UniformReal> {
    std::default_random_engine dre;
    std::uniform_real_distribution<T> randomDistribution;
    int nr_events;
public:

    /**
     *
     * @param i_lb Minimum value to be used by the random number generator
     * @param i_ub Maximum value to be used as an upper bound by the random number generator
     * @param i_nr_events Number of sequential events to generated
     * @param i_seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T i_lb, T i_ub, int i_nr_events, int i_seed=1)
            : randomDistribution(i_lb, i_ub), nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values() {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end() {
        events.push_back(randomDistribution(dre));
    }

    T sum() {
        T cumulative = 0;
        for ( T element : events )
            cumulative += element;
        return cumulative;
    }

    std::deque<T> events;
};

/**
 * Template Specialization
 * Distribution of Integral values restricted to two values
 * @tparam T should be an integral type, suggest type restricted to 0 (false) and 1 (true)
 *      (Note: should not use bool because the library uses a vector and members of
 *      vector<bool> cannot be referenced using general methods).
 *      NOTE: The prior statement is currently not applicable because of
 *      changing over to a deque as the basic structure for multiple events.
 */
template <class T>
class Distribution <T, DistributionType::BernoulliIntegral> {
    std::default_random_engine dre;
    std::bernoulli_distribution randomDistribution;
    int nr_events;
public:

    /**
     *
     * @param i_numerator Numerator of probability of 1 (true)
     * @param i_denominator Denominator of probability of 1 (true)
     * @param i_nr_events Number of sequential events to generated
     * @param i_seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T i_numerator, T i_denominator, int i_nr_events, int i_seed=1)
            : randomDistribution(static_cast<double>(i_numerator) / static_cast<double>(i_denominator)),
              nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    /**
     *
     * @param probability_of_true Fixed type double representing probability of 1 (true)
     * @param i_nr_events Number of sequential events to generated
     * @param i_seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(double probability_of_true, int i_nr_events, int i_seed=1)
            : randomDistribution(probability_of_true),
              nr_events(i_nr_events), dre(i_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values() {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end() {
        events.push_back(randomDistribution(dre));
    }

    std::deque<T> events;
};

#endif //MONTECARLO_DISTRIBUTION_H
