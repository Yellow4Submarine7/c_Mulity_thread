#include <stdio.h>
#include <mpi.h>
 
#define BUFMAX 81
 
int main(int argc, char *argv[])
{
    char outbuf[BUFMAX], inbuf[BUFMAX];
    int rank, size;
    int sendto, recvfrom;
    MPI_Status status;
 
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    //sprintf(outbuf, "Hello, world! from process %d of %d", rank, size);
 
    sendto = (rank + 1) % size;
    recvfrom = ((rank + size) - 1) % size;
 
    if (!(rank % 2))
    {
        MPI_Send(outbuf, BUFMAX, MPI_CHAR, sendto, 0, MPI_COMM_WORLD);
        MPI_Recv(inbuf, BUFMAX, MPI_CHAR, recvfrom, 0, MPI_COMM_WORLD, &status);
    }
    else
    {
        MPI_Recv(inbuf, BUFMAX, MPI_CHAR, recvfrom, 0, MPI_COMM_WORLD, &status);
        MPI_Send(outbuf, BUFMAX, MPI_CHAR, sendto, 0, MPI_COMM_WORLD);
    }
 
    printf("当前进程为%d,从第%d个进程接收,发送给第%d个进程\n",rank,recvfrom,sendto);
    MPI_Finalize();
 
    return(0);
}
