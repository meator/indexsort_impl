#ifndef DOUBLE_SORT_
#define DOUBLE_SORT_

#include <vector>
#include <algorithm>

#include "base.hpp"

namespace indexsort
{
/**
 * `std::sort` index with custom comparator that uses values contents instead of index contents. Then `std::sort` values
 * directly with `cmp`.
 *
 * @throws indexsort::length_mismatch_error If `std::distance(value_begin, value_end) != std::distance(index_begin, index_end)`.
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void double_sort(RandomIt1 value_begin, RandomIt1 value_end, RandomIt2 index_begin, RandomIt2 index_end, Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::sort(index_begin, index_end, [&value_begin, &cmp](const index_val_type & a, const index_val_type & b)
    {
        return cmp(value_begin[a], value_begin[b]);
    });
    std::sort(value_begin, value_end, cmp);
}
};

#endif
