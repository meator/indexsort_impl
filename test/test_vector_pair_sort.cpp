#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include "vector_pair_sort.hpp"

using namespace indexsort;

TEST_CASE("Test sorting", "[simple-index-sort]")
{
    std::vector<int> values({7, 45, 18, 33, 77, 96, 83, 80, 4, 51});
    std::vector<int> index({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::vector<int> result_index({8, 0, 2, 3, 1, 9, 4, 7, 6, 5});

    SECTION("Using std::less")
    {
        vector_pair_sort(values.begin(), values.end(), index.begin(),
                         index.end(), std::less<int>());

        REQUIRE(std::is_sorted(values.begin(), values.end()));
        REQUIRE(index == result_index);
    }

    SECTION("Using std::greater")
    {
        vector_pair_sort(values.begin(), values.end(), index.begin(),
                         index.end(), std::greater<int>());

        REQUIRE(
          std::is_sorted(values.begin(), values.end(), std::greater<int>()));
        REQUIRE(index ==
                std::vector(result_index.rbegin(), result_index.rend()));
    }
}

TEST_CASE("Test sorting empty containers", "[simple-index-sort]")
{
    std::vector<int> values;
    std::vector<int> index;

    vector_pair_sort(values.begin(), values.end(), index.begin(), index.end(),
                     std::less<int>());

    REQUIRE(values.empty());
    REQUIRE(index.empty());
}

TEST_CASE("Test sorting container with invalid length of index",
          "[simple-index-sort]")
{
    std::vector<int> values({7, 45, 18, 33, 77, 96, 83, 80, 4, 51});

    SECTION("Index vector larger than values")
    {
        std::vector<int> index({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        REQUIRE_THROWS_AS(
          vector_pair_sort(values.begin(), values.end(), index.begin(),
                           index.end(), std::less<int>()),
          indexsort::length_mismatch_error);
    }
    SECTION("Index vector smaller than values")
    {
        std::vector<int> index({0, 1, 2, 3, 4, 5, 6, 7, 8});
        REQUIRE_THROWS_AS(
          vector_pair_sort(values.begin(), values.end(), index.begin(),
                           index.end(), std::less<int>()),
          indexsort::length_mismatch_error);
    }
    SECTION("Index vector empty")
    {
        std::vector<int> index;
        REQUIRE_THROWS_AS(
          vector_pair_sort(values.begin(), values.end(), index.begin(),
                           index.end(), std::less<int>()),
          indexsort::length_mismatch_error);
    }
}

TEST_CASE("Test sorting with invalid index", "[simple-index-sort][!shouldfail]")
{
    std::vector<int> values({7, 45, 18, 33, 77, 96, 83, 80, 4, 51});
    std::vector<int> index({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    WARN(
      "The algorithms currently doesn't check the validity of the index. "
      "This test therefore fails.");
    REQUIRE_THROWS(vector_pair_sort(values.begin(), values.end(), index.begin(),
                                    index.end(), std::less<int>()));
}
