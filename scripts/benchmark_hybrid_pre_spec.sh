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

PREV_K=`(cat HYBRID_PRE/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`
sed -i "s/UNROLL_LIMIT ${PREV_K}/UNROLL_LIMIT ${K}/g" HYBRID_PRE/src/*.c

echo "K-Induction : ${PREV_K}, `(cat HYBRID_PRE/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"
mkdir -p RUNNER_TIME_LOGS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K} converged_fuzz_${TIMEOUT}_${EPOCH}_${K} RUNNER_LOGS_ALLMODELS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}

echo "      ==== [HYBRID PRE SOLVER] Working Set : {1..133} ==== "
for file_index in {1..133};
do
    var=$file_index
    echo " ==== Solving HYBRID PRE timeout=${TIMEOUT}s, epoch=${EPOCH}, K=${K} | File : $file_index ==== "

    ( time ./run_solver_file.sh \
        ../../benchmarks/hybrid_pre/c_graph/${var}.c.json \
        ../../benchmarks/hybrid_pre/c_smt2/${var}.c.smt specs/fuzz_base/hybrid_pre_spec \
        -o converged_fuzz_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_hybrid_pre_spec.log ${var} \
    hybrid_pre_spec > RUNNER_LOGS_ALLMODELS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}/fuzz_${var}_all.log ) \
    2> RUNNER_TIME_LOGS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}/time_${var}_hybrid_spec.log
    
    sleep 60

    ( time ./run_solver_file.sh \
        ../../benchmarks/hybrid_pre/c_graph/${var}.c.json \
        ../../benchmarks/hybrid_pre/c_smt2/${var}.c.smt specs/fuzz_base/hybrid_pre_spec \
        -o converged_fuzz_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_hybrid_pre_spec.log ${var} \
    hybrid_pre_spec > RUNNER_LOGS_ALLMODELS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}/fuzz_${var}_all.log ) \
    2> RUNNER_TIME_LOGS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}/time_${var}_hybrid_spec.log
    
    # Check if the result is correct
    if [[ -f "converged_fuzz_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_hybrid_pre_spec.log" ]];
    then
        INV=`(head -n 1 converged_fuzz_${TIMEOUT}_${EPOCH}_${K}/inv_result_${var}_hybrid_pre_spec.log)`
        cd ../../
        echo
        timeout 15 scripts/check.sh ${var} "${INV}" hybrid_pre_spec
        echo
        timeout 15 scripts/check.sh ${var} "${INV}" fuzz_spec
        echo
        cd ./code2inv/prog_generator
    else
        echo "Could not converge for ${var}"
    fi
    
    # This is cool down time.
    sleep 120
done

sed -i "s/UNROLL_LIMIT ${K}/UNROLL_LIMIT ${PREV_K}/g" HYBRID_PRE/src/*.c
echo "K-Induction : ${PREV_K}, `(cat HYBRID_PRE/src/36.c | grep -Po "UNROLL_LIMIT \K[0-9]*")`"

echo " ==== Cleaning Up [Phase-1] ==== "
rm -rf *.fuzz
rm -rf *.TXT models.txt
rm -rf __pycache__

echo " ==== Processing Initiated ==== "
mv results results_${TIMEOUT}_${EPOCH}_${K}
mv candidates candidates_${TIMEOUT}_${EPOCH}_${K}
mv models models_${TIMEOUT}_${EPOCH}_${K}

echo " ==== MkDirs Initiated ==== "
mkdir -p results candidates models cache
mkdir -p HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}

echo " ==== Moving Dirs ==== "
mv results_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
mv candidates_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
mv models_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}

mv RUNNER_TIME_LOGS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
cp -R converged_fuzz_${TIMEOUT}_${EPOCH}_${K}/* cache
mv converged_fuzz_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
mv RUNNER_LOGS_ALLMODELS_HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K} HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}

echo " ==== Zipping for Upload : HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}.zip ==== "
mv hybrid_pre_calls HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
zip -r "HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}.zip" HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}/*
rm -rf HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}
mkdir -p ../../scripts/CSVs
mv HYBRID_PRE_${TIMEOUT}_${EPOCH}_${K}.zip ../../scripts/CSVs

echo " ==== Generating Results [Converged Cases] ==== "
# Process and dump the CSV for converged cases.
cd ../../scripts
mkdir -p CSVs
./getSolved.sh pre_${TIMEOUT} ${EPOCH} ${K} cache ACHAR_HYBRID_${TIMEOUT}_${EPOCH}_${K} "Achar (Hybrid Pre)"
rm -rf models

echo " ==== Cleaning Up [Phase-2] ==== "
rm -rf results/* candidates/* models/* cache/*