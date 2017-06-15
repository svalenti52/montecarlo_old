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
    int collective_count;
    double cumulative_value;
    int pre_size;
    std::vector<double> vector_of_values;
    std::function<bool(std::vector<double>&)> condition_met;
    //std::function<bool(std::vector<double>)> collective_condition_met;
public:
    MonteCarloSim() : nr_trials(1'000'000), cumulative_value(0.0) {
        condition_met =  nullptr;
    }
    MonteCarloSim( int i_nr_trials, std::function<bool(std::vector<double>&)> i_function)
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        condition_met = i_function;
    }

    void load_condition_met(std::function<bool(std::vector<double>&)> f) {
        condition_met = f;
    }

    virtual void run() {
        for ( int ix = 0; ix < nr_trials; ++nr_trials ) {
            if ( condition_met(vector_of_values) )
                cumulative_value += 1.0;
        }
    }

    virtual void print_result() {
        std::cout << "probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }
};

#endif //MONTECARLO_MONTECARLOSIM_H
