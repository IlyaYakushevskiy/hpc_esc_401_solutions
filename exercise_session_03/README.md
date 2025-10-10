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

MPI_Finalize();
tElapsed = getTime() - tStart;
thus second time I a bit delayed. 

## Ex2