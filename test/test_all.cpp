#include <catch2/catch_get_random_seed.hpp>
#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <random>
#include "boost_index_apply_sort.hpp"
#include "boost_index_apply_sort2.hpp"
#include "double_sort.hpp"
#include "permutate_in_place_sort.hpp"
#include "vector_pair_sort.hpp"
#include "vector_pair_sort2.hpp"

/*
 * test_vector_pair_sort.hpp tests the correctness of vector_pair_sort(). Tests
 * in this file assume that it's correct (if it wouldn't, it will be catched in
 * test_vector_pair_sort.hpp). These tests generate vector of random numbers,
 * applies vector_pair_sort() and the tested algorithm and it compares the
 * result.
 */

using namespace indexsort;

TEST_CASE("Test sorting")
{
    constexpr int vector_length = 500;

    auto rng_seed = Catch::getSeed();
    std::mt19937 gen(rng_seed);

    // Initialize values with random numbers.
    std::vector<int> values(vector_length);

    using limits = std::numeric_limits<int>;
    std::uniform_int_distribution<> distrib(limits::min(), limits::max());

    std::generate(values.begin(), values.end(),
                  [&gen, &distrib]() { return distrib(gen); });

    // Initialize index with sequence.
    std::vector<int> index(values.size());
    std::iota(index.begin(), index.end(), 0);

    auto check_values(values);
    auto check_index(index);
    vector_pair_sort(check_values.begin(), check_values.end(),
                     check_index.begin(), check_index.end(), std::less<int>());

    auto cmp = std::less<int>();

    SECTION("Test vector pair sort 2")
    {
        vector_pair_sort2(values.begin(), values.end(), index.begin(),
                          index.end(), cmp);
    }
    SECTION("Test double sort")
    {
        double_sort(values.begin(), values.end(), index.begin(), index.end(),
                    cmp);
    }
    SECTION("Test boost index apply sort")
    {
        boost_index_apply_sort(values.begin(), values.end(), index.begin(),
                               index.end(), cmp);
    }
    SECTION("Test boost index apply sort 2")
    {
        boost_index_apply_sort2(values.begin(), values.end(), index.begin(),
                                index.end(), cmp);
    }
    SECTION("Test permutate in place sort")
    {
        permutate_in_place_sort(values.begin(), values.end(), index.begin(),
                                index.end(), cmp);
    }

    REQUIRE(values == check_values);
    REQUIRE(index == check_index);
}

TEST_CASE("Test sorting empty containers")
{
    std::vector<int> values;
    std::vector<int> index;

    auto cmp = std::less<int>();

    SECTION("Test vector pair sort 2")
    {
        vector_pair_sort2(values.begin(), values.end(), index.begin(),
                          index.end(), cmp);
    }
    SECTION("Test double sort")
    {
        double_sort(values.begin(), values.end(), index.begin(), index.end(),
                    cmp);
    }
    SECTION("Test boost index apply sort")
    {
        boost_index_apply_sort(values.begin(), values.end(), index.begin(),
                               index.end(), cmp);
    }
    SECTION("Test boost index apply sort 2")
    {
        boost_index_apply_sort2(values.begin(), values.end(), index.begin(),
                                index.end(), cmp);
    }
    SECTION("Test permutate in place sort")
    {
        permutate_in_place_sort(values.begin(), values.end(), index.begin(),
                                index.end(), cmp);
    }

    REQUIRE(values.empty());
    REQUIRE(index.empty());
}

TEST_CASE("Test sorting container with invalid length of index")
{
    std::vector<int> values({7, 45, 18, 33, 77, 96, 83, 80, 4, 51});

    auto cmp = std::less<int>();

    using iterator_type = decltype(values)::iterator;
    void (*function)(iterator_type, iterator_type, iterator_type, iterator_type,
                     std::less<int>);

    SECTION("Test vector pair sort 2")
    {
        function =
          vector_pair_sort2<decltype(values)::iterator,
                            decltype(values)::iterator, std::less<int>>;
    }
    SECTION("Test double sort")
    {
        function = double_sort<decltype(values)::iterator,
                               decltype(values)::iterator, std::less<int>>;
    }
    SECTION("Test boost index apply sort")
    {
        function =
          boost_index_apply_sort<decltype(values)::iterator,
                                 decltype(values)::iterator, std::less<int>>;
    }
    SECTION("Test boost index apply sort 2")
    {
        function =
          boost_index_apply_sort2<decltype(values)::iterator,
                                  decltype(values)::iterator, std::less<int>>;
    }
    SECTION("Test permutate in place sort")
    {
        function =
          permutate_in_place_sort<decltype(values)::iterator,
                                  decltype(values)::iterator, std::less<int>>;
    }

    std::vector<int> index_too_large({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    try
    {
        function(values.begin(), values.end(), index_too_large.begin(),
                 index_too_large.end(), cmp);
        FAIL(
          "Test with too large index: function didn't throw "
          "indexsort::length_mismatch_error.");
    }
    catch (indexsort::length_mismatch_error &)
    {
    }

    std::vector<int> index_too_small({0, 1, 2, 3, 4, 5, 6, 7, 8});
    try
    {
        function(values.begin(), values.end(), index_too_small.begin(),
                 index_too_small.end(), cmp);
        FAIL(
          "Test with too small index: function didn't throw "
          "indexsort::length_mismatch_error.");
    }
    catch (indexsort::length_mismatch_error &)
    {
    }

    std::vector<int> index_empty({0, 1, 2, 3, 4, 5, 6, 7, 8});
    try
    {
        function(values.begin(), values.end(), index_empty.begin(),
                 index_empty.end(), cmp);
        FAIL(
          "Test with empty index: function didn't throw "
          "indexsort::length_mismatch_error.");
    }
    catch (indexsort::length_mismatch_error &)
    {
    }
}
