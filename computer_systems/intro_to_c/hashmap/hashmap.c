#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define STARTING_BUCKETS 8

uint32_t djb2(const char *s) {
  int32_t h = 8351;
  char ch;

  // increment right after to go to the next char pointer
  while ((ch = *s++)) {
    // the more we loop through the more we move the hash away from the starting
    // location so that we get significantly different hash values
    // (h<<5) is mulitplying by 32, then add h to get to the effect of
    // mulitplying by 33. We want to spread out the values even when there is a
    // small change to the input
    h = (h << 5) + h + ch;
  }

  return h;
}

int main() {

  printf("%d\n", djb2("oof"));
  printf("%d\n", djb2("goo"));
  printf("%d\n", djb2("foo"));
  printf("%d\n", djb2("bar"));
  // Hashmap *h = Hashmap_new();
  //
  // // basic get/set functionality
  // int a = 5;
  // float b = 7.2;
  // Hashmap_set(h, "item a", &a);
  // Hashmap_set(h, "item b", &b);
  // assert(Hashmap_get(h, "item a") == &a);
  // assert(Hashmap_get(h, "item b") == &b);
  //
  // // using the same key should override the previous value
  // int c = 20;
  // Hashmap_set(h, "item a", &c);
  // assert(Hashmap_get(h, "item a") == &c);
  //
  // // basic delete functionality
  // Hashmap_delete(h, "item a");
  // assert(Hashmap_get(h, "item a") == NULL);
  //
  // // handle collisions correctly
  // // note: this doesn't necessarily test expansion
  // int i, n = STARTING_BUCKETS * 10, ns[n];
  // char key[MAX_KEY_SIZE];
  // for (i = 0; i < n; i++) {
  //   ns[i] = i;
  //   sprintf(key, "item %d", i);
  //   Hashmap_set(h, key, &ns[i]);
  // }
  // for (i = 0; i < n; i++) {
  //   sprintf(key, "item %d", i);
  //   assert(Hashmap_get(h, key) == &ns[i]);
  // }
  //
  // Hashmap_free(h);
  // /*
  //    stretch goals:
  //    - expand the underlying array if we start to get a lot of collisions
  //    - support non-string keys
  //    - try different hash functions
  //    - switch from chaining to open addressing
  //    - use a sophisticated rehashing scheme to avoid clustered collisions
  //    - implement some features from Python dicts, such as reducing space use,
  //    maintaing key ordering etc. see
  //    https://www.youtube.com/watch?v=npw4s1QTmPg for ideas
  //    */
  // printf("ok\n");
}
