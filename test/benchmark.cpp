#include <catch2/benchmark/catch_benchmark.hpp>
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

constexpr int length_of_values = 1'000'000;

using namespace indexsort;

template <typename RandomIt1, typename RandomIt2, typename Compare>
static void sort_index_by_values(RandomIt1 values_begin,
                                 [[maybe_unused]] RandomIt1 values_end,
                                 RandomIt2 index_begin,
                                 RandomIt2 index_end,
                                 Compare cmp)
{
    using index_val_type = typename std::iterator_traits<RandomIt2>::value_type;

    std::sort(
      index_begin, index_end,
      [&values_begin, &cmp](const index_val_type & a, const index_val_type & b)
      { return cmp(values_begin[a], values_begin[b]); });
}

TEST_CASE("Benchmark sorting integers of all algorithms", "[!benchmark]")
{
    auto rng_seed = Catch::getSeed();
    std::mt19937 gen(rng_seed);

    std::vector<int> values_orig(length_of_values);

    using limits = std::numeric_limits<int>;
    std::uniform_int_distribution<> distrib(limits::min(), limits::max());

    // Initialize values with random numbers.
    std::generate(values_orig.begin(), values_orig.end(),
                  [&gen, &distrib]() { return distrib(gen); });

    std::vector<int> index_orig(length_of_values);
    std::iota(index_orig.begin(), index_orig.end(), 0);

    auto cmp = std::less<int>();

    REQUIRE(values_orig.size() == length_of_values);
    REQUIRE(index_orig.size() == length_of_values);

    BENCHMARK_ADVANCED(
      "sort values (this isn't index sort but it's put here for comparison)")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);

        meter.measure([&values, &cmp]
                      { return std::sort(values.begin(), values.end(), cmp); });
    };

    BENCHMARK_ADVANCED(
      "sort index by values (this isn't index sort but it's put here for "
      "comparison)")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return sort_index_by_values(values.begin(), values.end(),
                                          index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("vector pair sort")(Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return vector_pair_sort(values.begin(), values.end(),
                                      index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("vector pair sort 2")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return vector_pair_sort2(values.begin(), values.end(),
                                       index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("double sort")(Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return double_sort(values.begin(), values.end(), index.begin(),
                                 index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("boost index apply sort")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return boost_index_apply_sort(values.begin(), values.end(),
                                            index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("boost index apply sort 2")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return boost_index_apply_sort2(values.begin(), values.end(),
                                             index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("permutate in place sort")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return permutate_in_place_sort(values.begin(), values.end(),
                                             index.begin(), index.end(), cmp);
          });
    };
}

TEST_CASE("Benchmark sorting doubles of all algorithms", "[!benchmark]")
{
    auto rng_seed = Catch::getSeed();
    std::mt19937 gen(rng_seed);

    // Initialize values with random numbers.
    std::vector<double> values_orig(length_of_values);

    std::uniform_real_distribution<> distrib(0.0, 1.0);

    std::generate(values_orig.begin(), values_orig.end(),
                  [&gen, &distrib]() { return distrib(gen); });

    std::vector<int> index_orig(length_of_values);
    std::iota(index_orig.begin(), index_orig.end(), 0);

    auto cmp = std::less<double>();

    REQUIRE(values_orig.size() == length_of_values);
    REQUIRE(index_orig.size() == length_of_values);

    BENCHMARK_ADVANCED(
      "sort values (this isn't index sort but it's put here for comparison)")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);

        meter.measure([&values, &cmp]
                      { return std::sort(values.begin(), values.end(), cmp); });
    };

    BENCHMARK_ADVANCED(
      "sort index by values (this isn't index sort but it's put here for "
      "comparison)")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return sort_index_by_values(values.begin(), values.end(),
                                          index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("vector pair sort")(Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return vector_pair_sort(values.begin(), values.end(),
                                      index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("vector pair sort 2")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return vector_pair_sort2(values.begin(), values.end(),
                                       index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("double sort")(Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return double_sort(values.begin(), values.end(), index.begin(),
                                 index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("boost index apply sort")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return boost_index_apply_sort(values.begin(), values.end(),
                                            index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("boost index apply sort 2")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return boost_index_apply_sort2(values.begin(), values.end(),
                                             index.begin(), index.end(), cmp);
          });
    };

    BENCHMARK_ADVANCED("permutate in place sort")
    (Catch::Benchmark::Chronometer meter)
    {
        auto values(values_orig);
        auto index(index_orig);

        meter.measure(
          [&values, &index, &cmp]
          {
              return permutate_in_place_sort(values.begin(), values.end(),
                                             index.begin(), index.end(), cmp);
          });
    };
}
