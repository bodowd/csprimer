```
❯ perf stat -d ./a.out baseline

 Performance counter stats for './a.out baseline':

          4,823.27 msec task-clock:u                     #    0.997 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
           327,733      page-faults:u                    #   67.948 K/sec
    17,408,968,645      cycles:u                         #    3.609 GHz                         (74.99%)
         8,752,347      stalled-cycles-frontend:u        #    0.05% frontend cycles idle        (75.07%)
    15,438,136,472      stalled-cycles-backend:u         #   88.68% backend cycles idle         (75.01%)
    10,249,196,431      instructions:u                   #    0.59  insn per cycle
                                                  #    1.51  stalled cycles per insn     (74.99%)
     1,936,691,358      branches:u                       #  401.530 M/sec                       (75.06%)
         2,520,582      branch-misses:u                  #    0.13% of all branches             (75.05%)
     4,391,324,008      L1-dcache-loads:u                #  910.445 M/sec                       (74.94%)
        93,290,935      L1-dcache-load-misses:u          #    2.12% of all L1-dcache accesses   (74.90%)
   <not supported>      LLC-loads:u
   <not supported>      LLC-load-misses:u

       4.838139121 seconds time elapsed

       4.414486000 seconds user
       0.407491000 seconds sys


❯ perf stat -d ./a.out ordered
Ordered: -1043987429 in 0.073s

 Performance counter stats for './a.out ordered':

          5,260.71 msec task-clock:u                     #    0.995 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
           327,742      page-faults:u                    #   62.300 K/sec
    18,975,820,870      cycles:u                         #    3.607 GHz                         (74.94%)
         9,161,685      stalled-cycles-frontend:u        #    0.05% frontend cycles idle        (74.92%)
    16,925,436,298      stalled-cycles-backend:u         #   89.19% backend cycles idle         (75.01%)
    10,652,783,513      instructions:u                   #    0.56  insn per cycle
                                                  #    1.59  stalled cycles per insn     (75.00%)
     2,005,774,912      branches:u                       #  381.274 M/sec                       (75.02%)
         2,530,544      branch-misses:u                  #    0.13% of all branches             (75.06%)
     4,521,290,162      L1-dcache-loads:u                #  859.444 M/sec                       (75.03%)
       109,022,072      L1-dcache-load-misses:u          #    2.41% of all L1-dcache accesses   (75.01%)
   <not supported>      LLC-loads:u
   <not supported>      LLC-load-misses:u

       5.287507537 seconds time elapsed

       4.782088000 seconds user
       0.477406000 seconds sys

❯ perf stat -d ./a.out random
Random:  -1043987429 in 1.355s

 Performance counter stats for './a.out random':

          6,548.40 msec task-clock:u                     #    0.998 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
           327,743      page-faults:u                    #   50.049 K/sec
    24,066,674,277      cycles:u                         #    3.675 GHz                         (74.97%)
         9,285,235      stalled-cycles-frontend:u        #    0.04% frontend cycles idle        (74.97%)
    22,017,623,906      stalled-cycles-backend:u         #   91.49% backend cycles idle         (74.97%)
    10,675,727,650      instructions:u                   #    0.44  insn per cycle
                                                  #    2.06  stalled cycles per insn     (74.99%)
     2,009,815,326      branches:u                       #  306.917 M/sec                       (74.99%)
         2,533,997      branch-misses:u                  #    0.13% of all branches             (75.03%)
     4,585,865,236      L1-dcache-loads:u                #  700.304 M/sec                       (75.07%)
       164,580,961      L1-dcache-load-misses:u          #    3.59% of all L1-dcache accesses   (75.01%)
   <not supported>      LLC-loads:u
   <not supported>      LLC-load-misses:u

       6.558823309 seconds time elapsed

       6.087413000 seconds user
       0.460560000 seconds sys
```

```
Changing the order of the struct fields

❯ perf stat -d ./altered_struct baseline

 Performance counter stats for './altered_struct baseline':

          5,031.28 msec task-clock:u                     #    0.994 CPUs utilized             
                 0      context-switches:u               #    0.000 /sec                      
                 0      cpu-migrations:u                 #    0.000 /sec                      
           262,199      page-faults:u                    #   52.114 K/sec                     
    18,391,528,501      cycles:u                         #    3.655 GHz                         (74.93%)
         8,173,310      stalled-cycles-frontend:u        #    0.04% frontend cycles idle        (74.96%)
    16,442,368,498      stalled-cycles-backend:u         #   89.40% backend cycles idle         (75.03%)
    10,277,201,618      instructions:u                   #    0.56  insn per cycle            
                                                  #    1.60  stalled cycles per insn     (75.02%)
     1,941,579,851      branches:u                       #  385.902 M/sec                       (75.00%)
         2,446,143      branch-misses:u                  #    0.13% of all branches             (75.03%)
     4,371,501,553      L1-dcache-loads:u                #  868.865 M/sec                       (75.04%)
        87,987,608      L1-dcache-load-misses:u          #    2.01% of all L1-dcache accesses   (74.99%)
   <not supported>      LLC-loads:u                                                           
   <not supported>      LLC-load-misses:u                                                     

       5.060833927 seconds time elapsed

       4.667811000 seconds user
       0.358449000 seconds sys
❯ perf stat -d ./altered_struct ordered
Ordered: -1043987429 in 0.057s

 Performance counter stats for './altered_struct ordered':

          5,108.03 msec task-clock:u                     #    0.998 CPUs utilized             
                 0      context-switches:u               #    0.000 /sec                      
                 0      cpu-migrations:u                 #    0.000 /sec                      
           262,206      page-faults:u                    #   51.332 K/sec                     
    18,731,373,391      cycles:u                         #    3.667 GHz                         (74.97%)
         8,571,017      stalled-cycles-frontend:u        #    0.05% frontend cycles idle        (74.96%)
    16,732,743,337      stalled-cycles-backend:u         #   89.33% backend cycles idle         (74.98%)
    10,626,281,168      instructions:u                   #    0.57  insn per cycle            
                                                  #    1.57  stalled cycles per insn     (74.94%)
     2,008,809,458      branches:u                       #  393.265 M/sec                       (74.96%)
         2,452,333      branch-misses:u                  #    0.12% of all branches             (75.09%)
     4,510,449,314      L1-dcache-loads:u                #  883.011 M/sec                       (75.10%)
       100,754,109      L1-dcache-load-misses:u          #    2.23% of all L1-dcache accesses   (75.02%)
   <not supported>      LLC-loads:u                                                           
   <not supported>      LLC-load-misses:u                                                     

       5.116914265 seconds time elapsed

       4.732575000 seconds user
       0.375411000 seconds sys

```

| Cache                            | Baseline | Ordered       | Random       |
| -------------------------------- | -------- | ------------- | ------------ |
| L1 loads                         | 4.4B     | 4.5B (~+130M) | 4.6B         |
| L1 misses                        | 93M      | 109M (~+16M)  | 164M (~+71M) |
| L3 (not supported on my machine) |          |               |

With re-ordered struct
| Cache                            | Baseline | Ordered       | Random       |
| -------------------------------- | -------- | ------------- | ------------ |
| L1 loads                         | 4.4B     | 4.5B (~+100M) |          |
| L1 misses                        | 88M      | 100M (~+12M)  |   |
| L3 (not supported on my machine) |          |               |


