cmake_minimum_required(VERSION 3.15)
project(CacheAwareBenchmarks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories (modules)
add_subdirectory(false_sharing)
add_subdirectory(cache_alignment)
add_subdirectory(soa_vs_aos)
add_subdirectory(heap_vs_pool)
add_subdirectory(numa_access)