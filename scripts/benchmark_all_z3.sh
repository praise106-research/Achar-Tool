#!/usr/bin/env bash
# set -e
# set -u
# set -o pipefail

cd ../code2inv/prog_generator
mkdir -p RUNNER_TIME_LOGS_Z3_ALL results_Z3_all RUNNER_LOGS_ALL_Z3

export TIMEOUT=$1
export EPOCH=$2
export K=$3

for file_index in {1..133};
do
    var=$file_index
    # Code2Inv tool seems to hang on these two examples, 83 and 85.
    if [[ "${file_index}" != "83" ]] && [[ "${file_index}" != "85" ]]
    then
        echo " ======== Running Z3 All on $file_index file ======== "
        ( time ./run_solver_file.sh \
            ../../benchmarks/C_instances/c_graph/${var}.c.json \
            ../../benchmarks/C_instances/c_smt2/${var}.c.smt specs/c_nl_all_spec \
            -o results_Z3_all/inv_result_${var}_c_nl_all_spec.log ${var} \
        c_nl_all_spec > RUNNER_LOGS_ALL_Z3/z3_${var}_all.log ) \
        2> RUNNER_TIME_LOGS_Z3_ALL/time_${var}_c_nl_all_spec.log
        echo " Status : $?"
        sleep 60
    fi
done

echo " ==== Cleaning Up [Phase-1] ==== "
rm -rf *.fuzz
rm -rf *.TXT models.txt

echo " ==== Processing Initiated ==== "
mv results_Z3_all converged_z3_all_${EPOCH}
mv results results_Z3_all_${EPOCH}
mv candidates candidates_z3_all_${EPOCH}
mv models models_z3_all_${EPOCH}

echo " ==== MkDirs Initiated ==== "
mkdir -p results candidates models cache
mkdir -p Z3_all_${EPOCH}

echo " ==== Moving Dirs ==== "
mv results_Z3_all_${EPOCH} Z3_all_${EPOCH}
mv candidates_z3_all_${EPOCH} Z3_all_${EPOCH}
mv models_z3_all_${EPOCH} Z3_all_${EPOCH}

cp -R converged_z3_all_${EPOCH}/* cache
mv converged_z3_all_${EPOCH} Z3_all_${EPOCH}

mv RUNNER_TIME_LOGS_Z3_ALL Z3_all_${EPOCH}
mv RUNNER_LOGS_ALL_Z3 Z3_all_${EPOCH}

echo " ==== Zipping for Upload : Z3_all_${EPOCH}.zip ==== "
zip -r "Z3_all_${EPOCH}.zip" Z3_all_${EPOCH}/*

echo " ==== Generating Results [Converged Cases] ==== "
# Process and dump the CSV for converged cases.
cd ../../scripts
mkdir -p CSVs
./getSolved_all.sh z3 all ${EPOCH} cache
rm -rf models

echo " ==== Cleaning Up [Phase-2] ==== "
rm -rf results/* candidates/* models/* cache/*
