/**
 * \file Random_Event.h
 * \date 18-Jun-2017
 * \brief Encapsulates a sequence of random events in a vector.
 *
 * \details The length of the sequence of random events is given by the
 * third parameter, with the first two parameters giving the lower and
 * upper ends of the range from which the random numbers are derived.
 */

#ifndef MONTECARLO_RANDOM_EVENT_H
#define MONTECARLO_RANDOM_EVENT_H

#include <vector>
#include <random>

template <typename T>
class Random_Event {
public:

    std::default_random_engine dre;
    std::uniform_int_distribution<int> uid;
    std::uniform_real_distribution<double> urd;

    int nr_events;
    std::vector<T> events;
    T lbb;
    T ubb;


//----------------------------------------------------------------

    Random_Event(T i_lb, T i_ub, int i_nr_events)
            : lbb(i_lb), ubb(i_ub), nr_events(i_nr_events) {

            create_distribution( lbb, ubb, std::is_integral<T>() );
        }

    void create_distribution(T i_lb, T i_ub, std::true_type ) {
        std::uniform_int_distribution<T> tmp_uid(lbb, ubb);
        uid = std::move(tmp_uid);
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uid(dre));
    }

    void create_distribution(T i_lb, T i_ub, std::false_type ) {
        std::uniform_real_distribution<T> tmp_urd(lbb, ubb);
        urd = std::move(tmp_urd);
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(urd(dre));
    }

    void reload_random_value( int ix, std::true_type ) {
        events[ix] = uid(dre);
    }

    void reload_random_value( int ix, std::false_type ) {
        events[ix] = urd(dre);
    }

    void reload_random_values() {
        for ( int ix = 0; ix < nr_events; ++ix )
            reload_random_value( ix, std::is_integral<T>() );
    }

};

#endif //MONTECARLO_RANDOM_EVENT_H
