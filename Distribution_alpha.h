/**
 * \file Distribution_alpha.h
 * \date 25-Jul-2017
 *
 * \brief Alpha reworking of the Distribution class, mainly removing the random
 * number generator from the distribution.
 *
 */

#ifndef MONTECARLO_DISTRIBUTION_ALPHA_H
#define MONTECARLO_DISTRIBUTION_ALPHA_H

#include <vector>
#include <deque>
#include <random>
#include <algorithm>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

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
    BernoulliIntegral,
    PoissonIntegral,
    ExponentialReal,
    PiecewiseLinearReal
};

enum class Structure {
    List_With_Repetition,
    List_Without_Repetition,  ///> Permutations
    Set_With_Repetition,
    Set_Without_Repetition
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Primary template, note it has VoidDistribution as the default DistributionType.
 * @tparam T
 */
template <class T, DistributionType = DistributionType::VoidDistribution>
class Distribution {};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Uniform Distribution of Integral values
 * @tparam T should be an integral type (other than bool)
 */
template <class T>
class Distribution <T, DistributionType::UniformIntegral> {
    std::uniform_int_distribution<T> randomDistribution;
    int nr_events;
    Structure structure;
public:

    /**
     *
     * @param _min Minimum value to be used by the random number distribution
     * @param _max Maximum value to be used by the random number distribution
     * @param _nr_events Number of sequential events to generated
     * @param _seed Seed to be used by the random number generator (defaults to 1)
     */
    Distribution(T _min, T _max, int _nr_events)
            : randomDistribution(_min, _max), nr_events(_nr_events),
              structure(Structure::List_With_Repetition){
        //for ( int ix = 0; ix < nr_events; ++ix )
          //  events.push_back(randomDistribution(dre));
    }

    /*Distribution(int _nr_events, Structure _structure)
            : randomDistribution(0, _nr_events-1), nr_events(_nr_events),
              structure(_structure) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(ix);
        std::random_shuffle(events.begin(), events.end());
    }*/

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
    }

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Uniform Distribution of Floating Point values
 * @tparam T should be an floating point type
 */
template <class T>
class Distribution <T, DistributionType::UniformReal> {
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
    Distribution(T _lb, T _ub, int _nr_events)
            : randomDistribution(_lb, _ub), nr_events(_nr_events) {
        //for ( int ix = 0; ix < nr_events; ++ix )
          //  events.push_back(randomDistribution(dre));
    }

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
    }

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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Bernoulli Distribution of Integral values restricted to two values
 * @tparam T should be an integral type, suggest type restricted to 0 (false) and 1 (true)
 *
 */
template <class T>
class Distribution <T, DistributionType::BernoulliIntegral> {
    std::bernoulli_distribution randomDistribution;
    int nr_events;
public:

    /**
     *
     * @param _numerator Numerator of probability of 1 (true)
     * @param _denominator Denominator of probability of 1 (true)
     * @param _nr_events Number of sequential events to generated
     */
    Distribution(T _numerator, T _denominator, int _nr_events)
            : randomDistribution(static_cast<double>(_numerator) / static_cast<double>(_denominator)),
              nr_events(_nr_events) {
        //for ( int ix = 0; ix < nr_events; ++ix )
          //  events.push_back(randomDistribution(dre));
    }

    /**
     *
     * @param probability_of_true Fixed type double representing probability of 1 (true)
     * @param _nr_events Number of sequential events to generated
     */
    Distribution(double probability_of_true, int _nr_events)
            : randomDistribution(probability_of_true),
              nr_events(_nr_events) {
        //for ( int ix = 0; ix < nr_events; ++ix )
          //  events.push_back(randomDistribution(dre));
    }

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Poisson Distribution of non-negative integral values, unbounded on the right
 * @tparam T should be an integral type
 *
 */
template <class T>
class Distribution<T, DistributionType::PoissonIntegral> {
    std::poisson_distribution<T> randomDistribution;
    int nr_events;
public:
    Distribution(double _mean, int _nr_events)
            : randomDistribution(_mean), nr_events(_nr_events) {}

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Exponential Distribution of non-negative real values, unbounded on the right
 * @tparam T should be a floating point type
 *
 */
template <class T>
class Distribution<T, DistributionType::ExponentialReal> {
    std::exponential_distribution<T> randomDistribution;
    int nr_events;
public:
    Distribution(double _lambda, int _nr_events)
            : randomDistribution(_lambda), nr_events(_nr_events) {}

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

/**
 * Template Specialization
 * Piecewise Linear Distribution of real values
 * @tparam T should be a floating point type
 *
 */
template <class T>
class Distribution<T, DistributionType::PiecewiseLinearReal> {
    std::piecewise_linear_distribution<T> randomDistribution;
    int nr_events;
public:
    using ITERATOR = std::vector<double>::iterator;
    Distribution(ITERATOR _begin_intervals, ITERATOR _end_intervals,
            ITERATOR begin_weights, int _nr_events)
            : randomDistribution(_begin_intervals, _end_intervals, begin_weights), nr_events(_nr_events) {}

    void load_random_values(std::default_random_engine& dre) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    void reload_random_values(std::default_random_engine& dre) {
        for ( T& value : events )
            value = randomDistribution(dre);
    }

    void reload_values (const std::vector<T>& vector_of_values) {
        for ( int ix = 0; ix < events.size(); ++ix )
            events[ix] = vector_of_values[ix];
    }

    void reload_random_value(int index, std::default_random_engine& dre) {
        events[index] = randomDistribution(dre);
    }

    void add_random_value_to_end(std::default_random_engine& dre) {
        events.push_back(randomDistribution(dre));
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

#endif //MONTECARLO_DISTRIBUTION_ALPHA_H
