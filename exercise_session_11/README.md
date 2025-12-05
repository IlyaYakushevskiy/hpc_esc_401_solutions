# HOMEWORK 11 

## Ex1
Cool! Make generated 2 executables, the original and the one with summary from craypat. The summary is quite informative, it goes over CPU specs and then most importantly tells where in our code cpu did the most of work, namely : 

**```**3||  82.7% | 1,045.0 | hpc_esc_401_solutions/exercise_session_11/nbody/nbody.cpp
||||-------------------------------------------------------------------------
4|||   2.8% |    36.0 | line.38
4|||  23.0% |   291.0 | line.39
4|||  56.8% |   718.0 | line.40
||||=========================================================================
3||  17.3% |   219.0 | c++/12/bits/stl_vector.h
4||        |         |  line.386
**```**

where we see those are lines to calculate forces which take take of the most time 
**```**
	    ax += dx * ir3;
	    ay += dy * ir3;
	    az += dz * ir3;
**```**        
it makes absolute sense since it's calculating update with the main formula which has O(n^2) complexity, namely $ F_ij = (M_i * M_j)* e_i / |r^3| $  

FULL OUTPUT made this readme very messy, so I'll include it separatly in HW11_1output.md

## Ex2 

from the last run we've seen Avg Process Time: "12.72 secs". Now we have something close but a bit worse. Now working on the sqrt() problem. 

**```**
iyakushe@eiger-ln004:~/hpc_esc_401_solutions/exercise_session_11/nbody> time ./nbody

real    0m12.828s
user    0m12.823s
sys     0m0.002s
**```**

Now the code works only with float level of precision. We cut the time almost in half, impressive! 

**```**
real    0m7.330s
user    0m7.245s
sys     0m0.000s
**```**

## Ex3 

Im vectorized the code and ,actually , it performs much worse now , I suspect a divergence which is a part of a next problem ... 
real    0m16.554s
user    0m16.550s
sys     0m0.001s

## Ex4 

We achieved vectorisation w/out divergence and awesome speedup!


real    0m1.543s
user    0m1.534s
sys     0m0.006s

## Ex5 

Using 128 cores on eiger, for N = 50'000 : 

Average around 3.47637 (more precise in /job_outputs)

Since we increase n by 10 times, complexity will be increased 100 times thus I'd expect for it around 5 min to run 

for N = 500000: 