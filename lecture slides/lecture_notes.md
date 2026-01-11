OMP / MPI 

Shared Memory / Distributed Memory
Compiler Directives (#pragma omp ...)/(MPI_Send, MPI_Recv)
OMP is very efficient on single computer (memory<->cpu is very close) / MPI is better with a lot of nodes on supercomputer




Summary for exam by Illia Yakushevskyi : 

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
    - .hex is uploaded directly to chip, it's actually in hex but is a final step 

- Importance of compiler optimization and 
how can affect the results.
    - lecture 3; 20 time impovement from using gcc -O3 -ffast-math -mavx2 -o cpi cpi.c  over gcc -o cpi cpi.c


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
Top500 list
- Strong and weak scaling
- Latency and bandwidth.
- Memory, cache and bus (e.g., attached 
network or GPU card) hierarchy and their 
relative performance.
- Different ways of instrumenting 
(benchmarking) your code.



### OpenMP: 

•Directive based
•Model (shared memory, threads, a “thread” 
runs on a “core”)

designed to be run on one node 
•The serial and “parallel” (region) parts.
•The “parallel for” loop.
•Synchronization between threads, for 
example “reduce” clause, or “atomic” or 
“critical” pragmas. Performance of each.
•Shared versus private variables.
•How OpenMP schedules work between 
threads.


### MPI: 

•Model (distributed memory, message 
passing, a “rank” is a process).
    - MPI follows the Distributed Memory model where each process (rank) has its own private address space and cannot access another's memory directly. A Rank is a unique integer identifier assigned to a process within a communicator (e.g., MPI_COMM_WORLD), allowing for distinct logic paths in SPMD (Single Program, Multiple Data) execution.
    - Unlike OpenMP -- **provides communication** between prcesses, design for parallelism acros multiple nodes 


•How to split work between “ranks” (also 
known as load balancing or domain 
decomposition).
    - Domain Decomposition involves partitioning the global data set (e.g., a 2D grid) into sub-domains assigned to different ranks to allow parallel processing. Load Balancing is the practice of ensuring each rank performs an equal amount of computational work to prevent idle time at synchronization points. Static decomposition is determined at startup, while dynamic decomposition adjusts the workload during runtime to account for hardware or algorithmic imbalances.
•How to compile MPI programs (e.g., mpicc, 
cc, mpicxx, CC, etc.) — “wrappers”.
 
    - MPI programs are compiled using Wrappers like mpicc

•Some of the common functions (those 
covered in the lectures).
    - MPI_Init / MPI_Finalize: Respectively initialize and shut down the MPI execution environment.

    - MPI_Comm_size / MPI_Comm_rank: Determine the total number of processes and the calling process's unique ID.

    - MPI_Send / MPI_Recv: The fundamental blocking point-to-point communication routines for moving data between specific ranks.

    - MPI_Bcast / MPI_Reduce / MPI_Allreduce: Collective operations where one rank sends data to all others (Broadcast) or all ranks combine data into a single result on one rank (Reduce).

•How message passing works and common 
problems (e.g., deadlocks).
    - Message passing works by matching a Send in one rank with a corresponding Recv in another. A Deadlock occurs when processes are stuck indefinitely waiting for a message that will never arrive, often caused by circular dependencies (e.g., Rank A waits for Rank B, while Rank B waits for Rank A). To avoid deadlocks, developers use non-blocking routines (MPI_Isend/MPI_Irecv) or carefully ordered communication patterns.

- MPI code examples: 


### Hybrid Computing: 

•CPU “sockets” and “cores”, and GPU “SMs” and “cores”.
•SIMD (AVX) on CPUs and “Warps” on GPUs.
•CPU versus GPU
•CPU: small number of high performance cores and ~ one 
thead per core.
•GPU: large number of lower performance cores and many 
threads per core.
•Memory bandwidth to memory on each.
•Divergence: how it is handled on the CPU (SIMD) and on the GPU 
(Warps).
•Data alignment: what it is and why is it important.
•Latency hiding and Occupancy on GPUs. Latency to start kernels or 
data transfer. Latency of instruction on the GPU versus the CPU.


### OpenACC: 

•Directive Based
•Basic GPU operations: allocate, copy, kernel launch.
•Data management: how OpenACC gets your data to where 
it needs to be (GPU or CPU) and how you can steer this 
with a “data” construct.
•Difference between “kernels” construct and “parallel” 
construct.
•Difference between “grid”, “worker” and “vector”.
•Shared versus private variables.
•Synchronization on the GPU, for example “reduce” clause, 
or “atomic” or “critical” pragmas. Performance of each.
•What asynchronous operations do and way you would 
want to use them.

### CUDA: 

•How to compile CUDA code (nvcc).
•What a streaming multiprocessor (SM) is.
•What is a “grid”, “block”, “warp” and 
“thread” and how they relate to the SM.
•How indexing works. How to turn a thread 
and block index into a global index.

### Cloud & Containers: 

Difference between Cloud (Virtual Machines) and containers
•VM: a “virtual” computer. Has memory, CPUs, network, 
disks, etc.
•How to handle “persistence” with VMs and containers, e.g., 
“snapshots”.
•Ephemeral computing (create a resource, compute, throw 
away the resource).
•You are “root” in virtual machines and containers and what 
this means.
•Dockerhub: like github but for containers.
•How to access data
•images and snapshots for VMs; mounting host directories 
for containers.

### MapReduce: 

•Why the “compute” is sent to the “data” 
instead of the normal “HPC” way.
•Data model: write once and read (process) 
multiple times.
•What the “map” and “reduce” phases do.
•What are the “key” and “value”?
