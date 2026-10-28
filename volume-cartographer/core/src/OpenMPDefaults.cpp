// With LLVM's OpenMP runtime (libomp), idle worker threads spin for 200 ms
// after each parallel region by default. VC3D's parallel regions are short
// and frequent, so the spinning roughly triples CPU time without making
// anything faster. Make idle workers sleep immediately unless the user set
// KMP_BLOCKTIME. libomp reads its environment before this library's static
// initializers run, so use the runtime API rather than setenv().
#if defined(_OPENMP) && defined(__clang__)
#include <omp.h>

#include <cstdlib>

namespace {
[[maybe_unused]] const bool kOpenMPDefaultsApplied = [] {
    if (std::getenv("KMP_BLOCKTIME") == nullptr) {
        kmp_set_blocktime(0);
    }
    return true;
}();
}  // namespace
#endif
