#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTING_BUCKETS 8
#define MAX_KEY_SIZE 32

typedef uint32_t Hash;

typedef struct Node {
  char *key;
  void *value;
  Hash hash;
  struct Node *next;
} Node;

typedef struct Hashmap {
  Node **buckets;
  int num_buckets;
} Hashmap;

Hash djb2(const char *s) {
  Hash h = 8351;
  char ch;

  while ((ch = *s++)) {
    h = (h << 5) + h + ch;
  }
  return h;
}

Hashmap *Hashmap_new() {
  Hashmap *h = malloc(sizeof(Hashmap));
  h->buckets = calloc(STARTING_BUCKETS, sizeof(Node));
  h->num_buckets = STARTING_BUCKETS;
  return h;
}

void Hashmap_set(Hashmap *h, char *key, void *value) {
  Hash hash = djb2(key);
  int i = hash % h->num_buckets;
  Node *n = h->buckets[i];
  while (n != NULL) {
    if (n->hash == hash && strncmp(key, n->key, MAX_KEY_SIZE) == 0) {
      n->value = value; // replace the value
      return;
    }
    n = n->next;
  }

  // insert new node at head of linked list
  n = malloc(sizeof(Node));
  n->key = strdup(key);
  n->value = value;
  n->hash = hash;
  n->next = h->buckets[i];
  h->buckets[i] = n;
}

void *Hashmap_get(Hashmap *h, char *key) {
  Hash hash = djb2(key);
  int i = hash % h->num_buckets;
  Node *n = h->buckets[i];
  while (n != NULL) {
    if (n->hash == hash && strncmp(key, n->key, MAX_KEY_SIZE) == 0) {
      return n->value;
    }
    n = n->next;
  }
  return NULL;
}

void Hashmap_delete(Hashmap *h, char *key) {
  Hash hash = djb2(key);
  int i = hash % h->num_buckets;
  Node *n = h->buckets[i];
  Node *prev = NULL;
  while (n != NULL) {
    if (n->hash == hash && strncmp(key, n->key, MAX_KEY_SIZE) == 0) {
      if (prev == NULL) {
        // head of the linked list
        h->buckets[i] = NULL;
      } else {
        // connect the previous to the next in the linked list to skip and
        // delete the current node
        prev->next = n->next;
      }
      free(n->key);
      free(n);
      return;
    }
    prev = n;
    n = n->next;
  }
}

void Hashmap_free(Hashmap *h) {
  Node *prev, *n;
  for (int i = 0; i < h->num_buckets; i++) {
    n = h->buckets[i];
    while (n != NULL) {
      // advance the pointers and then delete the previous ones once we have
      // moved away from them
      prev = n;
      n = n->next;

      free(prev->key);
      free(prev);
    }
  }
  free(h->buckets);
  free(h);
}

int main() {
  Hashmap *h = Hashmap_new();

  // basic get/set functionality
  int a = 5;
  float b = 7.2;
  Hashmap_set(h, "item a", &a);
  Hashmap_set(h, "item b", &b);
  assert(Hashmap_get(h, "item a") == &a);
  assert(Hashmap_get(h, "item b") == &b);

  // using the same key should override the previous value
  int c = 20;
  Hashmap_set(h, "item a", &c);
  assert(Hashmap_get(h, "item a") == &c);

  // basic delete functionality
  Hashmap_delete(h, "item a");
  assert(Hashmap_get(h, "item a") == NULL);

  // handle collisions correctly
  // note: this doesn't necessarily test expansion
  int i, n = STARTING_BUCKETS * 10, ns[n];
  char key[MAX_KEY_SIZE];
  for (i = 0; i < n; i++) {
    ns[i] = i;
    sprintf(key, "item %d", i);
    Hashmap_set(h, key, &ns[i]);
  }
  for (i = 0; i < n; i++) {
    sprintf(key, "item %d", i);
    assert(Hashmap_get(h, key) == &ns[i]);
  }

  Hashmap_free(h);
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
  printf("ok\n");
}
