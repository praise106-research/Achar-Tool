#!/usr/bin/bash

rm -rf cache/*
rm -rf models/*
rm -rf candidates/*
rm -rf results/*

rm -rf models.txt *.TXT *.fuzz
rm -rf __pycache__
rm -rf RUNNER_*

rm -rf ../__pycache__
rm -rf ../new.smt2
rm -rf ../new.smt

rm -rf converged_*
rm -rf *_calls

mkdir -p cache
mkdir -p models
mkdir -p candidates
mkdir -p results
