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

FULL OUTPUT : 
**```**
CrayPat/X:  Version 23.12.0 Revision 67ffc52e7 sles15.4_x86_64  11/13/23 21:04:20

#################################################################
#                                                               #
#            CrayPat-lite Performance Statistics                #
#                                                               #
#################################################################

CrayPat/X:  Version 23.12.0 Revision 67ffc52e7 sles15.4_x86_64  11/13/23 21:04:20
Experiment:                  lite  lite-samples
Number of PEs (MPI ranks):      1
Numbers of PEs per Node:        1
Numbers of Threads per PE:      1
Number of Cores per Socket:    64
Execution start time:  Fri Dec  5 11:48:38 2025
System name and speed:  eiger-ln004  2.343 GHz (nominal)
AMD   Rome                 CPU  Family: 23  Model: 49  Stepping:  0
Core Performance Boost:  1 PE has CPB capability


Avg Process Time: 12.72 secs         
High Memory:       46.3 MiBytes 46.3 MiBytes per PE

Notes for table 1:

  This table shows functions that have significant exclusive sample
    hits, averaged across ranks.
  For further explanation, use:  pat_report -v -O samp_profile ...

Table 1:  Sample Profile by Function

  Samp% |    Samp | Group
        |         |  Function=[MAX10]
       
 100.0% | 1,264.0 | Total
|------------------------------------
| 100.0% | 1,264.0 | USER
||-----------------------------------
|| 100.0% | 1,264.0 | main
|====================================

Notes for table 2:

  This table shows functions, and line numbers within functions, that
    have significant exclusive sample hits, averaged across ranks.
  For further explanation, use:  pat_report -v -O samp_profile+src ...

Table 2:  Sample Profile by Group, Function, and Line

  Samp% |    Samp | Group
        |         |  Function=[MAX10]
        |         |   Source
        |         |    Line
       
 100.0% | 1,264.0 | Total
|----------------------------------------------------------------------------
| 100.0% | 1,264.0 | USER
||---------------------------------------------------------------------------
|| 100.0% | 1,264.0 | main
|||--------------------------------------------------------------------------
3||  82.7% | 1,045.0 | hpc_esc_401_solutions/exercise_session_11/nbody/nbody.cpp
||||-------------------------------------------------------------------------
4|||   2.8% |    36.0 | line.38
4|||  23.0% |   291.0 | line.39
4|||  56.8% |   718.0 | line.40
||||=========================================================================
3||  17.3% |   219.0 | c++/12/bits/stl_vector.h
4||        |         |  line.386
|============================================================================

Observation:  MPI utilization

    No suggestions were made because each node has only one rank.


Notes for table 3:

  This table shows memory traffic for numa nodes, taking for each numa
    node the maximum value across nodes. It also shows the balance in
    memory traffic by showing the top 3 and bottom 3 node values.
  For further explanation, use:  pat_report -v -O mem_bw ...

Table 3:  Memory Bandwidth by Numanode

  Memory |    Read |   Write |    Thread |  Memory |  Memory | Numanode
 Traffic |  Memory |  Memory |      Time | Traffic | Traffic | 
  GBytes | Traffic | Traffic |           |  GBytes |       / | 
         |  GBytes |  GBytes |           |   / Sec | Nominal | 
         |         |         |           |         |    Peak | 
|------------------------------------------------------------------------
|    0.03 |    0.03 |    0.00 | 12.691812 |    0.00 |    0.0% | numanode.5
|========================================================================

Notes for table 4:

  This table shows energy and power usage for the nodes with the
    maximum, mean, and minimum usage, as well as the sum of usage over
    all nodes.
    Energy and power for accelerators is also shown, if available.
  For further explanation, use:  pat_report -v -O program_energy ...

Table 4:  Program Energy and Power Usage from Cray PM

Total

  
===========================================================
  Total
-----------------------------------------------------------
  PM Energy Node    283 W     3,601 J
  PM Energy Cpu      94 W     1,194 J
  PM Energy Memory  140 W     1,785 J
  Process Time            12.720170 secs
===========================================================

Program invocation:  ./nbody

For a complete report with expanded tables and notes, run:
  pat_report /users/iyakushe/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+119383-1773762609s

For help identifying callers of particular functions:
  pat_report -O callers+src /users/iyakushe/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+119383-1773762609s
To see the entire call tree:
  pat_report -O calltree+src /users/iyakushe/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+119383-1773762609s

For interactive, graphical performance analysis, run:
  app2 /users/iyakushe/hpc_esc_401_solutions/exercise_session_11/nbody/nbody+119383-1773762609s
**```**

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