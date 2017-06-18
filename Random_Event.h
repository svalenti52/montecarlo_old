//
// Created by svalenti on 6/18/2017.
//

#ifndef MONTECARLO_RANDOM_EVENT_H
#define MONTECARLO_RANDOM_EVENT_H

#include <vector>
#include <random>

class Random_Event {
public:

    std::default_random_engine dre;
    std::uniform_int_distribution<int> uid;
    std::uniform_real_distribution<double> urd;

    int nr_integer_events;
    std::vector<int> integer_event;
    int min;
    int max;

    int nr_real_events;
    std::vector<double> real_event;
    double lb;
    double ub;


//----------------------------------------------------------------

    Random_Event(int i_min, int i_max, int nr_events)
            : min(i_min), max(i_max), nr_integer_events(nr_events)
    {
        std::uniform_int_distribution<int> tmp_uid(min, max);
        uid = std::move(tmp_uid);
        for ( int ix = 0; ix < nr_integer_events; ++ix )
            integer_event.push_back(uid(dre));
    }

    Random_Event(double i_lb, double i_ub, int nr_events)
            : lb(i_lb), ub(i_ub), nr_real_events(nr_events)
    {
        std::uniform_real_distribution<double> tmp_urd(lb, ub);
        urd = std::move(tmp_urd);
        for ( int ix = 0; ix < nr_real_events; ++ix )
            real_event.push_back(urd(dre));
    }

    void reload_random_integers() {
        for ( int ix = 0; ix < nr_integer_events; ++ix )
            integer_event[ix] = uid(dre);
    }

    void reload_random_reals() {
        for ( int ix = 0; ix < nr_real_events; ++ix )
            real_event[ix] = urd(dre);
    }

};

#endif //MONTECARLO_RANDOM_EVENT_H
