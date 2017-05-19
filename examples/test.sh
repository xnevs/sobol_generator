#!/usr/bin/bash
mpirun -np $1 ./generate | sort > dout
./serial/a.out $(($1 * 5)) > sout
paste dout sout | awk '{printf "%s %s %s %s %s %s",$1,$2,$3,$4,$5,$6; if($3!=$5 || $4!=$6){print " <------------"}else{print ""}}'
rm dout sout
