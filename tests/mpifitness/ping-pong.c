#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "util.h"
#include "ping-pong.h"

#define PING 13
#define PONG 17

int computeDestination(int source, int size);

int pingPong(MPI_Comm comm, Params conf) {
    MPI_Status mpiStatus;
    int size, rank, n, status;
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
        warnx("it takes at least two to ping-pong, size is %d\n", size);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    MPI_Comm_rank(comm, &rank);
    if (rank == 0 && conf.verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting PingPong\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Barrier(comm);
    for (n = 0; n < conf.pp_nrMsgs; n++) {
        int source, dest;
        if (rank == 0) {
            source = rand() % size;
            dest = computeDestination(source, size);
            if (conf.verbose > 1)
                fprintf(stderr, "sending msg %d from %d to %d\n",
                        n, source, dest);
        }
        MPI_Bcast(&source, 1, MPI_INT, 0, comm);
        MPI_Bcast(&dest, 1, MPI_INT, 0, comm);
        if (rank == source) {
            createRandomMsg(sBuff, conf.pp_msgSize);
            report(conf, n, SEND, source, dest, START);
            gettimeofday(&startTime, NULL);
            if ((status = MPI_Send(sBuff, conf.pp_msgSize, MPI_CHAR,
                                   dest, PING, comm)) != 0) {
                warnx("MPI_Send from %d to %d returned status %d",
                      source, dest, status);
                MPI_Abort(comm, EXIT_FAILURE);
            }
            report(conf, n, SEND, source, dest, END);
            report(conf, n, RECV, dest, source, START);
            if ((status = MPI_Recv(rBuff, conf.pp_msgSize, MPI_CHAR,
                                   dest, PONG, comm, &mpiStatus)) != 0) {
                warnx("MPI_Recv from %d by %d returned status %d",
                      source, dest, status);
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
        if (rank == dest) {
            report(conf, n, RECV, source, dest, START);
            if ((status = MPI_Recv(rBuff, conf.pp_msgSize, MPI_CHAR,
                                   source, PING, comm, &mpiStatus)) != 0) {
                warnx("MPI_Recv from %d by %d returned status %d",
                      source, dest, status);
                MPI_Abort(comm, EXIT_FAILURE);
            }
            report(conf, n, RECV, source, dest, END);
            report(conf, n, SEND, dest, source, START);
            if ((status = MPI_Send(rBuff, conf.pp_msgSize, MPI_CHAR,
                                   source, PONG, comm)) != 0) {
                warnx("MPI_Send from %d to %d returned status %d",
                      dest, source, status);
                MPI_Abort(comm, EXIT_FAILURE);
            }
            report(conf, n, SEND, dest, source, END);
        }
        MPI_Barrier(comm);
        if (conf.verbose > 1 && rank == 0)
            fprintf(stderr, "sent msg %d\n", n);
    }
    free(sBuff);
    free(rBuff);
    MPI_Barrier(comm);
    return EXIT_SUCCESS;
}

int computeDestination(int source, int size) {
    int dest;
    do {
        dest = rand() % size;
    } while (dest == source);
    return dest;
}

