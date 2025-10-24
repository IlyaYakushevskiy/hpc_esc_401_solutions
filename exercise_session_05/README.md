# Solutions to HW5 

## Ex1 

1) we need to implemet init_f, jacobi_step and norm_diff. All of those functions are highly paralelisable. To answer the first qiestion it suffices to read a comment to function : 

init_f: fill in the edges of matrix f with computing boundary() and and inner parts with with source() terms.

jacobi_step: Compute a Jacobi iteration to solve Poisson equation where we take update formula from exercise sheet.

norm_diff: compute norm between two matrixes as sum of squares of component-wise differences 

I must add that because of parameter rhs_function=2 , our source output is 0 
## Ex2 

created folder "poisson_solver_parallel" ; 

points 1) 2) 3) done 

## Ex3 

1) done 
2) added #pragma omp parallel for to second loop, num_n0++ is not attomic thus readinf incrementing and writing can happen at different times 
3) #pragma omp atomic update makes sure num is atomic 
4) serial version compiles 
gcc serial.c -o serial_version
iyakushe@eiger-ln004:~/hpc_esc_401_solutions/exercise_session_05/race_conditions> ./serial_version 
Size of integer array/file: 1000000
max number in file: 38747
number of 0s in file: 646016
true number of 0s in file: 646016s
---- 
Short question, why do we use .cpp (c++ file extension) if the code is in C? 