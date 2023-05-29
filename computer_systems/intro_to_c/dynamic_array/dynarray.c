#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  // pointer to the starting location of a sequence of pointers to
  // "anything"(void)
  // we add the pointer to the item to the array
  void **items;
  int length;   // number of items
  int capacity; // we will need to grow and need to know the capacity at any
                // point of time because that will tell us if we need to grow
                // again
} DA;

DA *DA_new(void) {
  // TODO allocate and return a new dynamic array
  DA *da =
      malloc(sizeof(DA)); // allocate the void** (8 bytes on some machines), and
                          // length and capacity which are 4 byte ints, each
  da->length = 0;
  da->capacity = STARTING_CAPACITY;
  da->items =
      malloc(STARTING_CAPACITY * sizeof(void *)); // allocate the actual items

  return da;
}

void DA_free(DA *da) {
  // TODO deallocate anything on the heap
  free(
      da->items); // da->items is pointer to sequence of void pointer pointers.
                  // This will deallocate those but NOT the values they point to
  free(da);
}

int DA_size(DA *da) {
  // TODO return the number of items in the dynamic array
  return da->length;
}

void DA_push(DA *da, void *x) {
  if (da->length == da->capacity) {
    da->capacity <<= 1; // left shift one means double the size (<< 1 == *2)
    da->items = realloc(
        da->items, da->capacity * sizeof(void *)); // grow to the new capacity
    printf("Resized to %d\n", da->capacity);
  }
  // increment length AFTER it is used as the index. Increments by one.
  // same as:
  // da->items[da->length]=x;
  // da->length++;
  da->items[da->length++] = x;
}

void *DA_pop(DA *da) {
  // TODO pop from the end
  if (da->length == 0) {
    return NULL;
  }
  // decrement length first, then use it as an index to access an element
  return da->items[--da->length];
}

void DA_set(DA *da, void *x, int i) {
  // TODO set at a given index, if possible
  // place item x at i
  da->items[i] = x;
}

void *DA_get(DA *da, int i) {
  // TODO get from a given index, if possible
  return da->items[i];
}

int main() {
  DA *da = DA_new();

  assert(DA_size(da) == 0);

  // basic push and pop test
  int x = 5;
  float y = 12.4;
  DA_push(da, &x);
  printf("&x: %p\n", &x);
  printf("&y: %p\n", &y);
  DA_push(da, &y);
  assert(DA_size(da) == 2);

  assert(DA_pop(da) == &y);
  assert(DA_size(da) == 1);

  assert(DA_pop(da) == &x);
  assert(DA_size(da) == 0);
  assert(DA_pop(da) == NULL);

  // basic set/get test
  DA_push(da, &x);
  DA_set(da, &y, 0);
  assert(DA_get(da, 0) == &y);
  DA_pop(da);
  assert(DA_size(da) == 0);

  // expansion test
  DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
  DA_push(da2, &x);
  int i, n = 100 * STARTING_CAPACITY, arr[n];
  for (i = 0; i < n; i++) {
    arr[i] = i;
    DA_push(da, &arr[i]);
  }
  assert(DA_size(da) == n);
  for (i = 0; i < n; i++) {
    assert(DA_get(da, i) == &arr[i]);
  }
  for (; n; n--)
    DA_pop(da);
  assert(DA_size(da) == 0);
  assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

  DA_free(da);
  DA_free(da2);
  printf("OK\n");
}
