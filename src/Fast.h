#pragma once

#include <benchmark/export.h>
#include <benchmark/utils.h>

#define N (1024 * 1024 * 64)

inline auto SumFast() noexcept -> int {
    int sum = 0;

#pragma omp parallel
    {
        int localSum = 0;

#pragma omp for
        for (int i = 0; i < N; ++i) {
            ++localSum;
            benchmark::DoNotOptimize(localSum);
        }

#pragma omp critical
        sum += localSum;
    }

    return sum;
}
