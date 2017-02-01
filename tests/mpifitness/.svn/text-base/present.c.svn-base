#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "present.h"

int present(MPI_Comm comm, int verbose) {
    int rank, size, nameLength;
    char name[1024];
    struct timeval currTime;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    if (rank == 0 && verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting Present\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Get_processor_name(name, &nameLength);
    MPI_Barrier(comm);
    gettimeofday(&currTime, NULL);
    if (verbose)
        fprintf(stderr, "# process %4d of %4d on %s present at %ld.%ld\n",
                rank, size, name, currTime.tv_sec, currTime.tv_usec);
    MPI_Barrier(comm);
    return EXIT_SUCCESS;
}

