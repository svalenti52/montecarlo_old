/**
 * \file MonteCarloSim_alpha.h
 * \date 25-Jul-2017
 *
 * \brief Update to the class MonteCarloSim.
 */

#ifndef MONTECARLO_MONTECARLOSIM_ALPHA_H
#define MONTECARLO_MONTECARLOSIM_ALPHA_H

#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <val/montecarlo/Distribution_alpha.h>

using DRE = std::default_random_engine;

/**
 * MonteCarloSimulation Class, consists of Constructor and the methods: run, change_message, and
 * print_result. This is a reworking of the original MonteCarloSim class. The main differences are the
 * presence of a random number generator and a template for the y-axis value.
 * @tparam T - For the x-axis or domain of the distribution, expected to be either integral or floating point.
 * @tparam U - For the y-axis or range of the distribution, expected to be either integral or floating point.
 * @tparam D - DistributionType (e.g., UniformIntegral, UniformReal)
 * */

template <class T, class U, DistributionType D>
class MonteCarloSimulation {
protected:
    int nr_trials;
    DRE dre;
    U cumulative_value;
    U interim_value;
    std::string message; ///> message can be changed to match the meaning of cumulative_value/nr_trials
    Distribution<T, D> distribution;
    std::function<bool(Distribution<T, D>&, U&, DRE&)> condition_met;

public:

    /**
     * MonteCarloSimulation - latest attempt at generalising a system includes separating the
     * random number generator from the distribution. Also includes establishing a type for the
     * values (y-axis).
     * @param _nr_trials
     * @param _seed
     * @param _condition_met
     * @param _distribution
     */
    MonteCarloSimulation ( int _nr_trials, int _seed,
            std::function<bool(Distribution<T, D>&, U&, DRE&)> _condition_met,
            Distribution<T, D>& _distribution )
            : nr_trials(_nr_trials), dre(_seed),
              cumulative_value(0), interim_value(1),
              message("probability is = "),
              condition_met(_condition_met),
              distribution(std::move(_distribution))
    {
        distribution.load_random_values(dre);
    }

    /**
     * The signatures of the "reload_random_values" and "condition_met"
     * functions were changed to accept dre from here.
     */
    virtual void run() {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            if ( condition_met(distribution, interim_value, dre) )
                cumulative_value += interim_value;
            distribution.reload_random_values(dre);
        }
    }

    virtual void change_message(const std::string& s) {
        message = s;
    }

    virtual void print_result() {
        std::cout << message
                  << static_cast<double>(cumulative_value)
                          /
                                  static_cast<double>(nr_trials) << '\n';
    }

    /**
     * print_distribution - prints the contents of the distribution
     */
    void show_distribution() {
        distribution.show_contents();
    }
};

#endif //MONTECARLO_MONTECARLOSIM_ALPHA_H
