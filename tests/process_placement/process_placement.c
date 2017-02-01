#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size, name_length;
    char hostname[1024];
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(hostname, &name_length);
    printf("rank %d out of %d on '%s'\n", rank, size, hostname);
    MPI_Finalize();
    return EXIT_SUCCESS;
}
