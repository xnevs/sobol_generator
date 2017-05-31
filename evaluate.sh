#/bin/bash

N=100000
n1=$((3*5*7*8*N))
n2=$((4*3*5*7*N))
n3=$((5*7*8*N))
n4=$((2*3*5*7*N))
n5=$((3*7*8*N))
n6=$((4*5*7*N))
n7=$((5*3*8*N))
n8=$((5*3*7*N))

echo "n: $n1"

echo -n "1 "
/usr/bin/time -f'%e' mpirun -np 1 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n1 1>/dev/null

echo -n "2 "
/usr/bin/time -f'%e' mpirun -np 2 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n2 1>/dev/null

echo -n "3 "
/usr/bin/time -f'%e' mpirun -np 3 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n3 1>/dev/null

echo -n "4 "
/usr/bin/time -f'%e' mpirun -np 4 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n4 1>/dev/null

echo -n "5 "
/usr/bin/time -f'%e' mpirun -np 5 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n5 1>/dev/null

echo -n "6 "
/usr/bin/time -f'%e' mpirun -np 6 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n6 1>/dev/null

echo -n "7 "
/usr/bin/time -f'%e' mpirun -np 7 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n7 1>/dev/null

echo -n "8 "
/usr/bin/time -f'%e' mpirun -np 8 ./evaluate1 direction_numbers/new-joe-kuo-6.21201.txt $n8 1>/dev/null
