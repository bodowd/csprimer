#include <assert.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  void **items;
  int length;
  int capacity;
} DA;

DA *DA_new(void) {
  DA *da = malloc(sizeof(DA));
  da->length = 0;
  da->capacity = STARTING_CAPACITY;
  da->items = malloc(STARTING_CAPACITY * sizeof(void *));
  return da;
}

void DA_free(DA *da) {
  free(da->items);
  free(da);
}

void DA_push(DA *da, void *x) {
  if (da->length == da->capacity) {
    da->capacity <<= 1;
    da->items = realloc(da->items, da->capacity * sizeof(void *));
  }
  da->items[da->length++] = x;
};

void *DA_pop(DA *da) {
  if (da->length == 0) {
    return NULL;
  };
  return da->items[--da->length];
};

void DA_set(DA *da, void *x, int i) { da->items[i] = x; }

void *DA_get(DA *da, int i) { return da->items[i]; }

int DA_size(DA *da) { return da->length; };

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
