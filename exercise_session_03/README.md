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

