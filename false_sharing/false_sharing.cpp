// ---------------------------------------------
// PROBLEM – FALSE SHARING
// ---------------------------------------------

// 1. WHAT IS FALSE SHARING?
/*
   Happens when two threads write to different variables,
   but those variables lie on the same cache line (64 bytes).

   Even though the threads are not sharing the data logically,
   the CPU thinks they are because they hit the same cache block.

   So, when one thread writes to its variable,
   it invalidates the cache line in the other thread’s CPU,
   forcing it to fetch it again – this back-and-forth is expensive.

   This leads to a lot of cache invalidation and ownership transfer,
   wasting CPU cycles and slowing things down.
*/


// 2. HOW DO WE FIX THIS?
/*
   We make sure that each thread’s data is on a different cache line.
   That way, there's no overlap, and no false sharing.
*/


// 3. HOW DO WE DO THAT?
/*
   Two ways:
   - Add padding (dummy space) so two variables don’t end up on the same line
   - Use alignas(64) to force each variable to start on its own cache line
*/


// 4. AREN'T WE WASTING SPACE?
/*
   Yes, we are using more memory than needed.
   But in HFT, latency is way more important than saving space.

   So we trade off memory for speed — and that’s a good deal.
*/


// RUN THIS CODE AND YOU WILL SEE THE DIFFERENCE IN CODE WITH FALSE SHARING AND NO FALSE SHARING CODE RUNNING IT FOR 1 BILLION OPERATIONS 
// GOT 2057ms in false sharing and 1020ms in padded version.


#include <iostream>
#include <thread>
#include <chrono>

constexpr size_t NUM_ITERATIONS = 1'000'000'000;

// 🚫 Structure with false sharing
struct SharedDataFalseSharing {
    int x;
    int y;
};

// ✅ Structure with padding to prevent false sharing
struct alignas(64) SharedDataNoFalseSharing {
    int x;
    char padding[64 - sizeof(int)];
    int y;
};

// Make them global and volatile to prevent compiler optimization
volatile SharedDataFalseSharing dataFalse{0, 0};
volatile SharedDataNoFalseSharing dataNoFalse{0, {}, 0};

void runFalseSharingBenchmark() {
    auto threadFunc1 = []() {
        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            dataFalse.x++;
        }
    };

    auto threadFunc2 = []() {
        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            dataFalse.y++;
        }
    };

    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);
    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "❌ Time taken with FALSE SHARING: " << duration << " ms\n";
}

void runNoFalseSharingBenchmark() {
    auto threadFunc1 = []() {
        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            dataNoFalse.x++;
        }
    };

    auto threadFunc2 = []() {
        for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
            dataNoFalse.y++;
        }
    };

    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(threadFunc1);
    std::thread t2(threadFunc2);
    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "✅ Time taken with NO FALSE SHARING (padded): " << duration << " ms\n";
}

int main() {
    runFalseSharingBenchmark();
    runNoFalseSharingBenchmark();
    return 0;
}








