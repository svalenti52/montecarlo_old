/**
 * \file Histogram.h
 * \date 29-Jun-2017
 *
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

template <typename T, typename U>
class Bin
{
public:
    T right_edge_interval;
    T size_interval;

    U amount;

    int index;

public:
    Bin(int i_index, T i_right_edge_interval, T i_size) :
            index(i_index),
            right_edge_interval(i_right_edge_interval),
            size_interval(i_size),
            amount(0) {}

    bool inc_count_if_less_equal(T v)
    {
        if ( v <= right_edge_interval )
        {
            amount = amount + 1;
            return true;
        }
        return false;
    }

    void add_amount(U added_amount) {
        amount += added_amount;
    }

    friend std::ostream& operator << <>(std::ostream& o, Bin<T,U>& b);
};

template <typename T, typename U>
std::ostream& operator <<(std::ostream& o, Bin<T,U>& b)
{
    o << b.index << "=" << b.amount << " ";
    return o;
}

///-------------------------------------------------------------------------------------

template <class T, class U>
class Histogram;

template <class T, class U>
std::ostream& operator << (std::ostream&, Histogram<T,U>&);

template <class T, class U>
class Histogram {
    T lower_bound_left_edge;
    T upper_bound_right_edge;
    int nr_bins;
    T bin_width;
    std::vector<Bin<T,U>> bins;

    U total_amount;
public:
    Histogram(T i_lower_bound_left_edge,
            T i_upper_bound_right_edge,
            int i_bin_width) :
            lower_bound_left_edge(i_lower_bound_left_edge),
            upper_bound_right_edge(i_upper_bound_right_edge),
            bin_width(i_bin_width),
            total_amount(0)
    {
        nr_bins = (upper_bound_right_edge - lower_bound_left_edge) / bin_width;
        for ( int ix = 0; ix < nr_bins; ++ix )
            bins.push_back(Bin<T,U>(ix, lower_bound_left_edge+bin_width, bin_width));
    }

    void increment_bucket(int which_bin) {
        int adjusted_index = which_bin - (lower_bound_left_edge + bin_width);
        if ( adjusted_index < 0 || adjusted_index >= nr_bins ) throw;
        bins[adjusted_index].amount += 1;
        total_amount += 1;
    }

    int get_midpoint() {
        U half_way_count = total_amount / 2;
        U running_count = 0;
        int ix = 0;
        for ( ix; ix < nr_bins; ++ix ) {
            running_count += bins[ix].amount;
            if ( running_count >= half_way_count )
                break;
        }
        return ix + lower_bound_left_edge + bin_width;
    }

    friend std::ostream& operator << <> (std::ostream& o, Histogram<T,U>& histogram);
};

template <class T, class U>
std::ostream& operator << (std::ostream& o, Histogram<T,U>& histogram) {
    for ( Bin<T,U>& b : histogram.bins )
        o << b;
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
        for ( ix; ix < upper_bound; ++ix ) {
            running_count += histogram[ix];
            if ( running_count >= half_way_count )
                break;
        }
        return ix + min_ix;
    }
};

#endif //MONTECARLO_HISTOGRAM_H
