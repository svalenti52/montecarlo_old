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

using Func_One_Double_Vector = std::function<bool(std::vector<double>&)>;
using Func_One_Int_Vector  = std::function<bool(std::vector<int>&)>;
using Func_Two_Int_Vectors = std::function<bool(std::vector<int>&, std::vector<int>&)>;

class MonteCarloSim {
protected:
    int nr_trials;
    double cumulative_value;
    int nr_random_integer_values;
public:
    std::vector<int> random_integer_vector;
protected:
    int nr_random_real_values;
    std::vector<double> random_real_vector;
    Func_One_Double_Vector real_condition_met;
    Func_One_Int_Vector integer_condition_met;
    Func_Two_Int_Vectors integer_condition_met_2;
public:

    MonteCarloSim() : nr_trials(1'000'000), cumulative_value(0.0) {
        real_condition_met =  nullptr;
    }

    MonteCarloSim( int i_nr_trials,
            Func_One_Double_Vector i_condition_met )
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        real_condition_met = i_condition_met;
    }

    MonteCarloSim( int i_nr_trials,
            Func_One_Int_Vector i_condition_met )
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        integer_condition_met = i_condition_met;
    }

    MonteCarloSim( int i_nr_trials,
            Func_One_Double_Vector i_condition_met,
            Func_One_Int_Vector i_integer_condition_met )
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        real_condition_met = i_condition_met;
        integer_condition_met = i_integer_condition_met;
    }

    MonteCarloSim( int i_nr_trials, Func_Two_Int_Vectors f)
            : nr_trials(i_nr_trials), cumulative_value(0.0) {
        integer_condition_met_2 = f;
    }
    //--------------------------------------------------------------------

    void load_condition_met(std::function<bool(std::vector<double>&)> f) {
        real_condition_met = f;
    }

    virtual void run() {
        for ( int ix = 0; ix < nr_trials; ++nr_trials ) {
            if ( real_condition_met(random_real_vector) )
                cumulative_value += 1.0;
        }
    }

    virtual void print_result() {
        std::cout << "probability is = " << cumulative_value/static_cast<double>(nr_trials) << '\n';
    }
};

#endif //MONTECARLO_MONTECARLOSIM_H
