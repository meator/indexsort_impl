#ifndef PERMUTATE_IN_PLACE_SORT_
#define PERMUTATE_IN_PLACE_SORT_

#include <vector>
#include <algorithm>
#include <stdexcept>

#include "base.hpp"

namespace indexsort
{
/**
 * `std::sort` index with custom comparator that uses values contents instead of index contents. Then apply the permutation
 * index in place to values.
 *
 * This algorithm is taken from https://medium.com/@kevingxyz/permutation-in-place-8528581a5553
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void permutate_in_place_sort(RandomIt1 value_begin, RandomIt1 value_end, RandomIt2 index_begin, RandomIt2 index_end, Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::sort(index_begin, index_end, [&value_begin, &cmp](const index_val_type & a, const index_val_type & b)
    {
        return cmp(value_begin[a], value_begin[b]);
    });

    // We'll be using these two as if they were arrays. Rename them for convenience.
    auto & index = index_begin;
    auto & values = value_begin;

    using std::swap;

    for (index_val_type i = 0; i < length; ++i)
    {
        index_val_type index_to_swap = index[i];
        while (index_to_swap < i)
            index_to_swap = index[index_to_swap];
        swap(values[i], values[index_to_swap]);
    }
}
};

#endif
