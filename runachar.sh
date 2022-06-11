#!/bin/bash

cd code2inv/prog_generator
mkdir -p results candidates cache models 
./reset.sh

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

export TIMEOUT=10
export EPOCH=8

while getopts ":h" option; do
    case $option in
        h) # display Help
            Help
        exit;;
        \?) # incorrect option
            echo "Error: Invalid option"
        exit;;
    esac
done

if [ -z $1 ];
then
    echo "Specify Benchmark Example to process"
    echo "Usage ./runbench.sh <file_index_to_process> <spec_type>"
    exit -1
else
    export INVPROCESSFILE=$1
    export EXAMPLE=$1
    var=$1
fi

if [ -z $2 ];
then
    echo "Specify SPEC type (see specs folder)"
    echo "Usage ./runbench.sh <file_index_to_process> <spec_type>"
    exit -1
else
    export SPEC=$2
fi

if [ -z $3 ];
then
    echo Using default K-Induction "K = 64"
    export K=64
else
    export K=$3
fi

figlet Achar | lolcat

export NPROG_PATH=$4
export NPROG_JSON_PATH=$5
export NPROG_SMT_PATH=$6
export SPECS_PATH=$7

PREV_K=`(cat $NPROG_PATH | grep -Po "UNROLL_LIMIT \K[0-9]*")`
sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" $NPROG_PATH
echo "K-Induction : ${PREV_K}, `(cat $NPROG_PATH | grep -Po "UNROLL_LIMIT \K[0-9]*")`"

time ./run_solver_file.sh ../../$NPROG_JSON_PATH ../../$NPROG_SMT_PATH $SPECS_PATH -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC

sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" $NPROG_PATH
echo "K-Induction : ${PREV_K}, `(cat $NPROG_PATH | grep -Po "UNROLL_LIMIT \K[0-9]*")`"