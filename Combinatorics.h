//
// Created by svale on 10/14/2021.
//

#ifndef MONTECARLO_COMBINATORICS_H
#define MONTECARLO_COMBINATORICS_H

#include <vector>
#include <functional>

/**
 * permutations_with_repetition
 * @tparam T - type of element, typically int, char, unsigned
 * @param symbol - sorted symbol to be selected from to form permutations, combinations, etc.
 * @param index - the index of the permutation/combination element [0..length-1]
 * @param prior_elements - suggestive of what is to be considered which is only elements prior to the index
 * @return always returns true for permutations_with_repetition
 */

template <typename T>
bool permutations_with_repetition(T symbol, int index, std::vector<T>& prior_elements)
{
    return true;
}

/**
 * permutations_without_repetition
 * @tparam T - type of element, typically int, char, unsigned
 * @param symbol - sorted symbol to be selected from to form permutations, combinations, etc.
 * @param index - the index of the permutation/combination element [0..length-1]
 * @param prior_elements - suggestive of what is to be considered which is only elements prior to the index
 * @return false if the current element is equal to a prior element
 */

template <typename T>
bool permutations_without_repetition(T symbol, int index, std::vector<T>& prior_elements)
{
    for (int ix = index-1; ix >= 0; --ix)
        if (symbol == prior_elements[ix])
            return false;
    return true;
}

/**
 * combinations_with_repetition
 * @tparam T - type of element, typically int, char, unsigned
 * @param symbol - sorted symbol to be selected from to form permutations, combinations, etc.
 * @param index - the index of the permutation/combination element [0..length-1]
 * @param prior_elements - suggestive of what is to be considered which is only elements prior to the index
 * @return false if the current element is less than a prior element
 */

template <typename T>
bool combinations_with_repetition(T symbol, int index, std::vector<T>& prior_elements)
{
    for (int ix = index-1; ix >= 0; --ix)
        if (symbol < prior_elements[ix])
            return false;
    return true;
}

/**
 * combinations_without_repetition
 * @tparam T - type of element, typically int, char, unsigned
 * @param symbol - sorted symbol to be selected from to form permutations, combinations, etc.
 * @param index - the index of the permutation/combination element [0..length-1]
 * @param prior_elements - suggestive of what is to be considered which is only elements prior to the index
 * @return false if the current element is less than or equal to a prior element
 */

template <typename T>
bool combinations_without_repetition(T symbol, int index, std::vector<T>& prior_elements)
{
    for (int ix = index-1; ix >= 0; --ix)
        if (symbol <= prior_elements[ix])
            return false;
    return true;
}

/**
 * create_combinatorial_element_set
 * Constructs a sequence of permutations or combinations depending on what is provided in the last parameter.
 * (Typically a selection function such as combinations_without_repetition is intended to be placed there).
 * Further selection is provided in the "select" parameter, e.g., see Motzkin Numbers example from Praxis.
 * Index is intended to be 0 on first call (create_combinatorial_element_set is recursive, going from index 0
 * to length-1).  The symbol set is also to consist of unique elements.
 * @tparam T - type of element, typically int, char, unsigned
 * @param symbols - sorted symbol set of elements to be selected from to form permutations, combinations, etc.
 * @param permutation_set - calculated permutations/combinations are stored here
 * @param permutation - the currently formed permutation/combination is stored here
 * @param index - the index of the permutation/combination element [0..length-1]
 * @param length - the length of the permutation/combination
 * @param select - user function to perform selection of permutation/combination
 * @param comparison_predicate - selection predicate typically using above library functions to produce desired set
 */

template <typename T>
void create_combinatorial_element_set(std::vector<T>& symbols,
                                         std::vector<std::vector<T>>& permutation_set,
                                         std::vector<T>& permutation,
                                         const int index,
                                         const int length,
                                         bool select(std::vector<T>& test_permutation),
                                         std::function<bool(T,int, std::vector<T>&)> comparison_predicate)
{
    if (index == length) return;

    for (T sym : symbols) {
        if (permutation.size() < index + 1)
            permutation.push_back(sym);
        else
            permutation[index] = sym;
        if (comparison_predicate(sym, index, permutation)) {
            create_combinatorial_element_set<T>(symbols, permutation_set, permutation, index + 1, length, select, comparison_predicate);
            if (index == length - 1 && select(permutation))

                permutation_set.push_back(permutation);
        }
    }
}

#endif //MONTECARLO_COMBINATORICS_H
