#include <stdio.h>

int main() {
  int n = 5;

  int *p = &n; // p will be the address where n is and *p dereferences it to get
               // the value at p

  int foo = *p; // get the value stored at *p and store at foo

  printf("n = %d\n&n = %p\np = %p\nfoo = %d\n", n, &n, p, foo);

  int arr[10];

  printf("arr =  %p\n", arr);
  printf("arr + 1 = %p\n",
         arr + 1); // this takes us to the next INTEGER since it's an arr of int

  arr[3] = 42;
  printf("arr[3] = %d\n", arr[3]);
  // move to the third INTEGER after start of array
  // that gives us the memory locaction
  // if we dereference it, we get the value there at 3 ints away from start of
  // array
  printf("arr + 3 = %p\n, *(arr+3) = %d\n", arr + 3, *(arr + 3));
}
