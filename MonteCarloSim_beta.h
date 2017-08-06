/**
 * \file MonteCarloSim_beta.h
 * \date 5-Aug-2017
 *
 * \brief
 *
 */

#ifndef MONTECARLO_MONTECARLOSIM_BETA_H
#define MONTECARLO_MONTECARLOSIM_BETA_H

#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <val/montecarlo/Distribution_beta.h>

using DRE = std::default_random_engine;

/**
 * MonteCarloSimulation Class, consists of Constructor and the methods: run, change_message, and
 * print_result. This is a reworking of the original MonteCarloSim class. The main differences are the
 * presence of a random number generator and a template for the y-axis value.
 * @tparam T - For the x-axis or domain of the distribution, expected to be either integral or floating point.
 * @tparam U - For the y-axis or range of the distribution, expected to be either integral or floating point.
 * @tparam D - DistributionType (e.g., UniformIntegral, UniformReal)
 */

template <class T, class U, template <class> class D>
class MonteCarloSimulation {
protected:
    int nr_trials; ///> number of repeated trials run for the simulation
    DRE dre;			///> default random engine (random number generator)
    U cumulative_value; ///> accumulates the interim value for nr_trials
    U interim_value;		///> value determined for each trial
    std::string message; ///> message can be changed to match the meaning of cumulative_value/nr_trials
    Distribution<T, D> distribution; ///> (e.g., real) and deque of numbers selected from it
    std::function<bool(Distribution<T, D>&, U&, DRE&)> condition_met; ///> function containing particulars of the simulation

public:

    /**
     * MonteCarloSimulation - latest attempt at generalising a system includes separating the
     * random number generator from the distribution. Also includes establishing a type for the
     * values (class U for the y-axis).
     * @param _nr_trials number of repeated trials run for the simulation
     * @param _seed integer seed for the random number generator
     * @param _condition_met function containing particulars of the simulation
     * @param _distribution (e.g., real) and deque of numbers selected from it
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
     * show_distribution - shows the contents of the distribution
     */
    void show_distribution() {
        distribution.show_contents();
        std::cout << '\n';
    }
};

#endif //MONTECARLO_MONTECARLOSIM_BETA_H
