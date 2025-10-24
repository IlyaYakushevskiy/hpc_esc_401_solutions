#include "jacobi.h"
#include <math.h>

/**
 * @brief      Computes norm of the difference between two matrices
 *
 * @param[in]  p     Parameters
 * @param      mat1  The matrix 1
 * @param      mat2  The matrix 2
 *
 * @return     Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){
    double norm_sq_sum = 0.0; 

    //#pragma omp parallel for collapse(2) reduction(+:norm_sq_sum) 
    for (int i = 1; i <= p.nx; i++){ 
        for (int j = 1; j <= p.ny; j++){ 
            norm_sq_sum += (mat1[i][j] - mat2[i][j]) * (mat1[i][j] - mat2[i][j]);
        }
    }
    return sqrt(norm_sq_sum / (double)(p.nx * p.ny)); 
}

/**
 * @brief      Compute a Jacobi iteration to solve Poisson equation. This function updates
 *             u_new and u_old in-place.
 *
 * @param[in]  p      Parameters
 * @param      u_new  The new solution
 * @param      u_old  The old solution
 * @param      f      The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f){
    double dx = 1.0 / (p.nx + 1); 
    double dy = 1.0 / (p.ny + 1); 

    //#pragma omp parallel for collapse(2) 
    for (int i = 0; i <= p.nx + 1; i++){
        for (int j = 0; j <= p.ny + 1; j++){
            u_old[i][j] = u_new[i][j]; 
        }
    }

    #pragma omp parallel for collapse(2) 
    for (int i = 1; i <= p.nx; i++){ 
        for (int j = 1; j <= p.ny; j++){ 
            u_new[i][j] = 0.25 * (u_old[i+1][j] + u_old[i-1][j] + 
                                  u_old[i][j+1] + u_old[i][j-1] - 
                                  dx*dy*f[i][j]);
        }
    }
}