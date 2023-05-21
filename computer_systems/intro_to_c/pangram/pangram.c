#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool ispangram(char *s) {
  // s is the LOCATION where the string starts

  uint32_t bs = 0;
  char c;
  while (*s != '\0') {
    c = tolower(*s++); // increment the pointer to the next char and lower it in
                       // one line

    // there's punctuation in the text so we want to ignore that
    if (c < 'a' || c > 'z')
      continue;

    bs |= 1 << (c - 'a');
  }
  // all the 'f's are the lower 24 bits --> 6 f's 4 bits each
  // then the 3 is the next highest 2 bits (b/c 3 is 0b11 -- 2 bits)
  // to give 26 bits on in total
  return bs == 0x03ffffff;
}

int main() {
  size_t len;
  ssize_t read;
  char *line = NULL;
  while ((read = getline(&line, &len, stdin)) != -1) {
    if (ispangram(line))
      printf("%s", line);
  }

  if (ferror(stdin))
    fprintf(stderr, "Error reading from stdin");

  free(line);
  fprintf(stderr, "ok\n");
}
