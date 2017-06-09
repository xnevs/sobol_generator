#!/bin/bash

for ((N=100; N<=5000; N+=100 ))
do
    n1=$((3*5*7*8*N))
    echo -n "$n1"
    echo -n " "
    mpirun -np 1 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n1
done
