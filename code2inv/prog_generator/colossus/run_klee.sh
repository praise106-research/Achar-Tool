#!/bin/bash

EXAMPLE=$1

rm -rf $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/base_klee 
rm -rf $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/loop_${EXAMPLE}.bc

echo " ==== Compiling Example ${EXAMPLE} ==="

clang-10 -I $HOME/klee/include \
    -I $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/include/ \
    -c -emit-llvm -g -O0 -fPIC \
    -fno-rtti -Xclang \
    -disable-O0-optnone $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/src/loop_${EXAMPLE}.c -o \
    $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/loop_${EXAMPLE}.bc 2> error.log

klee --libc=uclibc \
    --optimize --disable-inlining \
    --search=nurs:depth --use-cex-cache \
    --write-kqueries --output-dir=$HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/base_klee \
    $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/loop_${EXAMPLE}.bc --set-ptree-dump 2> error.log

# >models.txt

# for test in $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/base_klee/*.ktest;
# do
#     echo $test | lolcat
#     ktest-tool $test
    
#     g++ -std=c++17 \
#     -march=native -I $HOME/klee/include/ \
#     -I $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/include/ \
#     -L $HOME/klee/lib/ \
#     $HOME/Documents/Research/code2inv/code2inv/prog_generator/colossus/src/loop_${EXAMPLE}.c -lkleeRuntest
    
#     KTEST_FILE=$test ./a.out >> models.txt
#     figlet "Test Done" | lolcat
# done

rm -rf *.bc *.dot *.out
# figlet "KLEE Done" | lolcat