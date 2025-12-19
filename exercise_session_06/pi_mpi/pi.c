#include <stdio.h>
#include <sys/time.h>
#include "mpi.h"

static long nSteps = 1000000000;
static double PI25DT = 3.141592653589793238462643;

double getTime(void) {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec + 1e-6*(double)tv.tv_usec;
}

int main(int argc, char** argv){
    int myRank, nProcs;
    long i;
    double mypi, pi;
    double tStart, tElapsed;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&nProcs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

    tStart = getTime();
    mypi = 0.0;

    long start = myRank * (nSteps / nProcs);
    long end   = (myRank == nProcs-1) ? nSteps : (myRank + 1) * (nSteps / nProcs);

    for (i = start; i < end; i++) {
        double term = (i % 2 == 0 ? 1.0 : -1.0) / (2*i + 1);
        mypi += term;
    }
    mypi *= 4.0;

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    tElapsed = getTime() - tStart;

    if (myRank == 0){
        printf("pi is approximately %.16f, Error is %.16f\n",
               pi, pi - PI25DT);
        printf("Computed in %.4g seconds\n", tElapsed);
    }

    MPI_Finalize();
    return 0;
}
