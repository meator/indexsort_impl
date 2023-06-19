#ifndef BOOST_INDEX_APPLY_SORT2_
#define BOOST_INDEX_APPLY_SORT2_

#include <vector>
#include <algorithm>
#include <boost/algorithm/apply_permutation.hpp>

#include "base.hpp"

namespace indexsort
{
/**
 * @brief Variation of @ref boost_index_apply_sort.
 *
 * This algorithm behaves like @ref boost_index_apply_sort but it sorts a local copy
 * of index, copies it to `index_begin` and then it applies it.
 *
 * @throws indexsort::length_mismatch_error If `std::distance(value_begin, value_end) != std::distance(index_begin, index_end)`.
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void boost_index_apply_sort2(RandomIt1 value_begin, RandomIt1 value_end, RandomIt2 index_begin, RandomIt2 index_end, Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::vector<index_val_type> temp(index_begin, index_end);

    std::sort(temp.begin(), temp.end(), [&value_begin, &cmp](const index_val_type & a, const index_val_type & b)
    {
        return cmp(value_begin[a], value_begin[b]);
    });

    std::copy(temp.begin(), temp.end(), index_begin);

    boost::algorithm::apply_permutation(value_begin, value_end, temp.begin(), temp.end());
}
};

#endif
