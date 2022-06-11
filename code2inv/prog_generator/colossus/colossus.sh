#!/bin/bash

rm -rf base_colossus

# echo " ==== Check -lstring_stub ==== "
# rm -rf code
# gcc -Wall -g -o code -L /data/klee-colassus/shared_lib src/code.c -lstring_stub

export EXAMPLE=$1
export LLVM_SRC=/data/llvm-3.4.2.src
export LLVM_BUILD=${LLVM_SRC}/build
export LLVM_BIN=${LLVM_BUILD}/Release+Debug+Asserts/bin
export LLVM_LIB=${LLVM_BUILD}/Release+Debug+Asserts/lib
export Z3_BUILD=/data/z3-old/z3-z3-4.4.1/build/
export KLEE_UCLIBC=/data/colossus-uclibc/
export COLOSSUS=/data/klee-colassus
export COLOSSUS_BIN=${COLOSSUS}/build/Release+Debug+Asserts/bin
export COLOSSUS_LIB=${COLOSSUS}/build/Release+Debug+Asserts/lib
export AFL_DIR=${COLOSSUS}/afl
export EXAMPLES=${COLOSSUS}/examples
export PATH=$PATH:$LLVM_BIN:$COLOSSUS_BIN:$AFL_DIR:$COLOSSUS/lexer:$COLOSSUS/funcolic-scripts
export LD_LIBRARY_PATH=$LLVM_LIB:$COLOSSUS_LIB:$COLOSSUS/shared_lib

# ./code | figlet -ckln
# rm -rf code

echo " ==== Export Done, Running Colossus ==== "
make all
make clean 

chmod 777 *
chmod 777 */*