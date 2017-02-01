#include <err.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "cl_params.h"
#include "present.h"
#include "warmup.h"
#include "ping-pong.h"
#include "reduce.h"
#include "all-to-all.h"

int main(int argc, char *argv[]) {
    int rank;
    Params conf;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    initCL(&conf);
    /* check whether config file name was specified */
    if (rank == 0 && argc < 2) {
        warnx("expecting configuration file name");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    parseFileCL(&conf, argv[1]);
    if (rank == 0 && conf.verbose)
        dumpCL(stderr, "# ", &conf);
    MPI_Barrier(MPI_COMM_WORLD);
    if (conf.doPresent)
        present(MPI_COMM_WORLD, conf.verbose);
    MPI_Barrier(MPI_COMM_WORLD);
    if (conf.doP2pWarmup)
        warmup(MPI_COMM_WORLD, conf);
    MPI_Barrier(MPI_COMM_WORLD);
    if (conf.doPingPong)
        pingPong(MPI_COMM_WORLD, conf);
    MPI_Barrier(MPI_COMM_WORLD);
    if (conf.doReduce)
        reduce(MPI_COMM_WORLD, conf);
    MPI_Barrier(MPI_COMM_WORLD);
    if (conf.doAllToAll)
        allToAll(MPI_COMM_WORLD, conf);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# mpifitness finished succesfully\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}

