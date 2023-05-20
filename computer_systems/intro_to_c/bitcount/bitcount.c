#include <assert.h>
#include <stdio.h>

int bitcount(unsigned int n) {
  int count = 0;

  while (n) {

    // faster version:
    // x & x-1 "deletes" the right most bit
    // if we do this until x = 0
    // starting at 0b111 = x *******
    // 0b111 & 0b111-0b001 which is
    // 0b111 & 0b110 --> 0b110 = x ******
    // continue with this in the next iteration
    // 0b110 - 0b001 = 0b101
    // x&x-1 gives 0b110 & 0b101 --> 0b100 = x ******
    // and one more time
    // 0b100 - 0b001 --> 0b011
    // 0b100 & 0b011 --> 0b000 = x *****
    // now we hit 0

    // we can see that each time the right most "on" bit is removed
    // we started with 111, then 110, then 100, then 000
    // so we just have to go to zero
    // and if there's three "on" bits, it only takes 3 iterations,
    // compared to the initial implementation which needs to
    // iterate 32 times (32bit) no matter what n is
    count++;
    n &= n - 1;

    //////////////////////////////
    // initial implementation:
    // count += n & 0b1;
    // // C does arithmetic shift on signed int, so we tell it is a unsigned int
    // // in order to do logical shift
    // n >>= 1;
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
