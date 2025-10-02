## Ex1 
 I merged the changes from my laptop and from eiger 

## Ex2
 What is cc? What does the flag -O3 do? What
would happens if we change this to -O0?

- cc is for C compiler, is a wrapper for gcc
- O3 uses the compiler optimisation of 3rd level. From lecture slide: O3 turns on all optimizations specified by -O2 and also turns on the -finline-functions,
-funswitch-loops, -fpredictive-commoning, -fgcse-after-reload and -ftree-vectorize options


- O0 No Optimization.

make has generated 
cc -O3 -o cpi_omp -fopenmp cpi_omp.c 

 module list

Currently Loaded Modules:
  1) craype-x86-rome
  2) libfabric/1.22.0
  3) craype-network-ofi
  4) xpmem/2.9.6-1.1_20240510205610__g087dc11fc19d
  5) perftools-base/23.12.0
  6) cpe/23.12
  7) cray/23.12
  8) gcc-native/12.3
  9) craype/2.7.30
 10) cray-dsmml/0.2.2
 11) cray-mpich/8.1.28
 12) cray-libsci/23.12.5
 13) PrgEnv-gnu/8.5.0

module avail (availible modules here )

---- /opt/cray/pe/lmod/modulefiles/mpi/gnu/12.0/ofi/1.0/cray-mpich/8.0 ----
   cray-hdf5-parallel/1.12.2.9    cray-parallel-netcdf/1.12.3.9
   cray-mpixlate/1.0.3

---------- /opt/cray/pe/lmod/modulefiles/comnet/gnu/12.0/ofi/1.0 ----------
   cray-mpich-abi/8.1.28    cray-mpich/8.1.28 (L)

--------------- /opt/cray/pe/lmod/modulefiles/mix_compilers 
   amd-mixed/6.1.0                     intel-mixed/2023.2.0        (D)
   aocc-mixed/4.1.0                    intel-mixed/2024.0
   cce-mixed/17.0.0                    intel-oneapi-mixed/2023.2.0 (D)
   gcc-native-mixed/12.3               intel-oneapi-mixed/2024.0
   intel-classic-mixed/2023.2.0 (D)    nvhpc-mixed/24.3
   intel-classic-mixed/2024.0          nvidia-mixed/24.3

module spider (spider is generally used to search for versions )


The following is a list of the modules and extensions currently available:

  Boost: Boost/1.78.0-python3, Boost/1.78.0
    Boost provides free peer-reviewed portable C++ source libraries. 

  CDI: CDI/2.2.4-parallel
    CDI is a C and Fortran Interface to access Climate and NWP model
    Data. Supported data formats are GRIB, netCDF, SERVICE, EXTRA and
    IEG. 

  CDO: CDO/1.9.10
    CDO is a collection of command line Operators to manipulate and
    analyse Climate and NWP model Data. 

## Ex3 

1) We see the information on jobs in partition debug. for sinfo about the certain user we could use flag -u f.e. queue -u $USER

2) we can add lines #SBATCH --output=output.log #SBATCH --error=errors.log

3) please look for results into folder job_ouputs, which I've created for cleanliness 

4) we ran both mpi and omp on 128 cores of 1 node


for mpi without flag: pi is approximately 3.1415942652566006, Error is 0.0000000006668075
Computed in 4.491 seconds

for mpi with cpu-bind: 
Process rank: 0
pi is approximately 3.1415926542566006, Error is 0.0000000006668075
Computed in 4.517 seconds

for omp: 
pi is approximately 3.1415926542564692, Error is 0.0000000006666760
Computed in 0.1079 seconds

flag cpu bind does bind process to a cpu and in our case it made things a bit slower. 
we see that mpi most probably didn't paralelise code since the speed is by magnitude slower and only rank 0 is reported in output log

5) squeue --format="%.10i %.9u %.10p %.12a %.20j %.6D %.2t %.25r %.20S %.10L %.10p"

## Ex4

1) with  OMP_NUM_THREADS=1 : 
pi is approximately 3.1415926542566006, Error is 0.0000000006668075
Computed in 4.462 seconds

with  OMP_NUM_THREADS=10 : 
pi is approximately 3.1415926542564856, Error is 0.0000000006666925
Computed in 0.9342 seconds

omp with complier optimisation O0(a huge difference in compiling time!!!): 

pi is approximately 3.1458395987494163, Error is 0.0042469451596232
Computed in 23.51 seconds

What we see in first 2 cases is predictable boost of performance in 5 times, the reason why it didn't scale 10 tomes , as amount of thread is a result of Amdahls law -- we can get rid of a serial part so with cores -> inf the runtime will converge to serial part. In third case we actually felt that compiler optimisation matters sufficiently. 

## Bonus Task 

I've first looped over given parameters in new .job script, got the numbers, converted to array of runtimes and plotted against the n of threads with python. Please refer to runtimes_plot.png