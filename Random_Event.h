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

template <class T, class Enable = void>
class Distribution {};

template <class T>
class Distribution <T, typename std::enable_if<std::is_integral<T>::value>::type> {
public:
    std::default_random_engine dre;
    std::uniform_int_distribution<T> uid;
public:
    Distribution(T i_min, T i_max)
    : uid(i_min, i_max) {}
};

template <class T>
class Distribution <T, typename std::enable_if<std::is_floating_point<T>::value>::type> {
public:
    std::default_random_engine dre;
    std::uniform_real_distribution<T> urd;
public:
    Distribution(T i_lb, T i_ub)
            : urd(i_lb, i_ub) {}
};

//------------------------------------------------------
//using namespace std;

template <typename T>
class Random_Event {
    using UID = std::uniform_int_distribution<T>;
    using URD = std::uniform_real_distribution<T>;

    using UID_explicit = std::uniform_int_distribution<int>;
    using URD_explicit = std::uniform_real_distribution<double>;

    int nr_events;
    T lb;
    T ub;

    void create_distribution(T i_lb, T i_ub, std::true_type ) {
        UID tmp_uid(lb, ub);
        uid = std::move(tmp_uid);
        for ( int ix = 0; ix < nr_events; ++ix )
            events.push_back(uid(dre));
    }

    void create_distribution(T i_lb, T i_ub, std::false_type ) {
        URD tmp_urd(lb, ub);
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

    std::default_random_engine dre;
    UID_explicit uid;
    URD_explicit urd;

public:
    std::vector<T> events;

//----------------------------------------------------------------

    Random_Event(T i_lb, T i_ub, int i_nr_events)
            : lb(i_lb), ub(i_ub), nr_events(i_nr_events) {
            create_distribution( lb, ub, std::is_integral<T>() );
        }

    void reload_random_values() {
        for ( int ix = 0; ix < nr_events; ++ix )
            reload_random_value( ix, std::is_integral<T>() );
    }

};

#endif //MONTECARLO_RANDOM_EVENT_H
