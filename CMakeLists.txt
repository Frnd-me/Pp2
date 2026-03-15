cmake_minimum_required(VERSION 4.0)

project(Assignment2)

add_subdirectory(3rd/benchmark)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -march=native")
set(CMAKE_CXX_STANDARD 20)

add_executable(bench bench.cpp)

target_link_libraries(bench
    PRIVATE
        benchmark::benchmark
)