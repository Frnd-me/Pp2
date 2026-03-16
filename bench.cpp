#include "fast.h"
#include "fastest.h"
#include "medium.h"
#include "simd.h"
#include "slow.h"

#include <benchmark/registration.h>
#include <benchmark/state.h>

static void BM_SumFast(benchmark::State& state) noexcept {
    for (auto _ : state) {
        SumFast();
    }
}
BENCHMARK(BM_SumFast);

static void BM_SumFastest(benchmark::State& state) noexcept {
    for (auto _ : state) {
        SumFastest();
    }
}
BENCHMARK(BM_SumFastest);

static void BM_SumMedium(benchmark::State& state) noexcept {
    for (auto _ : state) {
        SumMedium();
    }
}
BENCHMARK(BM_SumMedium);

static void BM_SumSimd(benchmark::State& state) noexcept {
    for (auto _ : state) {
        SumSimd();
    }
}
BENCHMARK(BM_SumSimd);

static void BM_SumSlow(benchmark::State& state) noexcept {
    for (auto _ : state) {
        SumSlow();
    }
}
BENCHMARK(BM_SumSlow);

BENCHMARK_MAIN();