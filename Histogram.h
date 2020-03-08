/**
 * \file Histogram.h
 * \date 29-Jun-2017
 *
 * \brief Histogram class, with templates for two types: interval (x-axis) and amount (y-axis).
 *
 * \details The Histogram class consists of:
 *      - four variables that delineate the structure of the intervals at a macro level
 *      - a variable for tracking the total amount for the entire histogram
 *      - a container for Bin which tracks both the interval extent and corresponding amount
 *          for each sub-interval.
 * The Histogram class also contains the following member functions:
 *      - increment_bin: increments bin by 1 for counting applications
 *      - add_to_bin: increments bin by an input parameter amount
 *      - get_midpoint: returns bin number by which 50% probability has been reached
 */

#ifndef MONTECARLO_HISTOGRAM_H
#define MONTECARLO_HISTOGRAM_H

#include <vector>
#include <iostream>

template <typename T, typename U>
class Bin;

template <typename T, typename U>
std::ostream& operator <<(std::ostream& o, Bin<T,U>& b);

///------------------------------------------------------------------------------

template <typename X_AXIS, typename Y_AXIS>
class Bin
{
public:
    X_AXIS right_edge_interval; ///> right edge of bin; integer represented if type int
    X_AXIS size_interval; ///> bin_width

    Y_AXIS amount; ///> amount associated with this bin
    
    int index; ///> index associated with this bin, first element is one.

public:
    /**
     * Bin class constructor
     * @param _index - index of bin within container, first element is one.
     * @param _right_edge_interval - value of right edge of bin
     * @param _size - bin_width
     */
    Bin(int _index, X_AXIS _right_edge_interval, X_AXIS _size) :
            index(_index),
            right_edge_interval(_right_edge_interval),
            size_interval(_size),
            amount(0) {}

    /**
     * inc_count_if_less_equal - tests an input parameter value for being less than or
     * equal to the right edge. If it is, increments this bin's amount by one and returns
     * true; if not returns false. Usually used as part of a for loop that terminates
     * when returns true. In that case, it would start at the first interval, seeking
     * the bin in which it belongs since subsequent bins have monotonically increasing
     * values.
     * @param v - input value.
     * @return boolean value indicating whether the input value is LEQ to the right edge.
     */
    bool inc_count_if_less_equal(X_AXIS v)
    {
        if ( v <= right_edge_interval )
        {
            amount = amount + 1;
            return true;
        }
        return false;
    }

    bool add_if_less_equal(X_AXIS v, Y_AXIS _amount)
    {
        if ( v <= right_edge_interval )
        {
            amount = amount + _amount;
            return true;
        }
        return false;
    }

    void inc_count() {
        amount = amount + 1;
    }

    /**
     * add_amount - add amount to the amount of this bin.
     * @param added_amount
     */
    void add_amount(Y_AXIS added_amount) {
        amount += added_amount;
    }

    friend std::ostream& operator << <>(std::ostream& o, Bin<X_AXIS,Y_AXIS>& b);
};

template <typename T, typename U>
std::ostream& operator <<(std::ostream& o, Bin<T,U>& b)
{
    o << b.amount;
    return o;
}

///-------------------------------------------------------------------------------------

template <class X_AXIS, class Y_AXIS>
class Histogram;

template <class X_AXIS, class Y_AXIS>
std::ostream& operator << (std::ostream&, Histogram<X_AXIS,Y_AXIS>&);

/**
 * Histogram class
 * @tparam T - arithmetic type, this applies to the interval (x-axis)
 * @tparam U - arithmetic type, this applies to the amount (y-axis)
 */
template <class T, class U>
class Histogram {

    T lower_bound_left_edge; ///> lower bound of interval; for integers it is one less than integer represented
    T upper_bound_right_edge; ///> upper bound of interval; for integers it is the integer represented
    int nr_bins;                ///> number of bins that make up the interval of the histogram
    T bin_width;                ///> width of an individual bin
    double bin_width_inverse;   ///> multiplicative inverse of bin_width

    std::vector<Bin<T,U>> bins; ///> vector of Bin (size is nr_bins)

    U total_amount;         ///> Tracks total_amount contained in the histogram
    U bin_too_hi;
    U bin_too_lo;
public:
    /**
     * Histogram class constructor - note that the extent of the interval is quite nicely represented
     * by "upper_bound_right_edge - lower_bound_left_edge" regardless of the arithmetic type.
     * @param _lower_bound_left_edge - lower bound of "whole" interval
     * @param _upper_bound_right_edge - upper bound of "whole" interval
     * @param _bin_width - width of bin, should divide evenly into the parametrized interval
     */
    Histogram(T _lower_bound_left_edge,
            T _upper_bound_right_edge,
            T _bin_width) : /// int bin_width
            lower_bound_left_edge(_lower_bound_left_edge),
            upper_bound_right_edge(_upper_bound_right_edge),
            bin_width(_bin_width),
            bin_width_inverse(1.0 / static_cast<double>(_bin_width)),
            total_amount(0),
            bin_too_hi(0),
            bin_too_lo(0)
    {
        nr_bins = static_cast<int>((upper_bound_right_edge - lower_bound_left_edge) / bin_width);
        for ( int ix = 1; ix <= nr_bins; ++ix )
            bins.push_back(Bin<T,U>(ix, lower_bound_left_edge+ix*bin_width, bin_width));
    }

    /**
     * increment_bin - increments indicated bin amount by 1.
     * @param which_bin - external indication of which bin to increment. Also increment total.
     * It is adjusted so that the original lower_bound_right_edge aligns with the 0 component
     * of the bins vector. (Note: lower_bound_right_edge = lower_bound_left_edge + bin_width).
     */
    void increment_bin(int which_bin) {
        int adjusted_index = which_bin - (lower_bound_left_edge + bin_width);
        adjusted_index /= bin_width;
        if ( adjusted_index < 0 || adjusted_index >= nr_bins ) throw;
        bins[adjusted_index].amount += 1;
        total_amount += 1;
    }

    /**
     * add_to_bin - adds i_amount to the bin indicated.
     * @param which_bin - external indication of which bin to increment.
     * It is adjusted so that the original lower_bound_right_edge aligns with the 0 component
     * of the bins vector. (Note: lower_bound_right_edge = lower_bound_left_edge + bin_width).
     * @param _amount - amount to accumulate in both the indicated bin and total
     */
    void add_to_bin(int which_bin, U _amount) {
        int adjusted_index = which_bin - (lower_bound_left_edge + bin_width);
        adjusted_index /= bin_width;
        if ( adjusted_index < 0 || adjusted_index >= nr_bins ) throw;
        bins[adjusted_index].amount += _amount;
        total_amount += _amount;
    }

    /**
     * get_midpoint - calculates half_way_count, then determines the bin number at which it
     * first equals or surpasses the half_way_count.
     * Use Case: Alive_10_Years/challenge8_MCS.cpp.
     * @return the returned index is adjusted to account for the lower_bound_right_edge being
     * aligned with the bin at index 0.
     * (Note: lower_bound_right_edge = lower_bound_left_edge + bin_width).
     */
    int get_midpoint() {
        U half_way_count = total_amount / 2;
        U running_count = 0;
        int ix = 0;
        for ( ; ix < nr_bins; ++ix ) {
            running_count += bins[ix].amount;
            if ( running_count >= half_way_count )
                break;
        }
        return ix + lower_bound_left_edge + bin_width;
    }

    void increment_if_in_range(T x_axis_value) {
        if (x_axis_value < lower_bound_left_edge)
        {
            bin_too_lo += 1;
        }
        else if (x_axis_value > upper_bound_right_edge)
        {
            bin_too_hi += 1;
        }
        else
        {
            uint32_t index_bin = static_cast<int>(std::floor(x_axis_value * bin_width_inverse));
            if (index_bin < nr_bins)
                bins[index_bin].inc_count();
        }
    }

    void add_if_in_range(T x_axis_value, U _amount) {
        if (x_axis_value < lower_bound_left_edge)
        {
            bin_too_lo += _amount;
        }
        else if (x_axis_value > upper_bound_right_edge)
        {
            bin_too_hi += _amount;
        }
        else
        {
            int index_bin = static_cast<int>(std::floor(x_axis_value * bin_width_inverse));
            bins[index_bin].add_amount(_amount);
        }
    }

    /**
     * output stream operator, standard output of histogram. Currently, outputs in format
     * for Python (also many others I am reasonably sure) to read for graphing.
     * @param o ostream that is the receipt of the objects to be printed; this is returned.
     * @param histogram Object of type histogram. Outputs in format usable by Python.
     */
    friend std::ostream& operator << <T,U> (std::ostream& o, Histogram<T,U>& histogram);
};

template <class X_AXIS, class Y_AXIS>
std::ostream& operator << (std::ostream& o, Histogram<X_AXIS,Y_AXIS>& histogram) {
    o << "Amount" << '\n';
    for ( Bin<X_AXIS,Y_AXIS>& b : histogram.bins )
        o << b << '\n';
    o << "\nToo Low = " << histogram.bin_too_lo << '\n';
    o << "Too High = " << histogram.bin_too_hi << '\n';
    return o;
}

///--------------------------------------------------------------------------------------

class integral_histogram {
    int min_ix;
    int max_ix;
    int upper_bound;
    std::vector<int> histogram;
    int total_count;
public:
    integral_histogram(int i_min, int i_max)
            : min_ix(i_min), max_ix(i_max), upper_bound(i_max - i_min), total_count(0) {
        for ( int ix = 0; ix < upper_bound; ++ix )
            histogram.push_back(0);
    }
    void increment_bucket(int which_bucket) {
        if ( which_bucket < min_ix || which_bucket > max_ix ) throw;
        which_bucket = which_bucket - min_ix;
        ++histogram[which_bucket];
        ++total_count;
    }
    int get_midpoint() {
        int half_way_count = total_count / 2;
        int running_count = 0;
        int ix = 0;
        for ( ; ix < upper_bound; ++ix ) {
            running_count += histogram[ix];
            if ( running_count >= half_way_count )
                break;
        }
        return ix + min_ix;
    }
};

#endif //MONTECARLO_HISTOGRAM_H
