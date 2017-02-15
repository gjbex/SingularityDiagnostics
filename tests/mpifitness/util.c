#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void report(Params conf, int msgId, int type, int from, int to,
            int status) {
    if (conf.verbose > 1) {
        fprintf(stdout, "%d: ", msgId);
        if (type == SEND)
            fprintf(stdout, "%d -> %d", from , to);
        else if (type == RECV)
            fprintf(stdout, "%d <- %d", to, from);
        else if (type == REDUCE)
            fprintf(stdout, "reduce %d -> %d", from, to);
        else if (type == ALL_TO_ALL)
            fprintf(stdout, "allToAll %d", from);
        else
            warnx("unknown type");
        if (status == START)
            fprintf(stdout, " start");
        else if (status == END)
            fprintf(stdout, " end");
        else
            warnx("unknown status");
        fprintf(stdout, "\n");
    }
}

void createRandomMsg(char *buff, int size) {
    int i;
    for (i = 0; i < size; i++)
        buff[i] = 'A' + (rand() % 26);
}

void checkMsg(MPI_Comm comm, char *buff1, char *buff2, int size,
              int source, int dest) {
    if (strncmp(buff1, buff2, size)) {
        warnx("message between %d and %d failed",
                source, dest);
        MPI_Abort(comm, EXIT_FAILURE); 
    }
}

