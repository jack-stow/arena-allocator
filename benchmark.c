#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arena.h"

#define NUM_BLOCKS ((size_t)5000000ULL)
#define BLOCK_SIZE ((size_t)4)

// Helper: compute elapsed time in seconds from timespec
double timespec_diff_sec(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    // ----------------------
    // Benchmark malloc/free
    // ----------------------
    struct timespec wstart, wend;
    clock_t cstart, cend;
    double malloc_cpu_time, malloc_wall_time;

    void **blocks = malloc(NUM_BLOCKS * sizeof(void *));
    if (!blocks){
		printf("Failed to allocate blocks array\n");
		return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &wstart);
    cstart = clock();

    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        blocks[i] = malloc(BLOCK_SIZE);
        if (!blocks[i]) {
            printf("malloc failed at %zu\n", i);
            return 1;
        }
        memset(blocks[i], 0xAB, BLOCK_SIZE);
    }
    for (size_t i = 0; i < NUM_BLOCKS; i++) free(blocks[i]);

    cend = clock();
    clock_gettime(CLOCK_MONOTONIC, &wend);

    malloc_cpu_time = (double)(cend - cstart) / CLOCKS_PER_SEC;
    malloc_wall_time = timespec_diff_sec(wstart, wend);

    printf("malloc/free - CPU time: %.6f s, Wall-clock: %.6f s\n",
           malloc_cpu_time, malloc_wall_time);

    // ----------------------
    // Benchmark arena allocator
    // ----------------------
    Arena *arena = ArenaAlloc(NUM_BLOCKS * BLOCK_SIZE);
    if (!arena) {
        printf("Arena allocation failed\n");
        return 1;
    }

    clock_gettime(CLOCK_MONOTONIC, &wstart);
    cstart = clock();

    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        void *ptr = PushArray(arena, char, BLOCK_SIZE);
        if (!ptr) {
            printf("Arena allocation failed at %zu\n", i);
            return 1;
        }
        memset(ptr, 0xAB, BLOCK_SIZE);
    }

    ArenaClear(arena);
    ArenaRelease(arena);

    cend = clock();
    clock_gettime(CLOCK_MONOTONIC, &wend);

    double arena_cpu_time = (double)(cend - cstart) / CLOCKS_PER_SEC;
    double arena_wall_time = timespec_diff_sec(wstart, wend);

    printf("arena allocator - CPU time: %.6f s, Wall-clock: %.6f s\n",
           arena_cpu_time, arena_wall_time);

    return 0;
}
