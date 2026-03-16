#pragma once

#include <immintrin.h>
#include <benchmark/benchmark.h>

#define N (1024 * 1024 * 64)

inline auto SumSimd() noexcept {
    int sum = 0;

#pragma omp parallel reduction(+:sum)
    {
        __m256i vSum0 = _mm256_setzero_si256();
        __m256i vSum1 = _mm256_setzero_si256();
        __m256i vSum2 = _mm256_setzero_si256();
        __m256i vSum3 = _mm256_setzero_si256();

        __m256i vOnes = _mm256_set1_epi32(1);

#pragma omp for nowait
        for(int i = 0; i < N; i += 32) {
            vSum0 = _mm256_add_epi32(vSum0, vOnes);
            vSum1 = _mm256_add_epi32(vSum1, vOnes);
            vSum2 = _mm256_add_epi32(vSum2, vOnes);
            vSum3 = _mm256_add_epi32(vSum3, vOnes);

            benchmark::DoNotOptimize(vSum0);
        }

        __m256i vTotal = _mm256_add_epi32(
            _mm256_add_epi32(vSum0, vSum1),
            _mm256_add_epi32(vSum2, vSum3)
        );

        alignas(32) int tmp[8];
        _mm256_store_si256((__m256i*)tmp, vTotal);

        int localSum = 0;
        for (int j : tmp) {
            localSum += j;
        }

        sum += localSum;
    }

    return sum;
}