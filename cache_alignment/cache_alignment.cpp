// -----------------------------------------------------------
// PROBLEM – CACHE LINE ALIGNMENT
// -----------------------------------------------------------

// 1. WHAT IS THE PROBLEM?
/*
   When a struct spans across two cache lines (typically 64 bytes each),
   accessing it can force the CPU to load two cache lines instead of one.

   This results in:
   - More memory bandwidth usage
   - Higher latency
   - Possible partial writes and cache inefficiencies
*/

// 2. WHY DOES THIS HAPPEN?
/*
   Modern CPUs fetch data in chunks called cache lines.
   If your struct isn't aligned properly, its fields may cross
   into a second cache line, making access more expensive.
*/

// 3. HOW DO WE FIX IT?
/*
   Use alignas(64) to align structs to cache line boundaries.

   This ensures:
   - Struct starts on a fresh cache line
   - No crossing into adjacent cache blocks
*/

// 4. IS MEMORY BEING WASTED?
/*
   Slightly yes, but in HFT latency-sensitive systems, we trade
   memory for performance every time.
*/



#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>     // For aligned_alloc (C++17)
#include <cstring>     // For memset
#include <cassert>

constexpr size_t NUM_STRUCTS = 1'000'000;
constexpr size_t NUM_ITERATIONS = 100;
constexpr size_t CACHE_LINE_SIZE = 64;

// unaligned
struct UnalignedStruct {
    int data[16]; // 64 bytes
};

// aligned
struct alignas(CACHE_LINE_SIZE) AlignedStruct {
    int data[16]; // 64 bytes
};


template<typename T>
long long benchmarkAccess(T* arr, size_t count, const std::string& label) {
    volatile long long sum = 0; 

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t iter = 0; iter < NUM_ITERATIONS; ++iter) {
        for (size_t i = 0; i < count; ++i) {
            for (int j = 0; j < 16; ++j) {
                sum += arr[i].data[j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << label << " took: " << duration << " ms, dummy sum: " << sum << "\n";
    return duration;
}

int main() {
    std::cout << "🔍 Testing cache line alignment impact...\n";


    UnalignedStruct* unalignedArr = new UnalignedStruct[NUM_STRUCTS];
    std::memset(unalignedArr, 0, sizeof(UnalignedStruct) * NUM_STRUCTS);


    void* rawPtr = std::aligned_alloc(CACHE_LINE_SIZE, sizeof(AlignedStruct) * NUM_STRUCTS);
    assert(rawPtr != nullptr && "aligned_alloc failed");
    AlignedStruct* alignedArr = reinterpret_cast<AlignedStruct*>(rawPtr);
    std::memset(alignedArr, 0, sizeof(AlignedStruct) * NUM_STRUCTS);

  
    auto unalignedTime = benchmarkAccess(unalignedArr, NUM_STRUCTS, "❌ Unaligned access");
    auto alignedTime = benchmarkAccess(alignedArr, NUM_STRUCTS, "✅ Aligned access");

    delete[] unalignedArr;
    std::free(alignedArr);

    return 0;
}
