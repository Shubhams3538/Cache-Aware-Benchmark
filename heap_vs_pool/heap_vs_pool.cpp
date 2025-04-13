// ---------------------------------------------------------
// MODULE – MEMORY POOL VS HEAP ALLOCATOR
// ---------------------------------------------------------

// 1. WHAT’S THE PROBLEM?
/*
   - Dynamic allocation using `new` or `malloc` comes from the heap.
   - Heap is slow and can become fragmented over time.
   - Objects allocated on the heap may be far apart in memory.
   - This hurts spatial locality → more cache misses.
   - Heap introduces unpredictable latency – a big NO for HFT.
*/


// 2. HOW DO WE FIX THIS?
/*
   - Use a custom memory pool: allocate memory once at the start.
   - Divide it into equal-sized blocks for objects.
   - Reuse these blocks instead of constantly asking the heap.
   - Objects remain close in memory → better cache locality.
   - No fragmentation, deterministic allocation speed.
*/


// 3. HOW DO WE DO THAT?
/*
   - Allocate memory using `std::aligned_alloc`.
   - Cast the raw memory to your object type:
     e.g., Trade* trades = static_cast<Trade*>(memory);

   - Construct objects using placement new:
     new (&trades[i]) Trade{...};

   - Manually destroy them with destructor:
     trades[i].~Trade();

   This avoids `new`/`delete` completely during runtime.
*/


// 4. WHY IS THIS IMPORTANT IN HFT?
/*
   - HFT systems handle millions of events per second.
   - Every nanosecond matters – latency spikes are unacceptable.
   - Heap is unpredictable and slow.
   - Memory pools offer:
     ✅ Low-latency memory access
     ✅ Improved cache locality
     ✅ No fragmentation
     ✅ Predictable performance
*/

#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <cstring>

constexpr size_t NUM_OBJECTS = 10'000'000;

struct Trade {
    int id;
    double price;
    int quantity;
};

// Heap Allocation Benchmark

void heapAllocationBenchmark() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Trade*> trades;
    for (size_t i = 0; i < NUM_OBJECTS; ++i) {
        trades.push_back(new Trade{static_cast<int>(i), 100.5 + i, 10});

    }
    for (auto t : trades) delete t;

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "❌ Heap Allocation took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}


// Memory Pool Benchmark

void poolAllocationBenchmark() {
    auto start = std::chrono::high_resolution_clock::now();

    void* memory = std::malloc(sizeof(Trade) * NUM_OBJECTS);
    Trade* trades = static_cast<Trade*>(memory);

    for (size_t i = 0; i < NUM_OBJECTS; ++i) {
        new (&trades[i]) Trade{static_cast<int>(i), 100.5 + i, 10};

    }

    for (size_t i = 0; i < NUM_OBJECTS; ++i) {
        trades[i].~Trade(); // Manually call destructor
    }

    std::free(memory);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "✅ Pool Allocation took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    std::cout << "🚀 Comparing Heap vs Memory Pool Allocation...\n\n";
    heapAllocationBenchmark();
    poolAllocationBenchmark();
    return 0;
}
