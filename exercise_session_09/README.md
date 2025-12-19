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

1) because of in[i] = out[i]; we copy data in/out of GPU every step, what we want is to copy array, compute blur, copy out 

dispersion 1D test of length n = 1048580 : 8.00003MB
==== success ====
Host version took 0.165376 s (0.00165376 s/step)
GPU version took 0.204623 s (0.00204623 s/step)

2) 

we fixed the problem pointed out in point 1 

Host version took 0.0639543 s (0.000639543 s/step)
GPU version took 0.0636279 s (0.000636279 s/step)


# Ex3 

1) the problem is that we dont reduce sum explicitly and some threads can access sum at the same time 

2) 
reduction(+:sum)

3) 
even though gpu was twice faster it's not a significant improvement, we would need to do more operations to excuse GPU usage 

dot product OpenACC of length n = 4 : 3.05176e-05MB
expected 42 got 42: success
Host kernel took 6.4e-08 s
GPU kernel took 3.2e-08 s