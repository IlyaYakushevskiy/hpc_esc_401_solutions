#include "io.h"
#include "init.h"
#include "jacobi.h"

int main (int argc, char *argv[]){

    const char* file_name="params.txt";

    // Read the parameter file and store information in a params structure (defined in init.h)
    params p;
    readParameters(file_name, &p);

    // Initialize the matrices used in the Jacobi iteration
    double **f, **u_old, **u_new;

    // First allocate memory for each matrix
    f = allocateGrid(p.nx + 2, p.ny + 2, f);
    u_old = allocateGrid(p.nx + 2, p.ny + 2, u_old);
    u_new = allocateGrid(p.nx + 2, p.ny + 2, u_new);

    // Initialize the value of matrices
    init_variables(p, f, u_old, u_new);
    printf("initialization done.\n");
    // Output the source term of the Poisson equation in a csv file
    output_source(p, f);

    // Do a first jacobi step
    jacobi_step(p, u_new, u_old, f);
    printf("step 1 done.\n");

    // Compute differences and norm
    double diff = norm_diff(p, u_new, u_old);
    printf("Initial diff=%g\n", diff);
    // Initialize the Jacobi step conter
    int nstep=1;

    // Main loop for the Jacobi iterations
    while (diff>p.tol && nstep<p.nstep_max){
        jacobi_step(p, u_new, u_old, f);
        diff = norm_diff(p, u_new, u_old);
        nstep++;
        printf("Step %d, Diff=%g\n", nstep, diff);
        if (nstep%p.foutput==0)
            output(p, nstep, u_new);
    }
    return 0;
}
