#ifndef ALL_TO_ALL_HDR
#define ALL_TO_ALL_HDR

#include <mpi.h>

#include "cl_params.h"

int allToAll(MPI_Comm comm, Params conf);

#endif

