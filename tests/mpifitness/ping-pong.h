#ifndef PING_PONG_HDR
#define PING_PONG_HDR

#include <mpi.h>

#include "cl_params.h"

int pingPong(MPI_Comm comm, Params conf);

#endif

