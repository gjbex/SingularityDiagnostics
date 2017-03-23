# Tests
A number of applications useful for testing Singularity image interaction
with its host operating system and the network.

## What is it?
1. `mpifitness`: MPI application that executes peer-to-peer and collective
    communication, and gives performance results.
1. `process_placement`: a very simple MPI applications that prints the
    rank for each process, and the hostname that process is running on.

The applications are installed in the image as specified by the image
definition file.

## Example usage
```bash
$ mpirun  --mca orte_tmpdir_base /tmp singularity exec diagnostics.img \
    mpifitness /usr/share/tests/mpifitness/smallmsgs.conf
```
Note that the number of processes to run, but also process placement can
be control from the host environment.

```bash
$ mpirun  --mca orte_tmpdir_base /tmp singularity execdiagnostics.img \
    process_placement
```

## Requirements
The host software stack should have the same MPI library available as is
used in the image, and the versions should match as well.
