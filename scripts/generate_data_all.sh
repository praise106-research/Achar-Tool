#!/usr/bin/env bash
# set -e
# set -u
# set -o pipefail

TIMEOUT=$1
EPOCH=$2
K=$3

if [[ -z $5 ]];
then 
    NAME="Achar_${TIMEOUT}_${EPOCH}_${K}"
else
    NAME=$5
fi

if [[ -z $6 ]];
then 
    ALIAS="Tool (${TIMEOUT}, ${EPOCH}, ${K})"
else
    ALIAS=$6
fi

echo "Generating data for $ALIAS"
mkdir -p CE_Data Time_Data
touch stats.log

correct=`cat CSVs/compile_all_results_${TIMEOUT}_${EPOCH}_${K}.csv | grep "Passed" | grep "Yes" | wc -l`
incorrect=`cat CSVs/compile_all_results_${TIMEOUT}_${EPOCH}_${K}.csv | grep "Failed" | grep "Yes" | wc -l`

echo "Correct : $correct"
echo "Incorrect : $incorrect"

python3 datagen.py CSVs/compile_all_results_${TIMEOUT}_${EPOCH}_${K}.csv $NAME "$ALIAS"
