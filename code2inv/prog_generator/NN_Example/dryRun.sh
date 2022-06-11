#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

echo  ======== Compiling RQ3 NN ========
./start.sh -b bin -o output -t tests -e 150

echo  ======== Executing RQ3 NN ========
timeout 20 ./fuzz.sh -b bin -o output -t tests -e 150
