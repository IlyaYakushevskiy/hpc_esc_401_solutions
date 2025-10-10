# Exercise Session 03 #
In this session, you will work on modularization of the code and compilation optimization. Moreover, you will parallelize a simple code and successively plot its speedup. 

In this folder you can find:

* cpi.c : the serial version of last week parallel code, needed for Exercise 1
* cpi_mpi.c : the MPI version of cpi code, for Exercise 1
* sum.c : the code needed for Exercise 2 

# My solutions 

## Ex1 

1) 2) created Makefile and separated GetTime() fct into .h file 

3) done v

4) outputed times are: 
Computed in 1.508 seconds
Computed in 1.51 seconds
 
some very little time was taken to compute those lines 
'''MPI_Finalize();
tElapsed = getTime() - tStart;'''

thus second time I a bit delayed. 

## Ex2

1) 2) 

for -O0: 
sum=10022429073.341873
Time taken in sec: 1.122

for -O1: 
sum=10022429073.341873
Time taken in sec: 1.107

for -O2: 
sum=10022429073.341873
Time taken in sec: 1.088

for -O3 : 
sum=10022429073.341873
Time taken in sec: 1.099

- I guess using the functions of MPI such as MPI_Wtime()
- in this particular example the difference was rather neglegible, maximm of order of magnitude 0.1 sec
- from IBM website : O0 no optimisation  O1 Eliminates redundant code
O2 Performs basic loop optimization
Structures code to take advantage of -mcpu and -mtune settings O3 initiates more intense low-level transformations that remove many of the limitations present at -O2
- one can make it faster with paralelisation 

3) I inserted the line before the for loop as was shown in lecture. I had to write a new run.job script and modify makfile to use fopenmp and math library 
on 128 cores it took 
sum=10022429072.084940
Time taken in sec: 0.08981

cores : times per sec 
5 0.6674
30 0.3493
64 0.1585
90 0.1248
110 0.09418
120 0.09368
128 0.08847

4) I've reused simple python from last task  script to plot it. It is honestly a bit dissapointing. The reason I think is that the problem is rather memory limited and not compute limited, we need time to read and write stuff and we could make it somehow faster, we see speedup converges to const which is expected with Amdahls law. 

## Ex3 

Superlinear speedup is primarily caused by memory cache Superlinear speedup usually happens because of cache effects.
When the work is split across many cores, each core gets a smaller chunk of data that can fit into its fast local cache.
This avoids slow memory access and makes the program run even faster than expected from just parallelization alone.