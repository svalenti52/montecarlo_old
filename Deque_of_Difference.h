/**
 * \file Deque_of_Difference.h
 * \date 19-Jun-2017
 * \brief For a given vector, forms a deque of the differences between
 * subsequent values of the vector.
 *
 * \details There are (thus far) two different uses depending on the
 * constructor used:
 * 1) a deque of the differences between the elements
 * of an input vector; the vector is sorted prior to the differences
 * being taken; two 'maximal' elements are added to either end to represent
 * an infinite distance. The 'member_of_mutually_closest' function
 * applies here.
 * 2) a deque of the differences between the elements of an input vector
 * and a given anchor point. The 'closest_is_positive' function applies here.
 */

#ifndef MONTECARLO_DEQUE_OF_DIFFERENCE_H
#define MONTECARLO_DEQUE_OF_DIFFERENCE_H

#include <deque>
#include <vector>
#include <algorithm>

template <typename T>
class Deque_of_Difference {

    std::deque<T> differences;
    T max_value; ///> used to mark infinity or a relatively large value
public:

    /**
     * Constructs a deque of positive differences between the ordered elements of the input
     * vector. At both ends, "infinite" values are then placed. A "maximum" value is also
     * passed in that should have the property of being greater than all the interior
     * differences but less than the value(s) chosen to represent infinity.
     * @param elements - assumed sorted vector of data in ascending order (positive distances)
     * @param begin_value - represents the infinite distance before the first element
     * @param end_value - represents the infinite distance after the last element
     * @param i_max_value - greater than all the interior distances, less than the "infinite" values
     */
    Deque_of_Difference(std::vector<T>& elements,
            T begin_value, T end_value, T i_max_value) : max_value(i_max_value) {

        for ( int ix = 0; ix < elements.size()-1; ++ix )
            differences.push_back(elements[ix+1] - elements[ix]);
        differences.push_back(end_value);
        differences.push_front(begin_value);
    }

    T prior_distance(int index) { differences[index]; }
    T subsequent_distance(int index) { differences[index+1]; }

    bool subsequent_closest(int index) { return differences[index+1] < differences[index+2]; }
    bool prior_closest(int index) { return differences[index] < differences[index-1]; }

    /**
     * Indicates whether the element represented at position index is a member of a mutually
     * closest pair (either the element at position index-1 or index+1, but not both, must be
     * closest to the element at index). However, the closer of the two may also be even closer
     * to a different index, in which case, the element at position index would not be a member
     * of a mutually closest set.
     * @param index - indicates position of element to test for membership.
     * @return - indicates whether element is a member of the mutually closest set.
     */
    bool member_of_mutually_closest(int index) {
        if ( differences[index] > max_value )
            return differences[index+1] < differences[index+2];
        if ( differences[index+1] > max_value )
            return differences[index] < differences[index-1];
        return differences[index] < differences[index+1] ?
               differences[index] < differences[index-1] :
               differences[index+1] < differences[index+2];
    }

    //--------------------------------------------------------------------------------------------

    /**
     * Constructs a deque of differences of an input vector of elements and a given anchor point;
     * these differences are allowed to be positive or negative. A maximum value is used at
     * initialization to ensure that all points will be closer, i.e., it should be chosen to be
     * largest difference.
     * @param elements - vector of numeric elements.
     * @param anchor_point - a point selected to form the differences with elements.
     * @param i_max_value - a value selected to be the larger than any difference formed.
     */
    Deque_of_Difference(std::vector<T>& elements, T anchor_point, T i_max_value) : max_value(i_max_value) {

        for ( T element : elements )
            differences.push_back(element - anchor_point);
    }

    /**
     * Indicates whether the smallest difference is positive, i.e., which side of
     * the anchor point it is on.
     * @return - see above.
     */
    bool closest_is_positive() {

        if ( differences.size() == 1 ) return differences[0] > 0;

        T smallest_diff = max_value;
        bool is_positive = false;
        for ( T element : differences ) {
            if ( element < 0 ) {
                if ( -element < smallest_diff ) {
                    smallest_diff = -element;
                    is_positive = false;
                }
            }
            else if ( element < smallest_diff ) {
                smallest_diff = element;
                is_positive = true;
            }
        }
        return is_positive;
    }
};

#endif //MONTECARLO_DEQUE_OF_DIFFERENCE_H
