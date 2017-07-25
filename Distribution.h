/**
 * \file Distribution.h
 * \date 27-Jun-2017
 *
 * \brief Template-based implementation with an enumeration used to separately
 * define each distribution (since their signatures are distinct).
 *
 * \details tbd - try making a template of the distribution type. However, this
 * may too complicated because of the varied requirements of the constructors.
 */

#ifndef MONTECARLO_DISTRIBUTION_H
#define MONTECARLO_DISTRIBUTION_H

#include <vector>
#include <deque>
#include <random>
#include <algorithm>

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

enum class Structure {
    List_With_Repetition,
    List_Without_Repetition,  ///> Permutations
    Set_With_Repetition,
    Set_Without_Repetition
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
    Structure structure;
public:

    /**
     *
     * @param _min Minimum value to be used by the random number generator
     * @param _max Maximum value to be used by the random number generator
     * @param _nr_events Number of sequential events to generated
     * @param _seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T _min, T _max, int _nr_events, int _seed=1)
            : randomDistribution(_min, _max), nr_events(_nr_events), dre(_seed),
            structure(Structure::List_With_Repetition){
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    Distribution(int _nr_events, Structure _structure)
            : randomDistribution(0, _nr_events-1), nr_events(_nr_events),
            structure(_structure) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(ix);
        std::random_shuffle(events.begin(), events.end());
    }

    void reload_random_values() {
        if ( structure == Structure::List_Without_Repetition )
            std::random_shuffle(events.begin(), events.end());
        else
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
     * @param _lb Minimum value to be used by the random number generator
     * @param _ub Maximum value to be used as an upper bound by the random number generator
     * @param _nr_events Number of sequential events to generated
     * @param _seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T _lb, T _ub, int _nr_events, int _seed=1)
            : randomDistribution(_lb, _ub), nr_events(_nr_events), dre(_seed) {
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
     * @param _numerator Numerator of probability of 1 (true)
     * @param _denominator Denominator of probability of 1 (true)
     * @param _nr_events Number of sequential events to generated
     * @param _seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T _numerator, T _denominator, int _nr_events, int _seed=1)
            : randomDistribution(static_cast<double>(_numerator) / static_cast<double>(_denominator)),
              nr_events(_nr_events), dre(_seed) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    /**
     *
     * @param probability_of_true Fixed type double representing probability of 1 (true)
     * @param _nr_events Number of sequential events to generated
     * @param _seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(double probability_of_true, int _nr_events, int _seed=1)
            : randomDistribution(probability_of_true),
              nr_events(_nr_events), dre(_seed) {
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
