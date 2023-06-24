#ifndef VECTOR_PAIR_SORT2_
#define VECTOR_PAIR_SORT2_

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "base.hpp"

namespace indexsort
{
/**
 * @brief Variation of @ref vector_pair_sort.
 * This version of @ref vector_pair_sort uses iterators when copying values and
 * indexes from sorted vector. This implementation exists just to compare the
 * speed of the two approaches.
 *
 * @throws indexsort::length_mismatch_error If `std::distance(value_begin,
 * value_end) != std::distance(index_begin, index_end)`.
 */
template <typename RandomIt1, typename RandomIt2, typename Compare>
void vector_pair_sort2(RandomIt1 value_begin,
                       RandomIt1 value_end,
                       RandomIt2 index_begin,
                       RandomIt2 index_end,
                       Compare cmp)
{
    auto length = std::distance(value_begin, value_end);

    if (length != std::distance(index_begin, index_end))
        throw length_mismatch_error("Length of both iterables must match!");

    using value_val_type = typename std::iterator_traits<RandomIt1>::value_type;
    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::vector<std::pair<value_val_type, index_val_type>> conversion;
    conversion.reserve(length);

    // n is the index. We don't use index_begin because calculating this is
    // simpler. This also means that vector_pair_sort() could be fed garbage in
    // index_begin and it would still work.
    index_val_type n = 0;
    for (RandomIt1 i(value_begin); i != value_end; ++i)
        conversion.emplace_back(*i, n++);

    using pair_type = std::pair<value_val_type, index_val_type>;
    std::sort(conversion.begin(), conversion.end(),
              [&cmp](const pair_type & a, const pair_type & b)
              { return cmp(a.first, b.first); });

    for (auto vector_iter(conversion.begin()); vector_iter != conversion.end();
         ++vector_iter, ++value_begin, ++index_begin)
    {
        *value_begin = vector_iter->first;
        *index_begin = vector_iter->second;
    }
}
};  // namespace indexsort

#endif
