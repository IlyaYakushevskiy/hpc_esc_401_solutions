#include "mpi.h"
#include <stdio.h>
#include "init.h"

int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
	/*
	define corners or local domains
	*/


	// using method 1
	*min_y = 1;
    *max_y = ny - 2; 	

	int interior_cols = nx - 2;
	int chunk = interior_cols / size;
	int remainder = interior_cols % size;


	int my_start_col_index;
    int my_num_cols;

	if (my_rank < remainder) {
        my_num_cols = chunk + 1;
        my_start_col_index = my_rank * my_num_cols;
    } else {
        my_num_cols = chunk;
        my_start_col_index = (remainder * (chunk + 1)) + (my_rank - remainder) * chunk;
    }

	*min_x = my_start_col_index + 1;
    *max_x = *min_x + my_num_cols - 1;

	if (my_num_cols == 0) {
        *max_x = *min_x - 1; 
    }

    printf("in mpi_get_domain() in mpi_module.cpp,  define corners of the local domains\n");

	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){
    

    int num_cols = p.xmax - p.xmin + 1;

    if (num_cols == 0) {
        return 0;
    }

    
    int col_height = p.ymax - p.ymin + 1;

    
    for (int j=0; j < col_height; j++) {
        fromLeft[j] = 0.0;
        fromRight[j] = 0.0;
    }

    
    int rank_left = (my_rank == 0) ? MPI_PROC_NULL : my_rank - 1;
    int rank_right = (my_rank == size - 1) ? MPI_PROC_NULL : my_rank + 1;

    
    
    
    
    double* column_to_right = new double [col_height];
    double* column_to_left = new double [col_height];

    
    int last_col_index = p.xmax - p.xmin; 
    int first_col_index = 0;              

    for (int j=0; j < col_height; j++) {
        column_to_right[j] = u[last_col_index][j]; 
        column_to_left[j] = u[first_col_index][j]; 
    }
    
    
    
    MPI_Request reqs[4];
    MPI_Status stats[4];
    int num_requests = 0;

    //sending receiving non-blocking messages
    
    MPI_Irecv(fromLeft, col_height, MPI_DOUBLE, rank_left, 0, MPI_COMM_WORLD, &reqs[num_requests++]);
    
    MPI_Irecv(fromRight, col_height, MPI_DOUBLE, rank_right, 1, MPI_COMM_WORLD, &reqs[num_requests++]);    

    
    
    MPI_Isend(column_to_left, col_height, MPI_DOUBLE, rank_left, 1, MPI_COMM_WORLD, &reqs[num_requests++]);
    
    MPI_Isend(column_to_right, col_height, MPI_DOUBLE, rank_right, 0, MPI_COMM_WORLD, &reqs[num_requests++]);


    MPI_Waitall(num_requests, reqs, stats);

    delete[] column_to_right;
    delete[] column_to_left;


    return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

