#if defined(OS_LINUX)
#include <stdlib.h>

/// Interposing these symbols explicitly. The idea works like this: malloc.cpp compiles to a
/// dedicated object (namely clickhouse_malloc.o), and it will show earlier in the link command
/// than malloc libs like libjemalloc.a. As a result, these symbols get picked in time right after.
extern "C"
{
    void *malloc(size_t size);
    void free(void *ptr);
    void *calloc(size_t nmemb, size_t size);
    void *realloc(void *ptr, size_t size);
    int posix_memalign(void **memptr, size_t alignment, size_t size);
    void *aligned_alloc(size_t alignment, size_t size);
    void *valloc(size_t size);
    void *memalign(size_t alignment, size_t size);
    void *pvalloc(size_t size);
}

template<typename T>
inline void ignore(T x __attribute__((unused)))
{
}

static void dummyFunctionForInterposing() __attribute__((used));
static void dummyFunctionForInterposing()
{
    void* dummy;
    /// Suppression for PVS-Studio.
    free(nullptr); // -V575
    ignore(malloc(0)); // -V575
    ignore(calloc(0, 0)); // -V575
    ignore(realloc(nullptr, 0)); // -V575
    ignore(posix_memalign(&dummy, 0, 0)); // -V575
    ignore(aligned_alloc(0, 0)); // -V575
    ignore(valloc(0)); // -V575
    ignore(memalign(0, 0)); // -V575
    ignore(pvalloc(0)); // -V575
}
#endif
