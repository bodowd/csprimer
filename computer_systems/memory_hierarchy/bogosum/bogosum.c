/*
 * INSTRUCTIONS
 *
 * Consider the code below, and ask yourself the following questions:
 *
 * - How many memory accesses does it take to compute the sum of nums?
 * - How many cache hits/misses do you expect to see for ordered vs random
 * access?
 * - What would change if you:
 *   - reordered the fields of the struct?
 *   - removed `foo` and `bar`?
 *   - changed `value` to a short?
 * - Are there certain values of N that would substantially change your
 * calculations?
 * - Whatever else you find interesting!
 *
 * Try to form concrete hypotheses, and compare to the results you see in perf
 * and/or cachegrind. Note: if the cachegrind simulation takes too long, try
 * lower values of n. Also, you may want to compile at -O1 to avoid redundant
 * memory access at -O0.
 *
 * Advanced/strech goal: approximate the expected execution time of both ordered
 * and random, and try to explain any differences you see with actual
 * measurements!
 *
 * Estimations:
 * - struct number size: 12 B
 *      short 2B
 *      int 4B
 *      short 2B
 * but there is 2B padding after Short to line int on a 4B boundary
 * so with 2*2B padding, we get 12B for the struct number
 *
 * - n = 1 << 26 = 2^26 = 2^6 * 2^20 =~ 64M
 * - total data size: ~64*12 =~ 750MB
 * - this gives us an idea of how much of our data would even fit into cache
 *    we will overwhelm even L3 (which may be ~6MB)
 *
 * - cache line is 64B and struct size is 12B: so we can get ~5 structs per
 * cache line (12 * 5 = 60). A struct that straddles the cache line, you will
 * have to retrieve again
 *
 * - Q: How many memory accesses does it take to compute the sum of nums?
 *      - we will loop n times
 *      - then we will do one lookup in indexes
 *      - and one lookup in nums (to get nums.value)
 *      - so 2 lookups times n times
 *      - memory accesses per invocation of sum: 2 * n = 2 * ~64M =~ 130M
        - ordered access: (4 byte ints. 64 byte cache line)
            so 16 ints in a cache line
            1 time out of 16 we will miss the cache (the next int after the 16th
 int) 1 miss 15 hits
            5 structs per cache line
           ... 1/16 * 65M cache misses L1data cache + 1/5 structs * 65M L1d
           cache misses
           =~ 17M misses

        - random access: likely much more misses
        1/16 * 65M + 5/5 * 65M =~ 69M L1d misses


Q: what if we reordered the fields in the struct?
originally:
struct number {
  short foo;
  int value;
  short bar;
};

struct number {
  int value;
  short bar;
  short foo;
};

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct number {
  int value;
  short foo;
  short bar;
};

int sum(struct number nums[], int indexes[], int n) {
  int idx, total = 0;

  for (int i = 0; i < n; i++) {
    idx = indexes[i];
    total += nums[idx].value;
  }
  return total;
}

void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = n - 1; i > 0; i--) {
      size_t j = (unsigned int)(drand48() * (i + 1));
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int main(int argc, char **argv) {
  srand(1);
  int i, n = (1 << 26);
  int *ordered = malloc(n * sizeof(int));
  int *random = malloc(n * sizeof(int));
  struct number *nums = malloc(n * sizeof(struct number));
  // construct arrays of indices
  for (i = 0; i < n; i++) {
    ordered[i] = i;
    random[i] = i;
  }
  shuffle(random, n);
  // pick random numbers to sum
  for (i = 0; i < n; i++)
    nums[i].value = rand();
  if (argc == 2 && strcmp(argv[1], "baseline") == 0)
    exit(0);
  clock_t start, end;
  if (argc == 1 || strcmp(argv[1], "ordered") == 0) {
    start = clock();
    int sum1 = sum(nums, ordered, n);
    end = clock();
    printf("Ordered: %d in %0.3fs\n", sum1,
           (double)(end - start) / CLOCKS_PER_SEC);
  }
  if (argc == 1 || strcmp(argv[1], "random") == 0) {
    start = clock();
    int sum2 = sum(nums, random, n);
    end = clock();
    printf("Random:  %d in %0.3fs\n", sum2,
           (double)(end - start) / CLOCKS_PER_SEC);
  }
}
