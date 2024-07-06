#include <stdio.h>
#include <unistd.h>
void f(int depth, long int bottom) {
  // bottom - depth tells us how many bytes into the stack we are
  // the stack grows toward smaller addresses, so bottom - depth
  if (depth % 10000 == 0) {

    fprintf(stderr, "[pid %d] frame %d %ld (%p)\n", getpid(), depth,
            bottom - (long)&depth, &depth);
  }
  return f(depth + 1, bottom);
}

void start() {
  int depth = 0;
  f(depth, (long)&depth);
}

// int fib(int n, long int bottom) {
//   printf("frame %d %ld (%p)\n", n, bottom - (long)&n, &n);
//
//   if (n <= 1) {
//     return n;
//   }
//
//   return fib(n - 1, bottom) + fib(n - 2, bottom);
// }
//
// void start_fib() {
//   int depth = 100;
//   fib(depth, (long)&depth);
// }

int main() {
  start();
  // start_fib();
  printf("OK\n");
}
