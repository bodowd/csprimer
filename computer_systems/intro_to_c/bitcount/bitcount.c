#include <assert.h>
#include <stdio.h>

int bitcount(unsigned int n) {
  int count = 0;

  while (n) {
    count += n & 0b1;
    // C does arithmetic shift on signed int, so we tell it is a unsigned int
    // in order to do logical shift
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
  assert(bitcount(0xffffffff) == 32);
  printf("OK\n");
}
