#!/usr/bin/bash

mkdir -p include bin
echo "#define PHI 1" > include/$1.h

# Instrument code.c with gcov calls.
g++ -c -I./include -ftest-coverage -fprofile-arcs -Wall -O0 coverage/$1.c -o bin/$1.o
g++ -c -I./include -ftest-coverage -fprofile-arcs -Wall -O0 linklibs/link_$1.c -o bin/link_$1.o

# Don't instrument main with gcov.
g++ -Wall -O0 bin/$1.o bin/link_$1.o -o bin/main_$1.out -lgcov 

# Run with inputs
sed 's/,/ /g' program_inputs/inputs_$1.txt > program_inputs/mod_inputs_$1.txt
timeout 5m ./runner.sh $1

# Gcov for code
gcov -b -c bin/$1 >> coverage.log
gcov -b -c bin/link_$1 >> coverage.log

mkdir -p coverageInfo
mv *.gcov coverageInfo/