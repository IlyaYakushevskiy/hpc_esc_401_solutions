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

--------------- /opt/cray/pe/lmod/modulefiles/mix_compilers ---------------
   amd-mixed/6.1.0                     intel-mixed/2023.2.0        (D)
   aocc-mixed/4.1.0                    intel-mixed/2024.0
   cce-mixed/17.0.0                    intel-oneapi-mixed/2023.2.0 (D)
   gcc-native-mixed/12.3               intel-oneapi-mixed/2024.0
   intel-classic-mixed/2023.2.0 (D)    nvhpc-mixed/24.3
   intel-classic-mixed/2024.0          nvidia-mixed/24.3

module spider (spider is generally used to search for versions )

-----------------------------------------------------------------------
The following is a list of the modules and extensions currently available:
-----------------------------------------------------------------------
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

3) 