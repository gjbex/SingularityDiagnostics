#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "util.h"
#include "reduce.h"

int reduce(MPI_Comm comm, Params conf) {
    int size, rank, i, n, status;
    double *sBuff = NULL, *rBuff = NULL;
    struct timeval startTime, endTime;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    if ((sBuff = (double *) calloc(conf.reduce_size, sizeof(double))) == NULL) {
        warnx("can't allocate sBuff of size %d", conf.reduce_size);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    if (rank == 0)
        if ((rBuff = (double *) calloc(conf.reduce_size, sizeof(double))) == NULL) {
            warnx("can't allocate rBuff of size %d", conf.reduce_size);
            MPI_Abort(comm, EXIT_FAILURE);
        }
    for (i = 0; i < conf.reduce_size; i++)
        sBuff[i] = ((double) rand())/RAND_MAX;
    if (rank == 0 && conf.verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting Reduce\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Barrier(comm);
    for (n = 0; n < conf.reduce_nr; n++) {
        double term = ((double) rand())/RAND_MAX;
        for (i = 0; i < conf.reduce_size; i++)
            sBuff[i] += term;
        if (rank == 0 && conf.verbose > 1)
            fprintf(stderr, "reduction(%d) %d to %d\n", conf.reduce_size, n, 0);
        report(conf, n, REDUCE, rank, 0, START);
        if (rank == 0)
            gettimeofday(&startTime, NULL);
        if ((status = MPI_Reduce(sBuff, rBuff, conf.reduce_size, MPI_DOUBLE,
                                 MPI_SUM, 0, comm)) != 0) {
            warnx("MPI_Reduce to %d returned status %d", 0, status);
            MPI_Abort(comm, EXIT_FAILURE);
        }
        if (rank == 0)
            gettimeofday(&endTime, NULL);
        report(conf, n, REDUCE, rank, 0, END);
        if (rank == 0) {
            if (conf.verbose)
                fprintf(stderr, "%d\t%ld\t%ld.%ld\n",
                        n, 1000000*(endTime.tv_sec - startTime.tv_sec) +
                        endTime.tv_usec - startTime.tv_usec,
                        endTime.tv_sec, endTime.tv_usec);
            if (conf.verbose > 1)
                fprintf(stderr, "reduction %d done\n", n);
        }
        MPI_Barrier(comm);
    }
    free(sBuff);
    if (rank == 0)
        free(rBuff);
    return EXIT_SUCCESS;
}

