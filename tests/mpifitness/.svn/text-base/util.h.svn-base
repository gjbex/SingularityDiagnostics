#ifndef UTIL_HDR
#define UTIL_HDR

#include <mpi.h>
#include "cl_params.h"

#define SEND 0
#define RECV 1
#define REDUCE 2
#define ALL_TO_ALL 3
#define FILE_OPEN 4
#define FILE_WRITE 5
#define FILE_CLOSE 6
#define FILE_SEEK 7

#define START 201
#define END 202

void report(Params conf, int msgId, int type, int from, int to, int status);
void createRandomMsg(char *buff, int size);
void checkMsg(MPI_Comm comm, char *buff1, char *buff2, int size,
              int source, int dest);

#endif

