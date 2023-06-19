#ifndef BASE_H_
#define BASE_H_

#include <stdexcept>

namespace indexsort
{
    /**
     * @brief Exception signalling that the length of permutation index iterable doesn't match the length of value iterable.
     */
    struct length_mismatch_error : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };
};

#endif
