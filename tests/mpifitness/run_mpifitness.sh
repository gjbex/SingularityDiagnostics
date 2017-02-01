#!/bin/bash

if [ "$MPIFITNESS_CONF" != "x$MPIFITNESS_CONF" ]
then
    MPIFITNESS_CONF="/usr/share/tests/mpifitness/small-msgs.conf"
fi

mpirun "$@" /usr/bin/mpifitness.exe $MPIFITNESS_CONF
