# SingularityDiagnostics
Singularity image for diagnostic purposes, and supporting software.

## What is it?
1. `xenial_diagnostics.def`: Singularity image definition file.
1. `hello.c`: MPI application to print the hostname on which the MPI
    processes are running.
1. `Makefile`: make file to build the application.
1. `run_hello.sh`: Bash script to run the MPI hello.exe application, takes
    passes arguments to mpirun.
