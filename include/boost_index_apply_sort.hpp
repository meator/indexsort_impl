#ifndef BOOST_INDEX_APPLY_SORT_
#define BOOST_INDEX_APPLY_SORT_

#include <algorithm>
#include <boost/algorithm/apply_permutation.hpp>
#include <vector>

#include "base.hpp"

namespace indexsort
{
/**
 * `std::sort` index with custom comparator that uses values contents instead of
 * index contents. Then use `boost::algorithm::apply_permutation()` to sort
 * values. This approach doesn't require calling `std::sort()` twice, it uses
 * the information from `std::sort`ing the permutation index to sort values.
 *
 * `boost::algorithm::apply_permutation()` destroys the permutation index in the
 * process of applying it. This algorithm therefore has to make a copy of the
 * index to give it to `apply_permutation()`.
 *
 * Boost's `boost::algorithm::apply_permutation()` is inspired by the
 * https://devblogs.microsoft.com/oldnewthing/20170102-00/?p=95095 article and
 * the following articles.
 *
 * @throws indexsort::length_mismatch_error If `std::distance(value_begin,
 * value_end) != std::distance(index_begin, index_end)`.
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void boost_index_apply_sort(RandomIt1 value_begin,
                            RandomIt1 value_end,
                            RandomIt2 index_begin,
                            RandomIt2 index_end,
                            Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::sort(
      index_begin, index_end,
      [&value_begin, &cmp](const index_val_type & a, const index_val_type & b)
      { return cmp(value_begin[a], value_begin[b]); });

    std::vector<index_val_type> temp(index_begin, index_end);

    boost::algorithm::apply_permutation(value_begin, value_end, temp.begin(),
                                        temp.end());
}
};  // namespace indexsort

#endif
