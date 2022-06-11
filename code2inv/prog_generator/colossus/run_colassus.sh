#!/bin/bash

EXAMPLE=loop_$1

docker start colossus

figlet "Run Example" | lolcat
docker exec -t colossus env TERM=xterm script -q -c "cd /data/Documents/Research/code2inv/code2inv/prog_generator/colossus ; ./colossus.sh $EXAMPLE "

>models.txt

for test in $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/base_colossus/*.ktest;
do
    echo " ---------------- "
    echo "   $test" | lolcat -a
    echo " ---------------- "
    ktest-tool $test
    
    g++ -std=c++17 -march=native \
    -I $HOME/klee/include/ \
    -I $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/include/ \
    -L $HOME/klee/lib/ -g -O0 \
    $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/src/${EXAMPLE}.c -lkleeRuntest
    
    KTEST_FILE=$test ./a.out >> models.txt
done

rm -rf klee-* 
rm -rf *.bc *.dot *.out *.a

docker stop colossus