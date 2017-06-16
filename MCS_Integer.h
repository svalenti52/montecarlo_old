/**
 * \file MCS_Integer.h
 * \date 15-Jun-2017
 *
 */

#ifndef MONTECARLO_MCS_INTEGER_H
#define MONTECARLO_MCS_INTEGER_H

#include <functional>
#include <iostream>
#include <random>
#include "MonteCarloSim.h"

class MCS_Integer : MonteCarloSim {
protected:
    std::default_random_engine dre{};
    std::uniform_int_distribution<int> uid;
public:
    MCS_Integer(int i_nr_trials, int i_min, int i_max, int i_pre_size, std::function<bool(std::vector<double>&)> f)
            : MonteCarloSim(i_nr_trials, f) {
        std::uniform_int_distribution<int> uid_tmp(i_min, i_max);
        uid = std::move(uid_tmp);
        nr_random_real_values = i_pre_size;
    }
};

#endif //MONTECARLO_MCS_INTEGER_H
