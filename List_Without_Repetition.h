/**
 * \file List_Without_Repetition.h
 * \date 20-Jul-2017
 *
 * \brief
 *
 *
 */

#ifndef MONTECARLO_LIST_WITHOUT_REPETITION_H
#define MONTECARLO_LIST_WITHOUT_REPETITION_H

#include <random>

class List_Without_Repetition {

    std::default_random_engine dre;
    std::uniform_int_distribution<int> randomDistribution;
    int nr_events;

public:
    List_Without_Repetition();

};

#endif //MONTECARLO_LIST_WITHOUT_REPETITION_H

