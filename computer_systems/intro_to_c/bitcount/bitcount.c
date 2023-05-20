#include <assert.h>
#include <stdio.h>

int bitcount(int n) {
  int count = 0;

  while (n) {
    if (n & 0b1) {
      count += 1;
    }
    n >>= 1;
  }

  return count;
}

int main() {
  assert(bitcount(0) == 0);
  assert(bitcount(1) == 1);
  assert(bitcount(3) == 2);
  assert(bitcount(8) == 1);
  // harder case:
  // assert(bitcount(0xffffffff) == 32);
  printf("OK\n");
}
