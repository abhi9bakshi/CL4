#!/bin/sh
cp /dev/null output.txt

itr=1
while [ $itr -le 5 ]
do
mpicc -o  prime_MPI  prime_MPI.c
mpirun ./prime_MPI | awk 'FNR==29 {print $3}' >> output.txt
 itr=`expr $itr + 1`
done
quickplot output.txt
