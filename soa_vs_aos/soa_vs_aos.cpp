// ---------------------------------------------
// PROBLEM – STRUCT LAYOUT (AoS vs SoA)
// ---------------------------------------------

// 1. WHAT IS THIS ABOUT?
/*
   In data-heavy applications like simulations or trading engines,
   how you lay out your data structures in memory can hugely affect performance.

   The two most common ways to organize data:
   - Array of Structs (AoS)
   - Struct of Arrays (SoA)

   The choice impacts CPU cache efficiency, prefetching, and SIMD vectorization.
*/


// 2. WHAT IS AoS (Array of Structs)?
/*
   Example:
   struct Particle { float x, y, z; };
   Particle particles[N];

   Each element is a full object — x, y, z are stored together.

   ✅ Easier to write, good for object-oriented use.
   ❌ Slower for numeric-heavy tasks where you operate on one field at a time (e.g., all x's).
*/


// 3. WHAT IS SoA (Struct of Arrays)?
/*
   Example:
   struct ParticleSoA {
       float x[N];
       float y[N];
       float z[N];
   };

   Each field is stored in its own separate array.

   ✅ Much better cache locality and vectorization when accessing one field (like x[]).
   ❌ Slightly harder to maintain and less intuitive for general programming.
*/


// 4. WHY DOES THIS MATTER?
/*
   CPUs load data in cache lines (typically 64 bytes).
   With AoS, you may bring in data you don’t need (y/z when only x is used).

   SoA minimizes waste and ensures contiguous memory access,
   allowing better prefetching and SIMD acceleration.

   In HFT or simulation, this difference can significantly affect throughput.
*/


// 5. HOW DO WE TEST IT?
/*
   - Create large arrays (e.g., 100 million elements)
   - Benchmark time to process x, y, z in both AoS and SoA
   - Compare the runtime

   You’ll likely see SoA being faster when access is structured and linear.
*/


// 6. WHAT DO WE CONCLUDE?
/*
   - SoA is great for performance-critical, field-centric computations
   - AoS is easier but may be slower
   - In HFT, using SoA can improve latency for batch operations
*/
#include <iostream>
#include <vector>
#include <chrono>

constexpr size_t NUM_PARTICLES = 100'000'000;

struct ParticleAoS {
    float x, y, z;
};

struct ParticlesSoA {
    std::vector<float> x, y, z;

    ParticlesSoA(size_t n) {
        x.resize(n);
        y.resize(n);
        z.resize(n);
    }
};

void runAoSBenchmark() {
    std::vector<ParticleAoS> particles(NUM_PARTICLES);

    auto start = std::chrono::high_resolution_clock::now();
    float sum = 0.0f;
    for (size_t i = 0; i < NUM_PARTICLES; ++i) {
        sum += particles[i].x;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "❌ AoS read took: " << ms << " ms, sum: " << sum << '\n';
}

void runSoABenchmark() {
    ParticlesSoA particles(NUM_PARTICLES);

    auto start = std::chrono::high_resolution_clock::now();
    float sum = 0.0f;
    for (size_t i = 0; i < NUM_PARTICLES; ++i) {
        sum += particles.x[i];
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "✅ SoA read took: " << ms << " ms, sum: " << sum << '\n';
}

int main() {
    std::cout << "🔍 Benchmarking AoS vs SoA...\n";
    runAoSBenchmark();
    runSoABenchmark();
    return 0;
}
