#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define ONE_MEG 1 << 20

int main() {
  int f = open("./foo", O_CREAT | O_WRONLY | O_TRUNC);
  struct stat st;
  int prior_blocks = -1;
  for (int i = 0; i < ONE_MEG; i++) {
    write(f, ".", 1);
    fstat(f, &st);
    if (st.st_blocks != prior_blocks) {
      // printf("st_blocks: %ld, prior_blocks: %d\n", st.st_blocks,
      // prior_blocks);
      printf("Size: %ld, blocks: %ld, on disk: %ld\n", st.st_size, st.st_blocks,
             st.st_blocks * 512);
      prior_blocks = st.st_blocks;
    }
  }
}
