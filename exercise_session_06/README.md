# Exercise 6

## Ex1 

1) we see that the order of ranks is mixed in the output, which potentially can lead to deadlock. this happens because all processes send in parallel first and then all of them receive, we'd like to separate it 

2) I fixed it with a even odd separation , it works because if one rank sends in the end of the process, the next one will definitely recieve first and vice versa. But now the processes actually block each other, it's not optimal since it wouln't utilize all the bandwidth 

3) I implemented with MPI_Waitall() now all processes are sending and receiving synchronously

## Ex2  

1) I copied the template from the Week 2 excercise and created sub-directory pi_mpi/ I modified code to use specifically leibniz method  