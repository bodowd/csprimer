#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define SLEEP_SEC 3
#define NUM_MULS 100000000
#define NUM_MALLOCS 100000
#define MALLOC_SIZE 1000

// TODO define this struct
struct profile_times {
  clock_t cpu_start;
  double cpu_time_used;
  time_t wall_start;
  double wall_used;
  uint64_t real_usec;
};

// TODO populate the given struct with starting information
void profile_start(struct profile_times *t) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  t->real_usec = tv.tv_sec * 1000000 * tv.tv_usec;

  // real time
  t->wall_start = time(NULL);

  // cpu time
  t->cpu_start = clock();
}

// TODO given starting information, compute and log differences to now
void profile_log(struct profile_times *t) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  t->real_usec = tv.tv_sec * 1000000 * tv.tv_usec;

  // real time
  t->wall_used = time(NULL) - t->wall_start;

  // cpu time
  t->cpu_time_used = ((double)(clock() - t->cpu_start)) / CLOCKS_PER_SEC;

  pid_t pid = getpid();

  printf("[%d] real: %f, cpu: %f\n", pid, t->wall_used, t->cpu_time_used);
}

int main(int argc, char *argv[]) {
  struct profile_times t;

  // TODO profile doing a bunch of floating point muls
  printf("Floating point multiplications\n");
  float x = 1.0;
  profile_start(&t);
  for (int i = 0; i < NUM_MULS; i++)
    x *= 1.1;
  profile_log(&t);

  // TODO profile doing a bunch of mallocs
  printf("Mallocs\n");
  profile_start(&t);
  void *p;
  for (int i = 0; i < NUM_MALLOCS; i++)
    p = malloc(MALLOC_SIZE);
  profile_log(&t);

  // TODO profile sleeping
  printf("Sleeping\n");
  profile_start(&t);
  sleep(SLEEP_SEC);
  profile_log(&t);
}
