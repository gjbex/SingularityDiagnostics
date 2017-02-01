#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "util.h"
#include "warmup.h"

#define PING 19
#define PONG 23

int warmup(MPI_Comm comm, Params conf) {
    MPI_Status mpiStatus;
    int size, rank, n = 0, source;
    struct timeval startTime, endTime;
    char *sBuff, *rBuff;
    if ((sBuff = (char *) calloc(conf.pp_msgSize, sizeof(char))) == NULL) {
        warnx("can't allocate sBuff of size %d", conf.pp_msgSize);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    if ((rBuff = (char *) calloc(conf.pp_msgSize, sizeof(char))) == NULL) {
        warnx("can't allocate rBuff of size %d", conf.pp_msgSize);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    MPI_Comm_size(comm, &size);
    if (size == 1) {
        warnx("it takes at least two to warmup, size is %d\n", size);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    MPI_Comm_rank(comm, &rank);
    if (rank == 0 && conf.verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting P2pWarmup\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Barrier(comm);
    for (source = 0; source < size; source++) {
        if (rank == source) {
            int dest;
            createRandomMsg(sBuff, conf.pp_msgSize);
            for (dest = 0; dest < size; dest++) {
                if (source == dest)
                    continue;
                n++;
                report(conf, n, SEND, source, dest, START);
                gettimeofday(&startTime, NULL);
                if (MPI_Send(sBuff, conf.pp_msgSize, MPI_CHAR,
                             dest, PING, comm) != 0) {
                    MPI_Abort(comm, EXIT_FAILURE);
                }
                report(conf, n, SEND, source, dest, END);
                report(conf, n, RECV, dest, source, START);
                if (MPI_Recv(rBuff, conf.pp_msgSize, MPI_CHAR,
                             dest, PONG, comm, &mpiStatus) != 0) {
                    MPI_Abort(comm, EXIT_FAILURE);
                }
                report(conf, n, RECV, dest, source, END);
                gettimeofday(&endTime, NULL);
                if (conf.verbose)
                    fprintf(stderr, "%d\t%d\t%d\t%ld\t%ld.%ld\n",
                            n, source, dest,
                            1000000*(endTime.tv_sec - startTime.tv_sec) +
                            endTime.tv_usec - startTime.tv_usec,
                            endTime.tv_sec, endTime.tv_usec);
                checkMsg(comm, sBuff, rBuff, conf.pp_msgSize, source, dest);
            }
        } else {
            report(conf, n, RECV, source, rank, START);
            if (MPI_Recv(rBuff, conf.pp_msgSize, MPI_CHAR,
                         source, PING, comm, &mpiStatus) != 0) {
                MPI_Abort(comm, EXIT_FAILURE);
            }
            report(conf, n, RECV, source, rank, END);
            report(conf, n, SEND, rank, source, START);
            if (MPI_Send(rBuff, conf.pp_msgSize, MPI_CHAR,
                         source, PONG, comm) != 0) {
                MPI_Abort(comm, EXIT_FAILURE);
            }
            report(conf, n, SEND, rank, source, END);
        }
        MPI_Barrier(comm);
    }
    free(sBuff);
    free(rBuff);
    MPI_Barrier(comm);
    return EXIT_SUCCESS;
}

