/**
 * \file Deque_of_Difference.h
 * \date 19-Jun-2017
 * \brief For a given vector, forms a deque of the differences between
 * subsequent values of the vector.
 *
 * \details
 */

//
// Created by svalenti on 6/19/2017.
//

#ifndef MONTECARLO_DEQUE_OF_DIFFERENCE_H
#define MONTECARLO_DEQUE_OF_DIFFERENCE_H

#include <deque>
#include <vector>
#include <algorithm>

template <typename T>
class Deque_of_Difference {

    std::deque<T> difference;
    T max_value; // used to determine ends, will be less than the ends
                // but greater than all interior values
public:
    Deque_of_Difference(std::vector<T> elements,
            T begin_value, T end_value, T i_max_value) : max_value(i_max_value) {

        std::vector<T> temp{std::move(elements)}; // do copy instead of move if need preserve input vector
        std::sort(temp.begin(), temp.end());

        for ( int ix = 0; ix < temp.size()-1; ++ix )
            difference.push_back(temp[ix+1] - temp[ix]);
        difference.push_back(end_value);
        difference.push_front(begin_value);
    }

    T prior_distance(int index) { difference[index]; }
    T subsequent_distance(int index) { difference[index+1]; }

    bool subsequent_closest(int index) { return difference[index+1] < difference[index+2]; }
    bool prior_closest(int index) { return difference[index] < difference[index-1]; }

    bool member_of_mutually_closest(int index) {
        if ( difference[index] > max_value )
            return difference[index+1] < difference[index+2];
        if ( difference[index+1] > max_value )
            return difference[index] < difference[index-1];
        return difference[index] < difference[index+1] ?
               difference[index] < difference[index-1] :
               difference[index+1] < difference[index+2];
    }
};

#endif //MONTECARLO_DEQUE_OF_DIFFERENCE_H
