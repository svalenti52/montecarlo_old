//
// Created by svale on 11/6/2021.
//

#ifndef MONTECARLO_PRIMES_H
#define MONTECARLO_PRIMES_H

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

class Primes_List
{
    std::vector<bool> prime_list;
public:
    explicit Primes_List(uint64_t upper_bound)
    {
        auto sqrt_ub = static_cast<uint64_t>(std::ceil(std::sqrt(upper_bound)));
        for (int ix = 0; ix < upper_bound; ++ix)
            prime_list.push_back(true);
        prime_list[0] = false;
        prime_list[1] = false;
        for (int ix = 2; ix < sqrt_ub; ++ix) {
            if (prime_list[ix])
                for (int jx = ix * ix; jx < upper_bound; jx += ix)
                    prime_list[jx] = false;

        }
    }

    bool is_prime(uint64_t number) {
        return prime_list[number];
    }
};

class Primes
{
    std::vector<uint64_t> primes;
public:
    explicit Primes(Primes_List primesList, uint64_t upper_bound)
    {
        uint64_t ix = 0;
        while (ix < upper_bound)
        {
            if (primesList.is_prime(ix))
            {
                primes.push_back(ix);
            }
            ++ix;
        }
    }

    std::vector<uint64_t>::iterator get_pos(uint64_t index)
    {
        return primes.begin() + index;
    }

    uint64_t get_ith_prime(uint64_t index)
    {
        return primes[index];
    }

    void list_primes(uint64_t ub = 0)
    {
        if (ub == 0) {
            for (uint64_t d: primes)
                std::cout << d << ", ";
        }
        else {
            for (int ix = 0; ix < ub; ++ix)
                std::cout << ix+1 << ". " << primes[ix] << ", ";
        }

        std::cout << '\n';
        std::cout << "Primes size = " << primes.size() << '\n';
    }
};

class Partial_Primes_List
{
    std::vector<bool> prime_list;
public:
    explicit Partial_Primes_List(uint64_t upper_bound, uint64_t number_primes_to_sieve)
    {
        // auto sqrt_ub = static_cast<uint64_t>(std::ceil(std::sqrt(upper_bound)));
        for (int ix = 0; ix <= upper_bound; ++ix)
            prime_list.push_back(true);
        prime_list[0] = false;
        prime_list[1] = false;
        uint64_t prime_index = 2;
        uint64_t prime_count = 0;
        while (prime_count < number_primes_to_sieve) {
            if (prime_list[prime_index]) {
                ++prime_count;
                for (uint64_t ix = prime_index * prime_index; ix <= upper_bound; ix += prime_index)
                    prime_list[ix] = false;
            }
            ++prime_index;
        }
    }

    uint64_t get_initial_prime_count()
    {
        auto prime_list_count = [](const std::_Bit_reference v)
        {
            return v;
        };
        return std::count_if(prime_list.begin(), prime_list.end(), prime_list_count);
    }

    void list_potential_primes()
    {
        for (int ix = 0; ix < prime_list.size(); ++ix)
            if (prime_list[ix])
                std::cout << ix << ", ";
        std::cout << '\n';
    }
};

template <typename T>
bool is_numeric_palindrome(T number)
{
    std::string s = std::to_string(number);
    return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

template <typename T>
bool is_numeric_calc_palindrome(T number)
{
    T straight = number;
    T reversed = 0;

    while(number != 0)
    {
        reversed = (reversed * 10) + (number % 10);
        number = number / 10;
    }
    if (straight == reversed)
        return true;
    return false;
}

template <typename T>
T numeric_digits_reversed(T number)
{
    T reversed = 0;

    while(number != 0)
    {
        reversed = (reversed * 10) + (number % 10);
        number = number / 10;

    }
    return reversed;
}

template <typename T>
void digits_from_number(T number, std::vector<T>& digits)
{
    T rev_number = numeric_digits_reversed(number);
    while (rev_number != 0)
    {
        T digit = rev_number % 10;
        digits.push_back(digit);
        rev_number /= 10;
    }
}

#endif //MONTECARLO_PRIMES_H
