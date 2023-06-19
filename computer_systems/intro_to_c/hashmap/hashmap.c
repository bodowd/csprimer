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
  void *value;       // value could be anything
  Hash hash;         // cache the hash
  struct Node *next; // pointer to the next node in the linked list
} Node;

typedef struct Hashmap {
  Node **buckets; // a number of Node pointers, the next field will be a Node
                  // pointer. Can't put a struct in a struct. Have to put a
                  // pointer to the next struct
  int num_buckets;
} Hashmap;

Hash djb2(const char *s) {
  Hash h = 8351;
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

Hashmap *Hashmap_new() {
  Hashmap *h = malloc(sizeof(Hashmap));
  h->buckets = calloc(STARTING_BUCKETS, sizeof(Node));
  h->num_buckets = STARTING_BUCKETS;

  return h;
}

void Hashmap_free(Hashmap *h) {
  // TODO: free all the nodes in the buckets otherwise the bukets are freed but
  // the nodes themselves are dangling and leads to memory leak
  // remember also to free string copies
  free(h->buckets);
  free(h);
}

void Hashmap_set(Hashmap *h, char *key, void *value) {
  Hash hash = djb2(key);
  int i = hash % h->num_buckets;
  Node *n = h->buckets[i]; // go to where the first node would be, if it exists
  while (n != NULL) {
    // if key is same hash as what is already stored there, and the key is the
    // same, replace the value of the node
    if (n->hash == hash && strncmp(key, n->key, MAX_KEY_SIZE) == 0) {
      n->value = value;
      return;
    }
    n = n->next;
  }
  // otherwise, we have gotten to the end of the linked list at this bucket
  n = malloc(sizeof(Node));
  n->key = strdup(key);
  n->value = value;
  n->hash = hash;
  // set the next of the new node to be the current head of the linked list
  n->next = h->buckets[i];
  // set the head of the linked list at this bucket to be the new node
  h->buckets[i] = n;
}

void *Hashmap_get(Hashmap *h, char *key) {
  // TODO handle collisions
  Hash hash = djb2(key);
  Node *n = h->buckets[hash % h->num_buckets];
  while (n != NULL) {
    printf("%s\n", n->key);
    if (n->hash == hash && strncmp(key, n->key, MAX_KEY_SIZE) == 0) {
      return n->value;
    }
    n = n->next;
  }
  return NULL;
}

void Hashmap_delete(Hashmap *h, char *key) {
  int i = djb2(key) % h->num_buckets;
  Node *n = h->buckets[i];
  free(n); // TODO only free if there is something at that location
  h->buckets[i] = NULL;
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
