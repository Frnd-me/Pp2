#pragma once

#include <benchmark/export.h>
#include <benchmark/utils.h>

#define N (1024 * 1024 * 64)

inline auto SumFastest() noexcept {
    int sum = 0;

#pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < N; ++i) {
        ++sum;
        benchmark::DoNotOptimize(sum);
    }

    return sum;
}