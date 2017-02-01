INSTR     = 
CC        = mpicc
CFLAGS    = -O2 -g
MPI_INC   =
CPPFLAGS += $(MPI_INC)
LDFLAGS   =
MPI_LIB   =
PROF      =
LIBS     += $(MPI_LIB) $(PROF)
EXEC_NAME = mpifitness

TESTS = present warmup ping-pong reduce all-to-all mpi-io-write

TEST_OBJS = $(patsubst %, %.o, $(TESTS))
OBJS      = main.o util.o cl_params.o cl_params_aux.o $(TEST_OBJS)

all: mpifitness.exe

mpifitness.exe: $(OBJS)
	$(INSTR) $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.c
	$(INSTR) $(CC) $(CFLAGS) $(CPPFLAGS) -c $<

clean:
	rm -f *.o mpifitness

install: all
	cp mpifitness.exe ./usr/bin/
