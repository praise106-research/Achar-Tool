#!/usr/bin/env bash
set -e
set -u
set -o pipefail

if [[ -z "$3" ]];
then
    model=`python3 code2inv/prog_generator/checkers/c_inv_checker.py benchmarks/C_instances/c_smt2/$1.c.smt "$2"`
    simplify=`python3 code2inv/processing/simplifier.py "$2"`

    echo "Invariant Checked : $2"
    echo "CounterExample : $model"
    echo "Simplifed Expression : $simplify"
    exit 0
fi 

if [[ "$3" == "hybrid_loop_spec" ]];
then
    model=`python3 code2inv/prog_generator/checkers/c_inv_checker.py benchmarks/hybrid_loop/c_smt2/$1.c.smt "$2"`
    simplify=`python3 code2inv/processing/simplifier.py "$2"`

    echo "Invariant Checked : $2"
    echo "CounterExample : $model"
    echo "Simplifed Expression : $simplify"
elif [[ "$3" == "hybrid_pre_spec" ]];
then
    model=`python3 code2inv/prog_generator/checkers/c_inv_checker.py benchmarks/hybrid_pre/c_smt2/$1.c.smt "$2"`
    simplify=`python3 code2inv/processing/simplifier.py "$2"`

    echo "Invariant Checked : $2"
    echo "CounterExample : $model"
    echo "Simplifed Expression : $simplify"
else
    model=`python3 code2inv/prog_generator/checkers/c_inv_checker.py benchmarks/C_instances/c_smt2/$1.c.smt "$2"`
    simplify=`python3 code2inv/processing/simplifier.py "$2"`

    echo "Invariant Checked : $2"
    echo "CounterExample : $model"
    echo "Simplifed Expression : $simplify"
fi