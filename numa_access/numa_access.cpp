// ---------------------------------------------
// PROBLEM – NUMA MEMORY ACCESS LATENCY
// ---------------------------------------------

// 1. WHAT IS NUMA?
/*
   NUMA (Non-Uniform Memory Access) is a memory architecture used in multi-CPU systems.
   Each CPU has its own local memory (fast access) and can also access memory from other CPUs (slower).

   - Local access: CPU accesses memory attached to itself.
   - Remote access: CPU accesses memory attached to another CPU/socket — incurs latency.

   In HFT, even microsecond-level latency can make or break trades,
   so it’s critical to avoid remote memory access when performance matters.
*/


// 2. WHY DOES THIS MATTER?
/*
   If your thread runs on CPU 0 but accesses memory from CPU 1’s memory bank,
   it suffers higher latency — hurting performance.

   So memory locality isn’t just about cache — it’s also about NUMA zones.
*/


// 3. HOW DO WE FIX THIS?
/*
   We bind threads to specific NUMA nodes and allocate memory on the same node
   using the `libnuma` library (`numactl` in Linux).

   - numa_alloc_onnode: Allocate memory on a specific node
   - numa_run_on_node: Pin thread to a specific node
*/


// 4. HOW DO WE VERIFY IT?
/*
   Benchmark two scenarios:
   - Local memory access: Thread and memory on same node
   - Remote memory access: Thread on one node, memory from another

   Measure the latency difference between the two — expect local to be faster.
*/


// 5. SIDE NOTE:
   /*
      If your CPU has only 1 NUMA node, remote and local access will show similar timings.
      On real multi-socket servers, the difference is much more significant.
   */


#include <iostream>
#include <thread>
#include <vector>
#include <numa.h>
#include <chrono>

constexpr size_t NUM_ITERATIONS = 500'000'000;
constexpr size_t DATA_SIZE = 1024 * 1024;  // 1MB

void runBenchmark(void* memory, int node, const std::string& label) {
    numa_run_on_node(node);

    volatile char* data = reinterpret_cast<char*>(memory);
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
        data[i % DATA_SIZE]++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << label << " took: " << duration << " ms\n";
}

int main() {
    if (numa_available() == -1) {
        std::cerr << "NUMA is not available on this system.\n";
        return 1;
    }

    void* memory = numa_alloc_onnode(DATA_SIZE, 0);  // Allocate on node 0

    std::cout << "🔍 NUMA Memory Access Benchmark\n";

    runBenchmark(memory, 0, "✅ Local access (Node 0)");
    runBenchmark(memory, 1, "❌ Remote access (Node 1)");

    numa_free(memory, DATA_SIZE);
    return 0;
}
