# Cachegrind

`valgrind --tool=cachegrind ./one`

```
❯ valgrind --tool=cachegrind ./one
==223766== Cachegrind, a cache and branch-prediction profiler
==223766== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==223766== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==223766== Command: ./one
==223766==
--223766-- warning: L3 cache found, using its data for the LL simulation.
==223766==
==223766== I refs: 224,189,012
==223766== I1 misses: 1,133
==223766== LLi misses: 1,121
==223766== I1 miss rate: 0.00%
==223766== LLi miss rate: 0.00%
==223766==
==223766== D refs: 128,067,149 (96,046,626 rd + 32,020,523 wr)
==223766== D1 misses: 1,002,185 ( 1,595 rd + 1,000,590 wr)
==223766== LLd misses: 1,001,905 ( 1,354 rd + 1,000,551 wr)
==223766== D1 miss rate: 0.8% ( 0.0% + 3.1% )
==223766== LLd miss rate: 0.8% ( 0.0% + 3.1% )
==223766==
==223766== LL refs: 1,003,318 ( 2,728 rd + 1,000,590 wr)
==223766== LL misses: 1,003,026 ( 2,475 rd + 1,000,551 wr)
==223766== LL miss rate: 0.3% ( 0.0% + 3.1% )
```

```
❯ valgrind --tool=cachegrind ./two
==223767== Cachegrind, a cache and branch-prediction profiler
==223767== Copyright (C) 2002-2017, and GNU GPL'd, by Nicholas Nethercote et al.
==223767== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==223767== Command: ./two
==223767==
--223767-- warning: L3 cache found, using its data for the LL simulation.
==223767==
==223767== I refs: 224,189,012
==223767== I1 misses: 1,133
==223767== LLi misses: 1,121
==223767== I1 miss rate: 0.00%
==223767== LLi miss rate: 0.00%
==223767==
==223767== D refs: 128,067,149 (96,046,626 rd + 32,020,523 wr)
==223767== D1 misses: 16,002,185 ( 1,595 rd + 16,000,590 wr)
==223767== LLd misses: 1,001,905 ( 1,354 rd + 1,000,551 wr)
==223767== D1 miss rate: 12.5% ( 0.0% + 50.0% )
==223767== LLd miss rate: 0.8% ( 0.0% + 3.1% )
==223767==
==223767== LL refs: 16,003,318 ( 2,728 rd + 16,000,590 wr)
==223767== LL misses: 1,003,026 ( 2,475 rd + 1,000,551 wr)
==223767== LL miss rate: 0.3% ( 0.0% + 3.1% )
```

L1 is split into I and D. Dedicated and Instruction caches

# Perf stat

❯ perf stat ./one

```
❯ perf stat -d ./one

 Performance counter stats for './one':

             63.36 msec task-clock:u                     #    0.961 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
            15,673      page-faults:u                    #  247.346 K/sec
        78,888,709      cycles:u                         #    1.245 GHz                         (77.44%)
            82,942      stalled-cycles-frontend:u        #    0.11% frontend cycles idle        (77.41%)
        37,213,411      stalled-cycles-backend:u         #   47.17% backend cycles idle         (74.80%)
       203,836,339      instructions:u                   #    2.58  insn per cycle
                                                  #    0.18  stalled cycles per insn     (74.94%)
        29,421,379      branches:u                       #  464.318 M/sec                       (74.91%)
            22,231      branch-misses:u                  #    0.08% of all branches             (74.79%)
       146,233,306      L1-dcache-loads:u                #    2.308 G/sec                       (72.86%)
         1,155,143      L1-dcache-load-misses:u          #    0.79% of all L1-dcache accesses   (72.86%)
   <not supported>      LLC-loads:u
   <not supported>      LLC-load-misses:u

       0.065961323 seconds time elapsed

       0.038481000 seconds user
       0.025654000 seconds sys
```

```
❯ perf stat -d ./two

 Performance counter stats for './two':

             89.81 msec task-clock:u                     #    0.950 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
            15,674      page-faults:u                    #  174.517 K/sec
       260,338,209      cycles:u                         #    2.899 GHz                         (73.36%)
           149,565      stalled-cycles-frontend:u        #    0.06% frontend cycles idle        (73.39%)
       210,614,075      stalled-cycles-backend:u         #   80.90% backend cycles idle         (73.52%)
       216,004,214      instructions:u                   #    0.83  insn per cycle
                                                  #    0.98  stalled cycles per insn     (73.48%)
        32,848,075      branches:u                       #  365.737 M/sec                       (73.55%)
            22,708      branch-misses:u                  #    0.07% of all branches             (77.25%)
       153,537,174      L1-dcache-loads:u                #    1.710 G/sec                       (79.57%)
        16,942,808      L1-dcache-load-misses:u          #   11.03% of all L1-dcache accesses   (75.88%)
   <not supported>      LLC-loads:u
   <not supported>      LLC-load-misses:u

       0.094568225 seconds time elapsed

       0.061950000 seconds user
       0.028910000 seconds sys
```
