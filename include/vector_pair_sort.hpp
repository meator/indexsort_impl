#ifndef VECTOR_PAIR_SORT_
#define VECTOR_PAIR_SORT_

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "base.hpp"

/**
 * @brief Namespace containing all implementations of sort that return the permutation index.
 *
 * All functions in this namespace have the same signature. `std::distance(value_begin, value_end)` and
 * `std::distance(index_begin, index_end)` must be equal. If not, @ref indexsort::length_mismatch_error will be thrown.
 * The index iterable **must** be initialized with a sequence starting from 0 and continuing
 * to `std::distance(value_begin, value_end) - 1`.
 *
 * Instance of the `Compare` type is passed to `std::sort`, so `Compare` must fulfill requirements imposed by
 * `std::sort`s `Compare`.
 */
namespace indexsort
{
/**
 * Convert values into `std::vector` of `std::pair` containing the value and it's index. Value is copied into the new vector.
 * Then `std::sort` this vector with a custom comparator that invokes `cmp()` on the values of pairs. The result is then
 * reconstructed from the sorted vector.
 *
 * @throws indexsort::length_mismatch_error If `std::distance(value_begin, value_end) != std::distance(index_begin, index_end)`.
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void vector_pair_sort(RandomIt1 value_begin, RandomIt1 value_end, RandomIt2 index_begin, RandomIt2 index_end, Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using value_val_type = typename std::iterator_traits<RandomIt1>::value_type;
    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::vector<std::pair<value_val_type, index_val_type>> conversion;
    conversion.reserve(length);

    // n is the index. We don't use index_begin because calculating this is simpler. This also means
    // that vector_pair_sort() could be fed garbage in index_begin and it would still work.
    index_val_type n = 0;
    for (RandomIt1 i(value_begin); i != value_end; ++i)
        conversion.emplace_back(*i, n++);

    using pair_type = std::pair<value_val_type, index_val_type>;
    std::sort(conversion.begin(), conversion.end(), [&cmp](const pair_type & a, const pair_type & b)
    {
        return cmp(a.first, b.first);
    });

    using value_diff_type = typename std::iterator_traits<RandomIt1>::difference_type;

    for (value_diff_type i = 0; i < length; ++i)
    {
        value_begin[i] = conversion[i].first;
        index_begin[i] = conversion[i].second;
    }
}
};

#endif
