cpi: cpi.c gettime.c
	cc -O3 -o cpi cpi.c gettime.c


# gettime.o: gettime.c gettime.h
# 	cc -O3 -c gettime.c

cpi_omp: cpi_omp.c
	cc -O3 -o cpi_omp -fopenmp cpi_omp.c 

cpi_mpi: cpi_mpi.c gettime.c
	mpicc -O3 -o cpi_mpi -fopenmp cpi_mpi.c gettime.c 

all: cpi cpi_omp cpi_mpi

clean:
	rm -f cpi_omp cpi_mpi
