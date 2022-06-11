#!/usr/bin/env bash
set -e
set -u
set -o pipefail

export CC=$(which hfuzz-clang)
export CXX=$(which hfuzz-clang++)
export AFL=$(which honggfuzz)

export TIMEOUT=$1
export EPOCH=$2
export K=$3

cd ../code2inv/prog_generator

PREV_K=`(cat fuzz/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" fuzz/src/*.c

echo "K-Induction : ${PREV_K}, `(cat fuzz/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
mkdir -p RUNNER_TIME_LOGS_FUZZ_${TIMEOUT}_${EPOCH}_${K} converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K} RUNNER_LOGS_ALLMODELS_FUZZ_${TIMEOUT}_${EPOCH}_${K}

echo "      ==== [ALL MODEL] Working Set : {1..133} ==== "
for file_index in {1..133} ;
do
    var=$file_index
    echo " ==== Solving ALL timeout=${TIMEOUT}s, epoch=${EPOCH}, K=${K} | File : $file_index ==== "
    
    # Run Achar in All mode
    ( time ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_base/fuzz_all_spec \
        -o converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_fuzz_spec.log ${var} \
    fuzz_all_spec > RUNNER_LOGS_ALLMODELS_FUZZ_${TIMEOUT}_${EPOCH}_${K}/fuzz_${var}_all.log ) \
    2> RUNNER_TIME_LOGS_FUZZ_${TIMEOUT}_${EPOCH}_${K}/time_${var}_fuzz_spec.log
    
    sleep 60

    # Run Achar in All mode
    ( time ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/fuzz_base/fuzz_all_spec \
        -o converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_fuzz_spec.log ${var} \
    fuzz_all_spec > RUNNER_LOGS_ALLMODELS_FUZZ_${TIMEOUT}_${EPOCH}_${K}/fuzz_${var}_all.log ) \
    2> RUNNER_TIME_LOGS_FUZZ_${TIMEOUT}_${EPOCH}_${K}/time_${var}_fuzz_spec.log
    
    # # Check if the result is correct
    if [[ -f "converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_fuzz_spec.log" ]];
    then
        INV=`(head -n 1 converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_fuzz_spec.log)`
        cd ../../
        timeout 15 scripts/check.sh ${var} "${INV}" fuzz_all_spec
        cd ./code2inv/prog_generator
    else
        echo "Could not converge for ${var}"
    fi
    
    # This is fuzzer cool down time.
    sleep 120
done

sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" fuzz/src/*.c
echo "K-Induction : ${PREV_K}, `(cat fuzz/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"

echo " ==== Cleaning Up [Phase-1] ==== "
rm -rf *.fuzz
rm -rf *.TXT models.txt
rm -rf __pycache__
rm -rf ../*.smt2 ../*.smt

echo " ==== Processing Initiated ==== "
mv results results_${TIMEOUT}_${EPOCH}_${K}
mv candidates candidates_${TIMEOUT}_${EPOCH}_${K}
mv models models_${TIMEOUT}_${EPOCH}_${K}

echo " ==== MkDirs Initiated ==== "
mkdir -p results candidates models cache
mkdir -p FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}

echo " ==== Moving Dirs ==== "
mv results_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}
mv candidates_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}
mv models_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}

mv RUNNER_TIME_LOGS_FUZZ_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}
cp -R converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K}/* cache
mv converged_fuzz_all_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}
mv RUNNER_LOGS_ALLMODELS_FUZZ_${TIMEOUT}_${EPOCH}_${K} FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}

echo " ==== Zipping for Upload : FUZZER_${TIMEOUT}_${EPOCH}_${K}.zip ==== "
zip -r "FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}.zip" FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}/*
mkdir -p ../../scripts/CSVs
mv FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}.zip ../../scripts/CSVs

echo " ==== Cleaning Up [Phase-2] ==== "
rm -rf FUZZER_ALL_${TIMEOUT}_${EPOCH}_${K}
rm -rf __pycache__

echo " ==== Generating Results [Converged Cases] ==== "
# Process and dump the CSV for converged cases.
cd ../../scripts
mkdir -p CSVs
./getSolved_all.sh fuzz_all_${TIMEOUT} ${EPOCH} ${K} cache ACHAR_K_ALL_${TIMEOUT}_${EPOCH}_${K} "Achar (All, K=${K})"
rm -rf models

echo " ==== Cleaning Up [Phase-3] ==== "
rm -rf results/* candidates/* models/* cache/*