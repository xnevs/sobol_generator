#!/usr/bin/bash
mpirun -np $1 a.out | sort #| cut -d' ' -f3,4
