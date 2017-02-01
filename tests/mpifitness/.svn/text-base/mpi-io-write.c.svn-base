#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "mpi-io-write.h"

#define FILE_NAME_LENGTH 1024

void generateWord(char *buffer, int nrChars);

int mpiIoWrite(MPI_Comm comm, Params conf) {
    int rank, size, rv;
    long nrWords = 80, word, localNrWords, offset,
         nrWordsBuffer = 4000000,
         bufferSize, wordInBuffer, totalWrites = 0;
    int nrChars = 4, charsPerLine = 80, wordsPerLine;
    char *buffer;
    MPI_File fp;
    char fileName[FILE_NAME_LENGTH];
    MPI_Status status;
    struct timeval startTime, endTime, currTime;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    srand(104845 + 1023*rank);
    nrWords = conf.iow_nrWords;
    strncpy(fileName, conf.iow_fileName, FILE_NAME_LENGTH - 1);
    nrWordsBuffer = conf.iow_nrWordsBuffer;
    localNrWords = nrWords/size;
    if (rank == size - 1)
        localNrWords += (nrWords % size) - 1;
    if (conf.verbose > 1)
        fprintf(stderr, "rank %d writing %ld words\n",
               rank, localNrWords);
    offset = rank*localNrWords*(nrChars + 1)*sizeof(char);
    wordsPerLine = charsPerLine/(nrChars + 1);
    bufferSize = (nrChars + 1)*nrWordsBuffer + 1;
    if ((buffer = (char *) calloc(bufferSize, sizeof(char))) == NULL) {
        warnx("Can't calloc buffer of size %ld for rank %d", bufferSize, rank);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    if (rank == 0 && conf.verbose) {
        fprintf(stderr, "\n");
        fprintf(stderr, "# -------------------------------\n");
        fprintf(stderr, "# starting MPI_File_write\n");
        fprintf(stderr, "# -------------------------------\n");
    }
    MPI_Barrier(comm);
    report(conf, 0, FILE_OPEN, rank, -1, START);
    gettimeofday(&startTime, NULL);
    MPI_File_open(comm, fileName, MPI_MODE_CREATE | MPI_MODE_WRONLY,
                  MPI_INFO_NULL, &fp);
    gettimeofday(&endTime, NULL);
    if (conf.verbose)
        fprintf(stderr, "open %d\t%ld\t%ld.%ld\n",
                rank, 1000000*(endTime.tv_sec - startTime.tv_sec) +
                endTime.tv_usec - startTime.tv_usec,
                endTime.tv_sec, endTime.tv_usec);
    if (fp == NULL) {
        warn("Can't open '%s' for rank %d", fileName, rank);
        MPI_Abort(comm, EXIT_FAILURE);
    }
    report(conf, 0, FILE_OPEN, rank, -1, END);
    if (conf.verbose > 1)
        fprintf(stderr, "rank %d starting at %ld\n",
                rank, offset);
    report(conf, 0, FILE_SEEK, rank, -1, START);
    MPI_File_seek(fp, offset, MPI_SEEK_SET);
    report(conf, 0, FILE_SEEK, rank, -1, END);
    wordInBuffer = 0;
    for (word = 0; word < localNrWords; word++) {
        long offset = wordInBuffer*(nrChars + 1);
        generateWord(buffer + offset, nrChars);
        if ((word + 1) % wordsPerLine == 0)
            buffer[offset + nrChars] = '\n';
        else
            buffer[offset + nrChars] = ' ';
        buffer[offset + nrChars + 1] = '\0';
        wordInBuffer++;
        if (wordInBuffer % nrWordsBuffer == 0) {
            report(conf, totalWrites, FILE_WRITE, rank, -1, START);
            gettimeofday(&startTime, NULL);
            if (rv = MPI_File_write(fp, buffer, strlen(buffer), MPI_CHAR,
                                    &status)) {
                warnx("MPI_File_write status = %d for rank %d", rv, rank);
                MPI_Abort(comm, EXIT_FAILURE);
            }
            gettimeofday(&endTime, NULL);
            if (conf.verbose)
                fprintf(stderr, "write %d\t%ld\t%ld\t%ld.%ld\n",
                        rank, totalWrites,
                        1000000*(endTime.tv_sec - startTime.tv_sec) +
                        endTime.tv_usec - startTime.tv_usec,
                        endTime.tv_sec, endTime.tv_usec);
            report(conf, totalWrites, FILE_WRITE, rank, -1, END);
            if (conf.verbose > 1)
                fprintf(stderr, "rank %d wrote %ld words\n",
                        rank, wordInBuffer);
            wordInBuffer = 0;
            totalWrites++;
        }
    }
    if (rank == size - 1 && localNrWords >= 1) {
        long offset = wordInBuffer*(nrChars + 1);
        generateWord(buffer + offset, nrChars);
        buffer[offset + nrChars] = '\n';
        buffer[offset + nrChars + 1] = '\0';
        wordInBuffer++;
    }
    if (wordInBuffer > 0) {
        report(conf, totalWrites, FILE_WRITE, rank, -1, START);
        gettimeofday(&startTime, NULL);
        if (rv = MPI_File_write(fp, buffer, strlen(buffer), MPI_CHAR,
                                &status)) {
            warnx("MPI_File_write status = %d for rank %d", rv, rank);
            MPI_Abort(comm, EXIT_FAILURE);
        }
        gettimeofday(&endTime, NULL);
        if (conf.verbose)
            fprintf(stderr, "write %d\t%ld\t%ld\t%ld.%ld\n",
                    rank, totalWrites,
                    1000000*(endTime.tv_sec - startTime.tv_sec) +
                    endTime.tv_usec - startTime.tv_usec,
                    endTime.tv_sec, endTime.tv_usec);
        report(conf, totalWrites, FILE_WRITE, rank, -1, END);
        totalWrites++;
    }
    if (conf.verbose > 1)
        fprintf(stderr, "rank %d performed %ld writes\n",
                rank, totalWrites);
    report(conf, 0, FILE_CLOSE, rank, -1, START);
    gettimeofday(&startTime, NULL);
    MPI_File_close(&fp);
    gettimeofday(&endTime, NULL);
    if (conf.verbose)
        fprintf(stderr, "close %d\t%ld\t%ld.%ld\n",
                rank, 1000000*(endTime.tv_sec - startTime.tv_sec) +
                endTime.tv_usec - startTime.tv_usec,
                endTime.tv_sec, endTime.tv_usec);
    report(conf, 0, FILE_CLOSE, rank, -1, END);
    free(buffer);
    return EXIT_SUCCESS;
}

void generateWord(char *buffer, int nrChars) {
    int i;
    for (i = 0; i < nrChars; i++)
        buffer[i] = 'a' + rand() % 26;
}


