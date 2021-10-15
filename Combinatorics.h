//
// Created by svale on 10/14/2021.
//

#ifndef MONTECARLO_COMBINATORICS_H
#define MONTECARLO_COMBINATORICS_H

template <typename T>
void create_permutations(std::vector<T>& symbols,
                         std::vector<std::vector<T>>& permutation_set,
                         std::vector<T>& permutation,
                         const int index,
                         const int length,
                         bool filter(std::vector<T>& test_permutation))
{
    if (index == length) return;

    for (T sym : symbols) {
        if (permutation.size() < index + 1)
            permutation.push_back(sym);
        permutation[index] = sym;
        create_permutations(symbols, permutation_set, permutation, index + 1, length, filter);
        if (index == length - 1 &&
            permutation.size() == length  &&
            filter(permutation)) {
            permutation_set.push_back(permutation);
        }
    }
}


#endif //MONTECARLO_COMBINATORICS_H
