#pragma once

#define N (1024 * 1024 * 64)

inline auto SumFast() noexcept {
    int sum = 0;

#pragma omp parallel
    {
        int localSum = 0;

#pragma omp for
        for(int i = 0; i < N; ++i) {
            ++localSum;
        }

#pragma omp critical
        sum += localSum;
    }

    return sum;
}
