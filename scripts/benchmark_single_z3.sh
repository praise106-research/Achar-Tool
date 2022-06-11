#!/usr/bin/env bash
set -e
set -u
set -o pipefail

cd ../code2inv/prog_generator
mkdir -p RUNNER_TIME_LOGS_Z3_SINGLE results_Z3_single RUNNER_LOGS_SINGLE_Z3

export TIMEOUT=10
export EPOCH=8
export K=64

for file_index in {1..133};
do
    var=$file_index
    echo " ======== Running Z3 Single on $file_index file ======== "
    ( time ./run_solver_file.sh \
        ../../benchmarks/C_instances/c_graph/${var}.c.json \
        ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_spec \
    -o results_Z3_single/inv_result_${var}_c_nl_spec.log ${var} c_nl_spec > RUNNER_LOGS_SINGLE_Z3/z3_${var}_single.log ) \
    2> RUNNER_TIME_LOGS_Z3_SINGLE/time_${var}_c_nl_spec.log
done

echo " ==== Cleaning Up [Phase-1] ==== "
rm -rf *.fuzz
rm -rf *.TXT models.txt

echo " ==== Processing Initiated ==== "
mv results_Z3_single converged_z3_single_${EPOCH}
mv results results_z3_single_${EPOCH}
mv candidates candidates_z3_single_${EPOCH}
mv models models_z3_single_${EPOCH}

echo " ==== MkDirs Initiated ==== "
mkdir -p results candidates models cache
mkdir -p Z3_SINGLE_${EPOCH}

echo " ==== Moving Dirs ==== "
mv results_z3_single_${EPOCH} Z3_SINGLE_${EPOCH}
mv candidates_z3_single_${EPOCH} Z3_SINGLE_${EPOCH}
mv models_z3_single_${EPOCH} Z3_SINGLE_${EPOCH}

cp -R converged_z3_single_${EPOCH}/* cache
mv converged_z3_single_${EPOCH} Z3_SINGLE_${EPOCH}

mv RUNNER_TIME_LOGS_Z3_SINGLE Z3_SINGLE_${EPOCH}
mv RUNNER_LOGS_SINGLE_Z3 Z3_SINGLE_${EPOCH}

echo " ==== Zipping for Upload : Z3_SINGLE_${EPOCH}.zip ==== "
zip -r "Z3_SINGLE_${EPOCH}.zip" Z3_SINGLE_${EPOCH}/*

echo " ==== Generating Results [Converged Cases] ==== "
# Process and dump the CSV for converged cases.
cd ../../scripts
mkdir -p CSVs
./getSolved.sh z3 single ${EPOCH} cache
rm -rf models

echo " ==== Cleaning Up [Phase-2] ==== "
rm -rf results/* candidates/* models/* cache/*