#!/usr/bin/bash
#mpirun -np $1 a.out | sort | cut -d' ' -f3,4 | tail -n+2 > dout
mpirun -np $1 a.out | sort | tail -n+2 > dout
../serial/a.out $(($1 * 10 - 1)) > sout
paste dout sout | awk '{printf "%s %s %s %s %s %s",$1,$2,$3,$4,$5,$6; if($3!=$5 || $4!=$6){print " <------------"}else{print ""}}'
