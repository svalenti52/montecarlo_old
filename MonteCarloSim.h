/** 
 * \file MonteCarloSim.h
 * \date 15-Jun-2017.
 *
 * \brief Parent class for Monte Carlo Simulation Projects.
 *
 */

#ifndef MONTECARLO_MONTECARLOSIM_H
#define MONTECARLO_MONTECARLOSIM_H

#include <functional>
#include <iostream>
#include <vector>
#include <val/montecarlo_alt/Distribution.h>

//using Func_One_Double_Vector = std::function<bool(std::vector<double>&)>;
//using Func_One_Int_Vector  = std::function<bool(std::vector<int>&)>;
//using Func_Two_Int_Vectors = std::function<bool(std::vector<int>&, std::vector<int>&)>;

//using VEC_DOUBLE = std::vector<double>;
//using VEC_INTEGER = std::vector<int>;

/**
 * MonteCarloSimulation Class, consists of Constructor and the methods: run, change_message, and
 * print_result. Since the interim_value is now passed in to the condition_met function, the
 * methods increment_interim_value and assign_interim_value are deprecated.
 * @tparam T - For the primary distribution, expected to be either integral or floating point.
 * @tparam U - For the secondary distribution, expected to be either integral or floating point.
 */
template <class T, class U, DistributionType D1, DistributionType D2>
class MonteCarloSimulation {
protected:
    int nr_trials;
    double cumulative_value;
    double interim_value;
    std::string message;
    Distribution<T, D1> primary_distribution;
    Distribution<U, D2> secondary_distribution;
    std::function<bool(std::vector<T>&, std::vector<U>&)> condition_met;
    std::function<bool(Distribution<T, D1>&,
            Distribution<U, D2>&, double&)> condition_metx;
public:

    /**
     * MonteCarloSimulation - Constructs an object that provides the scaffolding for running a Monte Carlo
     * simulation. The major input parameters are:
     *      1) The number of trials to run, more leads to more computation but generally better precision.
     *      2) Condition Met function - returns a bool so that an incremental value can be accumulated.
     *      3) Lower and Upper bounds on the random distributions.
     * This class has two templates, each to be used separately for two distributions, termed the primary
     * and secondary distribution. In one of the use cases, the primary distribution is based on the
     * fundamental type "double", while the secondary distribution is based on "int".
     * Note that there is nothing that prevents the secondary distribution to be used as a deterministic
     * state vector or something similar (one or more of the use cases uses it this way).
     * Currently, the primary distribution is used as a container of random values (see run method below).
     *
     * @param i_nr_trials - Number of trials to run
     * @param i_condition_met - Function having primary, secondary distributions, and reference to interim_value
     * @param i_lb_primary - Lower bound on primary distribution
     * @param i_ub_primary - Upper bound on primary distribution
     * @param nr_events_primary - Number of events occurring on each trial for the primary distribution
     * @param seed_primary - Seed for the random number generator for the primary distribution
     * @param i_lb_secondary - Lower bound on secondary distribution
     * @param i_ub_secondary - Upper bound on secondary distribution
     * @param nr_events_secondary - Number of events occurring on each trial for the secondary distribution
     * @param seed_secondary - Seed for the random number generator for the secondary distribution
     */
    MonteCarloSimulation( int i_nr_trials,
            std::function<bool(Distribution<T, D1>&,
                    Distribution<U, D2>&, double&)> i_condition_met,
            T i_lb_primary, T i_ub_primary, int nr_events_primary, int seed_primary,
            U i_lb_secondary, U i_ub_secondary, int nr_events_secondary, int seed_secondary )
            : nr_trials(i_nr_trials), cumulative_value(0.0),
              interim_value(1.0), message("probability is = "),
              condition_metx(i_condition_met),
              primary_distribution(i_lb_primary, i_ub_primary, nr_events_primary, seed_primary),
              secondary_distribution(i_lb_secondary, i_ub_secondary, nr_events_secondary, seed_secondary ) {
    }

    /**
     * run - executes the simulation. Loops for nr_trials number of times, checking each time for
     * the result of condition_met; if the condition is met, then cumulative_value is increased by
     * interim_value. Note that interim_value is passed by reference, along with primary_distribution
     * and secondary_distribution, so this provides some options within condition_met for adjusting
     * interim_value. Lastly, within the loop, the primary distribution is reset to new random values.
     */
    virtual void run() {
        for ( int ix = 0; ix < nr_trials; ++ix ) {
            if ( condition_metx(primary_distribution, secondary_distribution, interim_value) )
                cumulative_value += interim_value;
            primary_distribution.reload_random_values();
        }
    }

    /**
     * change_message - allows the changing of the message printed in print_result. The default
     * is "probability is = " which is not always appropriate.
     * @param s - string of message to which to change.
     */
    virtual void change_message(const std::string& s) {
        message = s;
    }

    /**
     * print_result - prints a message and the computed result over a number of trials.
     * The computed result is in cumulative_value and is divided by the number of trials.
     */
    virtual void print_result() {
        std::cout << message << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }
};

#endif //MONTECARLO_MONTECARLOSIM_H
