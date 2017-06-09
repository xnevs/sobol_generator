#!/bin/bash

#N=50000
for ((N=5000; N<=50000; N+=5000 ))
do
    n1=$((3*5*7*8*N))
    n2=$((4*3*5*7*N))
    n3=$((5*7*8*N))
    n4=$((2*3*5*7*N))
    n5=$((3*7*8*N))
    n6=$((4*5*7*N))
    n7=$((5*3*8*N))
    n8=$((5*3*7*N))

    echo -n "$n1"
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 1 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n1 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 2 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n2 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 3 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n3 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 4 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n4 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 5 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n5 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 6 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n6 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 7 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n7 2>&1 1>/dev/null | tr -d '\n'
    echo -n " "
    /usr/bin/time -f'%e' mpirun -np 8 ./evaluate direction_numbers/new-joe-kuo-6.21201.txt $n8 2>&1 1>/dev/null | tr -d '\n'
    echo
done
