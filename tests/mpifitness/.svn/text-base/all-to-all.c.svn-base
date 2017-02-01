#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "util.h"
#include "all-to-all.h"

int allToAll(MPI_Comm comm, Params conf) {
    int size, rank, i, j, n, status, nr = conf.allToAll_size;
    int *sBuff, *rBuff;
    struct timeval startTime, endTime, currTime;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    if ((sBuff = (int *) calloc(nr*size, sizeof(int))) == NULL) {
        warnx("can't allocate sBuff of size %d", conf.allToAll_size);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    if ((rBuff = (int *) calloc(nr*size, sizeof(int))) == NULL) {
        warnx("can't allocate rBuff of size %d", conf.reduce_size);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    for (i = 0; i < size; i++)
        for (j = 0; j < nr; j++) {
            sBuff[i*nr + j] = rank + 10*j;
            rBuff[i*nr + j] = -1;
        }
    if (rank == 0 && conf.verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting AllToAll\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Barrier(comm);
    for (n = 0; n < conf.allToAll_nr; n++) {
        if (rank == 0 && conf.verbose > 1)
            fprintf(stderr, "allToAll(%d) %d\n", n, rank);
        report(conf, n, ALL_TO_ALL, rank, -1, START);
        if (rank == 0)
            gettimeofday(&startTime, NULL);
        if (status = MPI_Alltoall(sBuff, nr, MPI_INT,
                                  rBuff, nr, MPI_INT,
                                  comm)) {
            warnx("MPI_Alltoall from %d returned status %d", rank, status);
            MPI_Abort(comm, EXIT_FAILURE);
        }
        if (rank == 0)
            gettimeofday(&endTime, NULL);
        report(conf, n, ALL_TO_ALL, rank, -1, END);
        if (rank == 0) {
            if (conf.verbose)
                fprintf(stderr, "%d\t%ld\t%ld.%ld\n",
                        n, 1000000*(endTime.tv_sec - startTime.tv_sec) +
                        endTime.tv_usec - startTime.tv_usec,
                        endTime.tv_sec, endTime.tv_usec);
            if (conf.verbose > 1)
                fprintf(stderr, "allToAll %d done\n", n);
        }
        MPI_Barrier(comm);
    }
    free(sBuff);
    free(rBuff);
    return EXIT_SUCCESS;
}

