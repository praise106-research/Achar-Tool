#!/usr/bin/bash 

for file in {1..133};
do
    ./run_klee.sh ${file}
done