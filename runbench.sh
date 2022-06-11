#!/bin/bash

cd code2inv/prog_generator
mkdir -p results candidates cache models 
./reset.sh

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

if [ -z $4 ];
then
    export TIMEOUT=10
else
    export TIMEOUT=$4
fi

if [ -z $5 ];
then
    export EPOCH=8
else
    export EPOCH=$5
fi

Help()
{
    # Display Help
    figlet Achar
    echo
    echo "==== Achar : Verifying REAL Loop Invariants. ===="
    echo
    echo "Usage : ./runexample.sh (-h) [INDEX] [SPEC_TYPE] (Optional .. K-Induction Factor)"
    echo "parameters : "
    echo "  INDEX      Benchmark Example Number or Index to process."
    echo "  SPEC_TYPE  Specifiy the grammar and checker/solver pair for the run."
    echo "             Check the specs folder for more information"
    echo
    echo "                 To run a Hybrid Benchmark {1..10} Example, spec : fuzz_hybrid"
    echo "                 To run Open-Program Benchmark {1..12, 14, 15} Examples, spec : fuzz_open"
    echo "                 To run the NN MNIST Example, spec : fuzz_nn, INDEX : 150"
    echo "                 To run a Fuzz Example with HonggFuzz, spec : fuzz_spec, INDEX : [1-133]"
    echo "                 To run with Z3, spec : c_nl_all_spec, INDEX : [1-133]"
    echo "                 To run a Colassus Example, spec : colossus_spec [need Colossus Docker Running]"
    echo
    echo
    echo "Examples :  Use the Example Number as INDEX."
    echo
    echo "      Hybrid Example 1 : multiply()"
    echo "      Hybrid Example 2 : mod2check()"
    echo
    echo "      Open-Program Benchmark Example 2 : isprime() // Paper Example [isprime()]"
    echo "      Open-Program Benchmark Example 1 : sum() // Sum of squares"
    echo "      Open-Program Benchmark Example 8 : multiply() // Multiply Example"
    echo "  -h          Print this Help."
    echo
    echo "Example : "
    echo "$ ./runbench.sh 11 fuzz_spec"
    echo
}

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
mkdir -p results candidates cache models 
if [[ "$SPEC" == "fuzz_hybrid" ]];
then
    # Run a RQ5 Example (Refer as a Hybrid Benchmark Example)
    PREV_K=`(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
    sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" Hybrid_Examples/src/hybrid_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
    
    time ./run_solver_file.sh \
    ../../benchmarks/Hybrid_Examples/c_graph/hybrid_${var}.c.json \
    ../../benchmarks/Hybrid_Examples/c_smt2/hybrid_${var}.c.smt specs/hybrid_specs/hybrid_${EXAMPLE}_spec \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" Hybrid_Examples/src/hybrid_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
elif [[ "$SPEC" == "fuzz_open" ]];
then
    # Run a Opaque Example (Refer as a Opaque Benchmark Example) [1..12 14 15]
    PREV_K=`(cat Opaque_Examples/src/example_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
    sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" Opaque_Examples/src/example_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Opaque_Examples/src/example_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
    
    time ./run_solver_file.sh \
    ../../benchmarks/Opaque_Examples/c_graph/example_${var}.c.json \
    ../../benchmarks/Opaque_Examples/c_smt2/example_${var}.c.smt specs/Opaque_specs/example_${EXAMPLE}_spec \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" Opaque_Examples/src/example_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Opaque_Examples/src/example_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
elif [[ "$SPEC" == "fuzz_nn" ]];
then
    # Run the MNIST NN Example
    PREV_K=`(cat NN_Example/src/150.cpp | grep -Po "UNROLL_LIMIT \K[0-9]*")`
    sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" NN_Example/src/150.cpp
    echo "K-Induction : ${PREV_K}, `(cat NN_Example/src/150.cpp | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
    
    time ./run_solver_file.sh \
    ../../benchmarks/NN_Example/c_graph/150.c.json \
    ../../benchmarks/NN_Example/c_smt2/150.c.smt specs/nn_spec \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" NN_Example/src/150.cpp
    echo "K-Induction : ${PREV_K}, `(cat NN_Example/src/150.cpp | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
elif [[ "$SPEC" == "colossus_spec" ]];
then
    export K=1
    # Run a Colassus KLEE Tool Example along with fuzzer.
    # Colassus KLEE Tool : Pull and run the docker with complete setup first.
    docker start colossus
    
    time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/$SPEC \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    docker stop colossus
elif [[ "$SPEC" == "s_colossus_spec" ]];
then
    export K=1
    # Run a Colassus KLEE Tool on Example (Instead of Fuzzer)
    # Colassus KLEE Tool : Pull and run the docker with complete setup first.
    docker start colossus
    
    time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/$SPEC \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    docker stop colossus
elif [[ "$SPEC" == "regular_rq5" ]];
then
    # Run a RQ5 Hybrid Example in regular fuzz_spec
    PREV_K=`(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
    sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" Hybrid_Examples/src/hybrid_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
    
    time ./run_solver_file.sh \
    ../../benchmarks/Hybrid_Examples/c_graph/hybrid_${var}.c.json \
    ../../benchmarks/Hybrid_Examples/c_smt2/hybrid_${var}.c.smt specs/fuzz_base/$SPEC \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" Hybrid_Examples/src/hybrid_${var}.c
    echo "K-Induction : ${PREV_K}, `(cat Hybrid_Examples/src/hybrid_${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
elif [[ "$SPEC" == "c_nl_spec" ||  "$SPEC" == "c_nl_all_spec" ||  "$SPEC" == "c_spec" ]];
then
    # NOTE : c_nl_all_spec is Code2Inv (Vanilla)
    # NOTE : c_nl_spec is Code2Inv (Single)
    time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/$SPEC \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
else
    # Base HonggFuzz or Z3 on 133 benchmark examples.
    # Hybrid on nl_inv grammar also comes to this branch.
    # These are base level specifications that must work on any example.
    PREV_K=`(cat fuzz/src/${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
    sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" fuzz/src/${var}.c
    echo "K-Induction : ${PREV_K}, `(cat fuzz/src/${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
    
    time ./run_solver_file.sh \
    ../../benchmarks/C_instances/c_graph/${var}.c.json \
    ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_base/$SPEC \
    -o results/inv_result_${var}_${SPEC}.log ${var} $SPEC
    
    sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" fuzz/src/${var}.c
    echo "K-Induction : ${PREV_K}, `(cat fuzz/src/${var}.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
fi

rm -rf *.fuzz *.TXT __pycache__

if [[ -f "results/inv_result_${var}_${SPEC}.log"  ]] && [[ "$SPEC" != "fuzz_hybrid" ]] \
&& [[ "$SPEC" != "full_spec" ]] \
&& [[ "$SPEC" != "fuzz_rq3" ]] && [[ "$SPEC" != "fuzz_nn" ]] \
&& [[ "$SPEC" != "fuzz_open" ]];
then
    INV=`(head -n 1 results/inv_result_${var}_${SPEC}.log)`
    cd ../../
    timeout 15 scripts/check.sh ${var} "${INV}" ${SPEC}
else
    echo "The tool has converged but checking using Z3 is not possible. Example : ${var}, Spec : ${SPEC}"
fi