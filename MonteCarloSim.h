/** \file MonteCarloSim.h
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

class MonteCarloSim {
protected:
    int nr_trials;
    double cumulative_value;
    int nr_random_integer_values;
    std::vector<int> vector_of_random_integer_values;
    int nr_random_real_values;
    std::vector<double> vector_of_random_real_values;
    std::function<bool(std::vector<double>&)> real_condition_met;
    std::function<bool(std::vector<int>&)> integer_condition_met;
public:

    MonteCarloSim() : nr_trials(1'000'000), cumulative_value(0.0) {
        real_condition_met =  nullptr;
    }

    MonteCarloSim( int i_nr_trials,
            std::function<bool(std::vector<double>&)> i_condition_met )
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        real_condition_met = i_condition_met;
    }

    MonteCarloSim( int i_nr_trials,
            std::function<bool(std::vector<double>&)> i_condition_met,
            std::function<bool(std::vector<int>&)> i_integer_condition_met )
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        real_condition_met = i_condition_met;
        integer_condition_met = i_integer_condition_met;
    }
    //--------------------------------------------------------------------

    void load_condition_met(std::function<bool(std::vector<double>&)> f) {
        real_condition_met = f;
    }

    virtual void run() {
        for ( int ix = 0; ix < nr_trials; ++nr_trials ) {
            if ( real_condition_met(vector_of_random_real_values) )
                cumulative_value += 1.0;
        }
    }

    virtual void print_result() {
        std::cout << "probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }
};

#endif //MONTECARLO_MONTECARLOSIM_H
