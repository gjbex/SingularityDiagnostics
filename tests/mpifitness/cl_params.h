#ifndef CL_PARAMS_HDR
#define CL_PARAMS_HDR

#include <stdio.h>

typedef struct {
	int verbose;
	int doPresent;
	int doP2pWarmup;
	int doPingPong;
	int pp_msgSize;
	int pp_nrMsgs;
	int doReduce;
	int reduce_size;
	int reduce_nr;
	int doAllToAll;
	int allToAll_size;
	int allToAll_nr;
	int doMpiFileWrite;
	char * iow_fileName;
	long iow_nrWords;
	long iow_nrWordsBuffer;
} Params;

void initCL(Params *params);
void parseCL(Params *params, int *argc, char **argv[]);
void parseFileCL(Params *params, char *fileName);
void dumpCL(FILE *fp, char prefix[], Params *params);
void finalizeCL(Params *params);

#endif