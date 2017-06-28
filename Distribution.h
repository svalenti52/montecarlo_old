/**
 * \file Distribution.h
 * \date 27-Jun-2017
 */

#ifndef MONTECARLO_DISTRIBUTION_H
#define MONTECARLO_DISTRIBUTION_H

#include <vector>
#include <random>

enum class DistributionType {
    VoidDistribution,
    UniformIntegral,
    UniformReal,
    BernoulliIntegral
};

template <class T, DistributionType = DistributionType::VoidDistribution>
class Distribution {};

template <class T>
class Distribution <T, DistributionType::UniformIntegral> {
    std::default_random_engine dre;
    std::uniform_int_distribution<T> randomDistribution;
    int nr_events;
public:
    Distribution(T i_min, T i_max, int i_nr_events)
            : randomDistribution(i_min, i_max), nr_events(i_nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    Distribution(T i_min, T i_max, int i_nr_events, int i_seed)
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

    std::vector<T> events;
};

template <class T>
class Distribution <T, DistributionType::UniformReal> {
    std::default_random_engine dre;
    std::uniform_real_distribution<T> randomDistribution;
    int nr_events;
public:
    Distribution(T i_lb, T i_ub, int i_nr_events)
            : randomDistribution(i_lb, i_ub), nr_events(i_nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    Distribution(T i_lb, T i_ub, int i_nr_events, int i_seed)
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

    std::vector<T> events;
};

template <class T>
class Distribution <T, DistributionType::BernoulliIntegral> {
    std::default_random_engine dre;
    std::bernoulli_distribution randomDistribution;
    int nr_events;
public:
    Distribution(T i_lb, T i_ub, int i_nr_events)
            : randomDistribution(0.5), nr_events(i_nr_events) {
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(randomDistribution(dre));
    }

    Distribution(T i_lb, T i_ub, int i_nr_events, int i_seed)
            : randomDistribution(static_cast<double>(i_lb) / static_cast<double>(i_ub)),
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

    std::vector<T> events;
};


#endif //MONTECARLO_DISTRIBUTION_H
