# Short Summary for the HPC exam by Illia Yakushevskyi : 

### Compiler and Queues: 
- Version control (e.g. “git”): clone, pull, add, 
commit, push.
    - while we treat 1 copy on github as a main one, it's just 1 another copy without being higher in hierarchy -- no need to be connected to server as in SVN (Sebersion)
    Git is **distributed** -> branching is light 

- Phases of a compiler (compile, link).
    - ![alt text](<img/Screenshot 2026-01-08 at 11.31.39.png>)
    - Front end : get atomic tokens like "if" , check for syntax errors and create a parse tree 
    - parse tree : A "root" might be a Statement, which has "children" like Expression or Assignment. e.g. brackets are always above 
    - .s are assembly files , they are converted into machine object 
    - .elf is all files linked 
    - .hex is uploaded directly to chip, it's actually in hex but is a final step -
    - f.e. mpicc wrapper links linked obj files with mpi software in "Lib"

- Importance of compiler optimization and 
how can affect the results.
    - makes star
    - lecture 3; 20 time impovement from using gcc -O3 -ffast-math -mavx2 -o cpi cpi.c  over gcc -o cpi cpi.c (it breaks IEEE 754 compliance for speed) 


- Basics of “make” (lecture 3)
    - tracks file dependencies to ensure only modified 
    
    parts are recompiled, saving time. 

    ```
    target: dependencies
        system_command
    ```

    e.g.
    ```cpi_omp: cpi_omp.c
        cc -O3 -o cpi_omp -fopenmp cpi_omp.c 
            cpi_mpi: cpi_mpi.c
                mpicc -O3 -o cpi_mpi -fopenmp cpi_mpi.c  
            all: cpi_omp cpi_mpi
            clean:
                rm -f cpi_omp cpi_mpi
    ```



- Purpose and function of batch queue 
systems (e.g. SLURM). Scheduling: priority 
versus FIFO. How you request resources 
(nodes, cores, etc.) Performance: 
    - SLURM uses Multifactor Priority Queue : it gives all jobs a prioriy score ![alt text](<img/Screenshot 2026-01-08 at 11.57.42.png>)
    ![alt text](<img/Screenshot 2026-01-08 at 14.41.00.png>)

    - for MPI (distributed memory model), ranks commiunicate over bus: --ntasks-per-node=36 and --cpus-per-task=1
    - OpenMP: --ntasks-per-node=1 and --cpus-per-task=36



- Moore’s Law and how it relates to the 
Top500 list ( lecture 7)
- Strong and weak scaling (lecture)
    - strong scaling (Amdahls Law): goal is to decrease the runtime of problem of the same time 
    Speedup(N)= T_serial / T_parallel(N)  SpeedUp ->inf 
    ![alt text](<img/Screenshot 2026-01-14 at 12.02.10.png>)
    - alpha is serial!! 
    - weak scaling : (scale speedup adding more resources) aim to solve a larger problem in the same amount of time by scaling the problem size proportionally with the number of processors.
    Speedup(N)=α+(1−α)N SpeedUp ->inf 

- Latency and bandwidth.
    - infiniband is go to for latency and bacndwidth
    -  Latency is the "speed limit" of physics, while bandwidth is tied to the number of parallel paths and the signaling rate of the hardware (how much data you moduldate on the wave)
- Memory, cache and bus (e.g., attached network or GPU card) hierarchy and their relative performance.
    - L1..3 are faster cause they use SRAM (6 transistor/bit, expensisive) vs DRAM (dynamic RAM, 1 capacitor/bit ) 
    ![alt text](<img/Screenshot 2026-01-13 at 15.27.36.png>)

- Different ways of instrumenting 
(benchmarking) your code.
    - gcc -g  flaf Produces debugging information in the operating system's native format
    - use high res clc std::chrono::high_resolution_clock
    - use Craypat


### OpenMP: 

- Directive based
    - pragma is "suplementary information" seen as a comment by C compiler and compiled by the other wrapper files -- if omp is diabled, the C code still works without problems 
    - parallelise only what's within pragma scope 

- Model (shared memory, threads, a “thread” runs on a “core”)
    - an OpenMP program is executed by only one process, called the Master thread
    - programmer adds #pragma omp instructions to C/C++ to guide the compiler. It uses a Shared Memory model where multiple Threads (lightweight execution units) all access the same global memory space simultaneously. Typically, a "thread" is mapped to a physical CPU Core, and the entire program is restricted to running on a single node because it cannot communicate across networks like MPI.
    - thread vs cores: In practice, the situation is complex. Threads can be migrated across cores by the operating system, ideally 1 thread one core, if several threads per core then it's just serial 
    - has global variables s.a. export OMP_NUM_THREADS=4
    


- The serial and “parallel” (region) parts.
    - a program begins as a single Serial (master thread 0) thread, all the serial parts are rank 0. When a #pragma omp parallel directive is reached, the Master thread Forks a team of worker threads to execute the code within that block (the Parallel Region). Once the block ends, threads Join (synchronize and terminate), leaving only the Master thread to continue serial execution.
    - parallel region defined 
    ```
        #ifdef _OPENMP
                p = omp_in_parallel();
        #endif
    ```

- The “parallel for” loop.
    - pragma transforms the loop: parallel version doesnt have indexes, disctribution scheduled by **schedule** clause 
    - optimal : #pragma omp parallel for  instead of #pragma omp parallel  
    #pragma omp for 


- Synchronization between threads, for  example “reduce” clause, or “atomic” or “critical” pragmas. Performance of each.
    - in a parallel loop, if one needs to perform a global operation, one uses the reduction clause.          
    - Without reduction(+:sum), the variable sum is treated as shared by default -> data race 
    - #pragma omp barrier forces the synchronization of all threads within a parallel region
    - data racing happens when 2 processes update one variable and 2nd make update on the old varible so the sum uses old number 
    - #pragma omp atomic is alternative to reduce, usees low-level instructions, locks the variable ![alt text](<img/Screenshot 2026-01-12 at 17.35.12.png>) 
    - #pragma omp critical is more generic, order of execution is non-deterministic, less efficient that atomic 
    - Consider using the if (n>1024) clause in the SCHEDULE directive.


- Shared versus private variables.
    - The default(none) clause is a "safety first": It forces you to explicitly declare whether every variable used inside a parallel region is shared or private. 
    - #pragma omp parallel default(none) shared(a) OR  private(a) 
    - When you declare private(a), OpenMP creates a brand new, local copy of that variable for every single thread. May not be initialized by the compiler
    - Variables with firstprivate inherit the value of the global variable, but are then private.
    ```
    #pragma omp parallel\
                default(none)\
                firstprivate(a)
    ```
    -schedule(static, 128), you are telling OpenMP to give each thread a "chunk" of 128 iterations at a time in folowing fashion:

    Thread 0 gets iterations 0–127.

    Thread 1 gets 128–255.

    - if #pragma before the {} - all bracket is parallel , if before fct(); , only 1 line is parallel 
- How OpenMP schedules work between threads.
    - Dynamical Forking : 
    ```
    #pragma omp parallel num_threads(2)
    printf("hello\n");
    #pragma omp parallel num_threads(3)
    printf("hi\n");
    ```

-  code examples : 
    - compilation by gcc -fopenmp prog.c 
    - if 2 loops : 
    ```
    #pragma omp parallel for collapse(2) 
    for (int i = 1; i <= p.nx; i++){ 
        for (int j = 1; j <= p.ny; j++){ 
            u_new[i][j] = 0.25 * (u_old[i+1][j] + u_old[i-1][j] + 
                                  u_old[i][j+1] + u_old[i][j-1] - 
                                  dx*dy*f[i][j]);
        }
    }
    ```





### MPI: 

- Model (distributed memory, message 
passing, a “rank” is a process).
    -  MPI follows the Distributed **Memory** -- data itself is decomposed and distributed explicitly. each process (rank) has its own private address space and cannot access another's memory directly. A Rank is a unique integer identifier assigned to a process within a communicator (e.g., MPI_COMM_WORLD), allowing for distinct logic paths in **SPMD** (Single Program, Multiple Data) execution.
    -  Unlike OpenMP --  **provides communication** between processes, design for parallelism acros multiple nodes 
    - makes several copies of your .c file, varies only rank 

- Message Attributes
    ``` 
    int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
    ```
    - buf - initial address of send buffer (choice)
    -  count - number of elements in send buffer (nonnegative integer)
    - datatype (Mpi uses custom datatypes s.a. MPI_SIGNED_CHAR, MPI_DOUBLE,MPI_UINT16_T)
    - dest rank of destination (integer)
    - tag - message tag (integer)
    - comm - communicator (handle)
        


- How to split work between “ranks” (also known as load balancing or domain decomposition).
    -  Domain Decomposition involves partitioning the global data set (e.g., a 2D grid) into sub- domains assigned to different ranks to allow parallel processing. Load Balancing is the practice of ensuring each rank performs an equal amount of computational work to prevent idle time at synchronization points. Static decomposition is determined at startup, while dynamic decomposition adjusts the workload during runtime to account for hardware or algorithmic imbalances.


- How to compile MPI programs (e.g., mpicc, cc, mpicxx, CC, etc.) — “wrappers”.
 
    -  MPI programs are compiled using Wrappers like mpicc

- Some of the common functions (those covered in the lectures).
    -  MPI_Init / MPI_Finalize / MPI_Abort: Respectively initialize and shut down the MPI execution environment.

    -  MPI_Comm_size / MPI_Comm_rank: Determine the total number of processes and the calling process's unique ID.

    -  MPI_Send / MPI_Recv: The fundamental *blocking* point-to-point communication routines for moving data between specific ranks.
        ```
        int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
        ```

        - status receives information about the communication: source, tag, error codes...
        - this call is blocking. The execution remains 
        blocked until the message is fully received and stored in buf
        - buffer is a pointer to conigous block of memory with reerved count * sizeof(datatype) bytes
    -  MPI_Reduce / MPI_Allreduce: Collective operations where one rank sends data to all others (Broadcast) or all ranks combine data into a single result on one rank (Reduce).
    - MPI_Bcast -- sends a message with rank "root" to all other processes, root is chosen by  programmer


    ```
    int MPI_Bcast( void *buffer, int count, MPI_Datatype datatype, int root,MPI_Comm comm )
    ```
    ![alt text](<img/Screenshot 2026-01-13 at 14.27.03.png>)
    
    - MPI_Scatter - send from one process to all others ![alt text](<img/Screenshot 2026-01-13 at 14.27.11.png>)
    - for further fct check lecture 6, has good example 

- Non-blocking Functions (No risk of deadlock but risk of memory leak if the communication is not properly terminated.)

    - MPI_ISend / MPI_IRECV() - non-blocking send: You must not touch the buffer until you have called MPI_Wait or MPI_Test to confirm the transfer is finished.
    - MPI_WAIT()

- How message passing works and common problems (e.g., deadlocks).
    - Message passing works by matching a Send in one rank with a corresponding Recv in another. A Deadlock occurs when processes are stuck indefinitely waiting for a message that will never arrive, often caused by circular dependencies (e.g., Rank A waits for Rank B, while Rank B waits for Rank A). To avoid deadlocks, developers use non-blocking routines (MPI_Isend/MPI_Irecv) or carefully ordered communication patterns.
    - Collective Communications  (bring several ranks values to one rank):   
        - it's blocking : it's finished only when every subroutine is completed 
        - Global synchronization MPI_BARRIER()
        - MPI_REDUCE() 


- OMP vs MPI: 
    - huge problems like weather forcausting would expect distributed memory, so MPI only
    - MPI is well scalable 
    - Omp would be great for MonteCarlo simulation runing a lot of if statemens (smaller, tighter loops or frequent synchronization)
- MPI code examples: 
if you need simulaneosly exchange message of same var 
```
MPI_Sendrecv(&send_val, 1, MPI_INT, 1, 0, &recv_val, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
```
- Example : **Deadlock MPI**
```
// Assume 2 Ranks: Rank 0 and Rank 1
if (rank == 0) {
    // Rank 0 tries to receive from Rank 1 first
    MPI_Recv(buf, count, MPI_INT, 1, tag, MPI_COMM_WORLD, &status); // is blocking receive, will never run
    MPI_Send(buf, count, MPI_INT, 1, tag, MPI_COMM_WORLD);
} 
else if (rank == 1) {
    // Rank 1 also tries to receive from Rank 0 first
    MPI_Recv(buf, count, MPI_INT, 0, tag, MPI_COMM_WORLD, &status); 
    MPI_Send(buf, count, MPI_INT, 0, tag, MPI_COMM_WORLD);
}
```

FIX : 

```
if (rank == 0) {
    MPI_Send(...); MPI_Recv(...); 
} else {
    MPI_Recv(...); MPI_Send(...); 
}
```


### Hybrid Computing: 

- CPU “sockets” and “cores”, and GPU “SMs” and “cores”.
    - Typically 8 to 128 cores per socket, socket is actual place on motherboard
    - SM : Srteaming Multiprocessor, H100 has 132SMs,  The SM contains the shared L1 cache/SRAM and the scheduling logic
    - "Workers" -- CUDA Cores These are the  inside the SM. Unlike CPU cores, CUDA cores are very simple; they don't make their own decisions. They all follow the same instruction given by the SM but on different pieces of data 16,896 CUDA cores on an H100

- SIMD (AVX) on CPUs and “Warps” on GPUs.
    

- CPU versus GPU
    - 4TB DDR5 for CPU (per 8 cores)>> 80GB (per 16000 cores) VRAM GPU 
    - CPU has faster clock 
    - GPU puts more transistors into compute SMs

- CPU: small number of high performance cores and ~ one thead per core.


- GPU: large number of lower performance cores and many threads per core.

- Memory bandwidth to memory on each.
- Divergence: how it is handled on the CPU (SIMD) and on the GPU (Warps).
    - #TODO
- Data alignment: what it is and why is it important.
    - for vectorisation 
- Latency hiding and Occupancy on GPUs. Latency to start kernels or data transfer. Latency of instruction on the GPU versus the CPU.
    - When a group of threads (a Warp) hits a memory "stall," the GPU's scheduler instantly swaps it out for another Warp that is ready to perform a calculation.

### OpenACC: 

- Directive Based
    - like openMP
    - compiled with nvidia sdk nvc++ -O3 -acc 
    - unlike CUDA, OpenACC is a highlevel directive base hpc framework from nvidia (runs on all videocards tho)
    - hides latency automatically 



- Basic GPU operations: allocate, copy, kernel launch.
    - allocate: create/ pcreate (or present_or_create) create(array[n])
    is a data management clause used to handle memory allocation between the CPU and the GPU.
    - copyin does allocation as well , no pcreate needed
    ```
    #pragma acc data copyin(a,b) copy(c)
    #pragma acc kernels
    #pragma acc loop independent
    for(int i=0; i<n; ++i) {
        #pragma acc loop independent
        for(int j=0; j<n; ++j) {
            #pragma acc loop seq
            for(int k=0; k<n; ++k) {
            c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    ```

- Data management: how OpenACC gets your data to where it needs to be (GPU or CPU) and how you can steer this with a “data” construct.
    - #pragma acc data clauses
    - #pragma acc parallel loop


- Difference between “kernels” construct and “parallel” construct.
    - kernel is hinting to the compiler, compiler may decide to parallelise, parallel is assertion 
    - #pragma acc kernels {}
    - #pragma acc parallel {}


- Difference between “grid”, “worker” and “vector”.
    - max 1024 thread per block 
    - Gang (Highest Level, SM): This corresponds to a Thread Block in CUDA or an SM (Streaming Multiprocessor) on the hardware. Gangs are completely independent; they cannot easily talk to each other and might run in any order.

    - Worker (Middle Level): These are groups of threads within a single gang. Most modern NVIDIA GPUs don't use this level heavily; it’s often skipped in favor of the vector level.

    - Vector (Lowest Level): This corresponds to the CUDA threads or a Warp. These threads work in "lock-step," meaning they all execute the exact same instruction at the same time on different data (SIMD).

    ``` 
    #pragma acc parallel loop gang
    for(int i=0; i<n; ++i)
    #pragma acc loop vector
    for(int j=0; j<n; ++j)
    ```
- Shared versus private variables.
    - Scalar and loop index variables are private by default to each thread. VARIABLES INSIDE of Loop are private 
        - the loop index is private, but other variables might default to shared unless *default(none)* is used.
    - accessible by all threads within a gang (SM), if use copy are shared by default 

- Synchronization on the GPU, for example “reduce” clause, or “atomic” or “critical” pragmas. Performance of each.
    - An implicit synchronization happens when leaving a “kernels” or “parallel” region

    ```
    #pragma acc parallel
    #pragma acc loop reduction(+:sum) private(x)
    for (i=0; i < steps; i++) {
        x = (i+0.5)*step;
        sum += 4.0 / (1.0+x*x);
    }
 
    ```

- What asynchronous operations do and way you would want to use them.
    - By adding the async clause, the CPU launches a kernel or starts a data copy and immediately moves to the next line of code without waiting for the GPU to finish
    - maximises throughput 
    ![alt text](<img/Screenshot 2026-01-14 at 09.57.23.png>)
    - update manually synchronizes a specific "block" of the image from the CPU to the GPU. We use it here instead of copying the whole image at once to save memory and allow for "pipelining".
    - async(block % 3 + 1)	Overlaps data transfers with kernel execution using multiple streams. 

- Examples: 
    ```
    void matrix_multiply(int n, double **a, double **b, double **c) {
    // 1. DATA MANAGEMENT: Keep data on GPU to avoid the slow CPU-GPU bus
    // We use pcreate for 'c' if it's just a result buffer, or copy if it has initial values
    #pragma acc data copyin(a[0:n][0:n], b[0:n][0:n]) copy(c[0:n][0:n])
    {
        // 2. KERNEL LAUNCH: Using 'parallel' for explicit control (Programmer-driven)
        // This allows us to hide the 368-cycle memory latency with enough threads
        #pragma acc parallel loop gang vector_length(32)
        for(int i=0; i<n; ++i) {
            
            // 3. HIERARCHY: Outer loop is 'gang' (SM level), inner is 'vector' (Warp level)
            // This ensures we reach high occupancy (ideally 2048 threads per SM)
            #pragma acc loop vector
            for(int j=0; j<n; ++j) {
                
                double sum = 0.0; // Local variable stays in fast Registers (SRAM)
                
                // 4. SEQUENTIAL INNER: The 'k' loop must be 'seq' to avoid race conditions
                // but 'sum' is stored in a register to hide VRAM access delay
                #pragma acc loop seq
                for(int k=0; k<n; ++k) {
                    sum += a[i][k] * b[k][j];
                }
                c[i][j] = sum;
            }
        }
    }
    ```

### CUDA: 

- How to compile CUDA code (nvcc). / Basics 
    - nvcc hello_world.cu
    - host -cpu , device - gpu
    - The __global__ keyword means that the “add” function will be run on the device and called from the host
    ```
    __global__ void
    mykernel(void) {
    }
    int main(void) {
        mykernel<<<1,1>>>(); // <<<blocks,threads per block>>>
        printf("Hello World!\n");
        return 0;
    }
    ```
    - FLOPS/byte transfered matters: For an A100, this is roughly 150 to 200 FLOPs per 1 byte of memory access
        - Arithmetic: Takes 6 cycles.
        Memory Access: Takes 368 cycles.

    - e.g. , returns cuda error code 
    ```
    _host__ ​ __device__ ​cudaError_t 	cudaMalloc ( void** devPtr, size_t size ); 
    ```


- What a streaming multiprocessor (SM) is.
    - 1 computing "core", streaming cause it always computes no matter what to hide latency 

- What is a “grid”, “block”, “warp” and “thread” and how they relate to the SM.
    - Grid: The entire job you send to the GPU (e.g., "Rotate this 4K image").

    - Block: The grid is split into blocks. Each block is assigned to a single SM. Threads in the same block can share that fast on-chip SRAM (Shared Memory)

    - Warp (The "Unit of Work"): This is the most important level for performance. A Warp is a group of 32 threads that are *executed at the exact same time* on the CUDA cores. (don't care about them in actual programming , makes sence only for warm divergence )

    - SIMT (Single Instruction, Multiple Threads): If one thread in a warp has to do an if statement and the others don't, the whole warp slows down. This is called Warp Divergence.

    - Thread: The smallest unit, responsible for calculating a single pixel or a single number.


- How **indexing** works. How to turn a thread and block index into a global index.
    - threadIdx.x: The index of the thread within its current block. If a block has
    256 threads, this ranges from 0 to 255.
    - blockIdx.x: The index of the block within the entire grid.
    - blockDim.x: The size (number of threads) of a single block. This is a constant for all blocks in a kernel launch
    - gridDim.x: The total number of blocks in the grid.
    - global_index=(blockIdx.x×blockDim.x)+threadIdx.x
    - sometime you need to create more : *Ceiling Division*
    ```
    int numBlocks = (N + BLOCKSIZE - 1) / BLOCKSIZE;
    kern_set_val<<<numBlocks, BLOCKSIZE>>>(gpu_ptr, value, N)
    ```



- Code Examples: 

```
int main(void) {
	int *a, *b, *c;	// host copies of a, b, c
	int *a_d, *b_d, *c_d;	// device copies of a, b, c
	int size = N * sizeof(int);
	
	// Alloc space for device copies of a, b, c
	cudaMalloc((void **)&a_d, size);
	cudaMalloc((void **)&b_d, size);
	cudaMalloc((void **)&c_d, size);

	// Alloc space for host copies of a, b, c and setup input values
	a = (int *)malloc(size); random_ints(a, N);
	b = (int *)malloc(size); random_ints(b, N);
	c = (int *)malloc(size);

	// Copy inputs to device
	cudaMemcpy(a_d, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(b_d, b, size, cudaMemcpyHostToDevice);

	// Launch add() kernel on GPU, add() is a function defined in global scope earlier 
	add<<<N,1>>>(a_d, b_d, c_d);
	
	// Copy result back to host
	cudaMemcpy(c, c_d, size, cudaMemcpyDeviceToHost);
		
    // Print results
	for(int i=0; i<N; i++)printf("%d) %d + %d = %d\n",i,a[i],b[i],c[i]);
        	
    // Cleanup
    free(a); free(b); free(c);
	cudaFree(a_d); cudaFree(b_d); cudaFree(c_d);
	return 0;
} 
```


### Cloud & Containers: 

- Difference between Cloud (Virtual Machines) and containers
    - VM: Full OS, Snapshot = Disk + RAM, Root = Full machine control.
    - Container: Shared Kernel, Volumes = Persistence, Root = Isolated control.
    - VM: a “virtual” computer. Has memory, CPUs, network, disks, etc.
        - emulates hardware of other machine, has drivers of other machine etc 
        - includes its own Guest Operating System
        - ontainer: A lightweight package that shares the Host Operating System's kernel. It only contains the application and its specific dependencies, making it much smaller and faster to start than a VM.

- How to handle “persistence” with VMs and containers, e.g., “snapshots”.
    - "point-in-time" image of a VM's entire state, including the disk and sometimes memory. If a VM crashes, you can roll back to a previous snapshot
    - Persistence in Containers: Because containers are designed to be temporary, data written inside them is lost when they stop. To keep data, you must use External Volumes or "mount" directories from the host.

- Ephemeral computing (create a resource, compute, throw away the resource).
    - This is a "cloud-native" strategy where resources are treated as disposable.

    - Concept: You create a resource (VM or Container), perform a specific computation, and immediately throw away the resource.

    - Benefit: This ensures you only pay for the exact seconds of compute time you use and prevents "configuration drift" where old servers become messy over time.

- You are “root” in virtual machines and containers and what this means.
    - You have total control to install software, change configurations, and manage users.
    - While you are "root" inside a container, the isolation layers prevent you from being "root" on the physical host machine, protecting the rest of the cloud infrastructure.


- How to access data
    - Data Access in VMs: Usually involves creating a virtual disk image or taking a snapshot to move large amounts of data.

    - Data Access in Containers: Primarily done by mounting host directories. This maps a folder on your physical computer directly into the container so the app can read/write files in real-time.


- images and snapshots for VMs; mounting host directories for containers.


### MapReduce: 

- Why the “compute” is sent to the “data” instead of the normal “HPC” way.
    - You move the "compute" (the small code/program) to the nodes where the data already sits.
    - Sending a few kilobytes of code over a network is much faster and cheaper than moving terabytes of data. This minimizes network congestion and utilizes the local disk I/O of each server.
    - data distribution, schdulnig done by hadoop with RAID defined by machine, programmer only needs to write once, and then write code in map and reduce manner

- Data model: write once and read (process) multiple times.
    - Write Once: Data is loaded into the distributed file system in large chunks and is generally immutable (it doesn't change).

    - Read Multiple Times: Different "Map" jobs can then scan this same data multiple times to extract different insights.

    - Benefit: This simplifies "Persistence" and error recovery. If a node fails during a calculation, you don't have to worry about "half-finished" writes; you just restart the task on another node using the original, unchanged data.


- What the “map” and “reduce” phases do.
    - MAP: A chunk of raw data. Action: The "Mapper" function processes the data and outputs a list of intermediate Key-Value pairs. Highly paralelisable task 
    - Shuffle/Sort (The "Hidden" Phase): The system automatically moves all pairs with the same Key to the same "Reducer" node.
    - REDUCE Input: All values associated with a specific key (e.g., "apple" -> [1, 1, 1, 1]). Action: The "Reducer" function aggregates these values into a final result (e.g., "apple" -> 4).


- What are the “key” and “value”?
    - Key (k): An identifier used to group data together (e.g., a "Word" in a text file or a "User ID" in a log).

    - Value (v): The data associated with that key (e.g., the number "1" or a timestamp).

    - Example: If you are counting words, a pair would look like ("apple", 1).