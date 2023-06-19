#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include "vector_pair_sort.hpp"
#include "vector_pair_sort2.hpp"
#include "double_sort.hpp"
#include "boost_index_apply_sort.hpp"
#include "boost_index_apply_sort2.hpp"
#include "permutate_in_place_sort.hpp"
#include <algorithm>
#include <random>

constexpr int length_of_values = 1'000'000;

using namespace indexsort;

TEST_CASE("Benchmark sorting integers of all algorithms", "[!benchmark]") {
    auto rng_seed = Catch::getSeed();
    std::mt19937 gen(rng_seed);

    std::vector<int> values_orig(length_of_values);

    using limits = std::numeric_limits<int>;
    std::uniform_int_distribution<> distrib(limits::min(), limits::max());

    // Initialize values with random numbers.
    std::generate(values_orig.begin(), values_orig.end(), [&gen,&distrib](){ return distrib(gen); });

    std::vector<int> index_orig(length_of_values);
    std::iota(index_orig.begin(), index_orig.end(), 0);

    auto cmp = std::less<int>();

    auto values(values_orig);
    auto index(index_orig);
    BENCHMARK("vector pair sort") {
        return vector_pair_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    // We must reset vales and index after each benchmark.
    values = values_orig;
    index = index_orig;
    BENCHMARK("vector pair sort 2") {
        return vector_pair_sort2(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("double sort") {
        return double_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("boost index apply sort") {
        return boost_index_apply_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("boost index apply sort 2") {
        return boost_index_apply_sort2(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("permutate in place sort") {
        return permutate_in_place_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };
}

TEST_CASE("Benchmark sorting doubles of all algorithms", "[!benchmark]") {
    auto rng_seed = Catch::getSeed();
    std::mt19937 gen(rng_seed);

    // Initialize values with random numbers.
    std::vector<double> values_orig(length_of_values);

    std::uniform_int_distribution<> distrib(0, 1);

    std::generate(values_orig.begin(), values_orig.end(), [&gen,&distrib](){ return distrib(gen); });

    std::vector<int> index_orig(length_of_values);
    std::iota(index_orig.begin(), index_orig.end(), 0);

    auto cmp = std::less<double>();

    auto values(values_orig);
    auto index(index_orig);
    BENCHMARK("vector pair sort") {
        return vector_pair_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("vector pair sort 2") {
        return vector_pair_sort2(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("double sort") {
        return double_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("boost index apply sort") {
        return boost_index_apply_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("boost index apply sort 2") {
        return boost_index_apply_sort2(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };

    values = values_orig;
    index = index_orig;
    BENCHMARK("permutate in place sort") {
        return permutate_in_place_sort(values.begin(), values.end(), index.begin(), index.end(), cmp);
    };
}
