## Homework 9 

# Ex1
This task touches the topic of operations/bytes we discussed on lectures. Shortly, there's no point in doing gpu paralelism for little amount of operations like in our case, because the bandwidth is always limited. Also on gpu it take more time to initalize kernel. However CPU cache memory is very close, so we rund out of cache 

- n = 1: 
axpy (openmp): 0.0621312 s
axpy (openacc): 3.41052 s

- n = 2:

axpy (openmp): 0.0626829 s
axpy (openacc): 2.8365 s

- n = 4: 

axpy (openmp): 0.0622097 s
axpy (openacc): 2.82347 s

- n = 16: 
axpy (openmp): 0.0621974 s
axpy (openacc): 2.82384 s

- n = 20 (I overrode max value): 

axpy (openmp): 0.062584 s
axpy (openacc): 3.40031 s <- here finally problem is big enough

- n = 30: 
axpy (openmp): 0.106962 s <- here we presumably can not use L1/l2/l3 anymore and must use DRAM 
axpy (openacc): 3.16553 s

# Ex2 
