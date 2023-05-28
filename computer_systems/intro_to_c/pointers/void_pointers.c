#include <stdio.h>

struct Box {
  char *name;
  void *value;
};

int main() {
  struct Box b1 = {"foo", "box"};
  int n = 5;
  struct Box b2 = {"bar", &n};

  // we have to tell the compiler what the type of value is
  // void* allows it to be different types
  printf("values are: %s and %d\n", (char *)b1.value, *(int *)b2.value);
}
