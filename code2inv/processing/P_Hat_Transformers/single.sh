#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)
files=$1
export files=$1

# variables=$(grep -Po "int \K[a-zA-Z0-9_]*;" c/$files.c)
# vars=`echo $variables`

# python3 extern_functions.py "${vars}" $files c > linklibs/link_$files.c; 
# python3 main_template.py "${vars}" $files c > template/$files.c;
# python3 forcov.py "${vars}" $files c > coverage/$files.c;

mkdir -p output
mkdir -p coverage
mkdir -p tests

dd if=/dev/random of=tests/input01.txt bs=32 count=1
dd if=/dev/random of=tests/input02.txt bs=32 count=1
dd if=/dev/random of=tests/input03.txt bs=32 count=1
head -c 32 /dev/zero > tests/input04.txt
dd if=/dev/random of=tests/input05.txt bs=32 count=1
head -c 32 /dev/zero > tests/input06.txt

# g++ -I./include -c -ftest-coverage -fprofile-arcs -Wall -O0 linklibs/link_$files.c -o bin/link_$files.o
# g++ -I./include -c -ftest-coverage -fprofile-arcs -Wall -O0 coverage/$files.c -o bin/coverage_$files.o

hfuzz-gcc -I./include -Wall -O0 template/$files.c -o bin/code_$files
# g++ -I../include -Wall -O0 bin/link_$files.o bin/coverage_$files.o -o bin/main_$files -lgcov

timeout 30s honggfuzz -i tests -o output -n 1 --exit_upon_crash --mutations_per_run 200 -P -- bin/code_$files ___FILE___