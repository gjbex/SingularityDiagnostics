#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "cl_params.h"
#include "cl_params_aux.h"

#define MAX_CL_OPT_LEN 128
#define MAX_CL_LINE_LEN 1024

void initCL(Params *params) {
	params->verbose = 1;
	params->doPresent = 1;
	params->doP2pWarmup = 1;
	params->doPingPong = 1;
	params->pp_msgSize = 65536;
	params->pp_nrMsgs = 1000;
	params->doReduce = 1;
	params->reduce_size = 100000;
	params->reduce_nr = 10;
	params->doAllToAll = 1;
	params->allToAll_size = 1000;
	params->allToAll_nr = 10;
	params->doMpiFileWrite = 0;
	int len;
	len = strlen("/scratch/leuven/301/vsc30140/iow");
	if (!(params->iow_fileName = (char *) calloc(len + 1, sizeof(char))))
		errx(EXIT_CL_ALLOC_FAIL, "can not allocate iow_fileName field");
	strncpy(params->iow_fileName, "/scratch/leuven/301/vsc30140/iow", len + 1);
	params->iow_nrWords = 1600000000;
	params->iow_nrWordsBuffer = 1000000;
}

void parseCL(Params *params, int *argc, char **argv[]) {
	char *argv_str;
	int i = 1;
	while (i < *argc) {
		if (!strncmp((*argv)[i], "-verbose", 9)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doPresent", 11)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doPresent' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doPresent = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doP2pWarmup", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doP2pWarmup' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doP2pWarmup = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doPingPong", 12)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doPingPong' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doPingPong = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-pp_msgSize", 12)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-pp_msgSize' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->pp_msgSize = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-pp_nrMsgs", 11)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-pp_nrMsgs' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->pp_nrMsgs = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doReduce", 10)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doReduce' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doReduce = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-reduce_size", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-reduce_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->reduce_size = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-reduce_nr", 11)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-reduce_nr' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->reduce_nr = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doAllToAll", 12)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doAllToAll' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doAllToAll = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-allToAll_size", 15)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-allToAll_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->allToAll_size = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-allToAll_nr", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-allToAll_nr' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->allToAll_nr = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-doMpiFileWrite", 16)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doMpiFileWrite' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doMpiFileWrite = atoi(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-iow_fileName", 14)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-iow_fileName' of type char *\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			char *tmp;
			int len = strlen(argv_str);
			free(params->iow_fileName);
			if (!(tmp = (char *) calloc(len + 1, sizeof(char))))
				errx(EXIT_CL_ALLOC_FAIL, "can not allocate char* field");
			params->iow_fileName = strncpy(tmp, argv_str, len + 1);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-iow_nrWords", 13)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-iow_nrWords' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->iow_nrWords = atol(argv_str);
			i++;
			continue;
		}
		if (!strncmp((*argv)[i], "-iow_nrWordsBuffer", 19)) {
			shiftCL(&i, *argc, *argv);
			argv_str = (*argv)[i];
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-iow_nrWordsBuffer' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->iow_nrWordsBuffer = atol(argv_str);
			i++;
			continue;
		}
		break;
	}
	if (i > 1) {
		(*argv)[i - 1] = (*argv)[0];
		*argv = &((*argv)[i - 1]);
		*argc -= (i - 1);
	}
}

void parseFileCL(Params *params, char *fileName) {
	char line_str[MAX_CL_LINE_LEN];
	char argv_str[MAX_CL_LINE_LEN];
	FILE *fp;
	if (!(fp = fopen(fileName, "r"))) {
		fprintf(stderr, "### error: can not open file '%s'\n", fileName);
		exit(EXIT_CL_FILE_OPEN_FAIL);
	}
	while (fgets(line_str, MAX_CL_LINE_LEN, fp)) {
		if (isCommentCL(line_str)) continue;
		if (isEmptyLineCL(line_str)) continue;
		if (sscanf(line_str, "verbose = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-verbose' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->verbose = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doPresent = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doPresent' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doPresent = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doP2pWarmup = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doP2pWarmup' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doP2pWarmup = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doPingPong = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doPingPong' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doPingPong = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "pp_msgSize = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-pp_msgSize' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->pp_msgSize = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "pp_nrMsgs = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-pp_nrMsgs' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->pp_nrMsgs = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doReduce = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doReduce' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doReduce = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "reduce_size = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-reduce_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->reduce_size = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "reduce_nr = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-reduce_nr' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->reduce_nr = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doAllToAll = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doAllToAll' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doAllToAll = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "allToAll_size = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-allToAll_size' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->allToAll_size = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "allToAll_nr = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-allToAll_nr' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->allToAll_nr = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "doMpiFileWrite = %[^\n]", argv_str) == 1) {
			if (!isIntCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-doMpiFileWrite' of type int\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->doMpiFileWrite = atoi(argv_str);
			continue;
		}
		if (sscanf(line_str, "iow_fileName = %[^\n]", argv_str) == 1) {
			if (!1) {
				fprintf(stderr, "### error: invalid value for option '-iow_fileName' of type char *\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			char *tmp;
			int len = strlen(argv_str);
			free(params->iow_fileName);
			if (!(tmp = (char *) calloc(len + 1, sizeof(char))))
				errx(EXIT_CL_ALLOC_FAIL, "can not allocate char* field");
			params->iow_fileName = strncpy(tmp, argv_str, len + 1);
			stripQuotesCL(params->iow_fileName);
			continue;
		}
		if (sscanf(line_str, "iow_nrWords = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-iow_nrWords' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->iow_nrWords = atol(argv_str);
			continue;
		}
		if (sscanf(line_str, "iow_nrWordsBuffer = %[^\n]", argv_str) == 1) {
			if (!isLongCL(argv_str, 0)) {
				fprintf(stderr, "### error: invalid value for option '-iow_nrWordsBuffer' of type long\n");
				exit(EXIT_CL_INVALID_VALUE);
			}
			params->iow_nrWordsBuffer = atol(argv_str);
			continue;
		}
		fprintf(stderr, "### warning, line can not be parsed: '%s'\n", line_str);
	}
	fclose(fp);
}

void dumpCL(FILE *fp, char prefix[], Params *params) {
	fprintf(fp, "%sverbose = %d\n", prefix, params->verbose);
	fprintf(fp, "%sdoPresent = %d\n", prefix, params->doPresent);
	fprintf(fp, "%sdoP2pWarmup = %d\n", prefix, params->doP2pWarmup);
	fprintf(fp, "%sdoPingPong = %d\n", prefix, params->doPingPong);
	fprintf(fp, "%spp_msgSize = %d\n", prefix, params->pp_msgSize);
	fprintf(fp, "%spp_nrMsgs = %d\n", prefix, params->pp_nrMsgs);
	fprintf(fp, "%sdoReduce = %d\n", prefix, params->doReduce);
	fprintf(fp, "%sreduce_size = %d\n", prefix, params->reduce_size);
	fprintf(fp, "%sreduce_nr = %d\n", prefix, params->reduce_nr);
	fprintf(fp, "%sdoAllToAll = %d\n", prefix, params->doAllToAll);
	fprintf(fp, "%sallToAll_size = %d\n", prefix, params->allToAll_size);
	fprintf(fp, "%sallToAll_nr = %d\n", prefix, params->allToAll_nr);
	fprintf(fp, "%sdoMpiFileWrite = %d\n", prefix, params->doMpiFileWrite);
	fprintf(fp, "%siow_fileName = '%s'\n", prefix, params->iow_fileName);
	fprintf(fp, "%siow_nrWords = %ld\n", prefix, params->iow_nrWords);
	fprintf(fp, "%siow_nrWordsBuffer = %ld\n", prefix, params->iow_nrWordsBuffer);
}

void finalizeCL(Params *params) {
	free(params->iow_fileName);
}